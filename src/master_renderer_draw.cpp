#include "master_renderer.hpp"
#include "render_storage.hpp"

#include <functional>
#include <map>

using std::make_shared;
using std::dynamic_pointer_cast;
using std::function;
using std::map;

void MasterRenderer::renderLogo(shared_ptr<Quad2dEntity> entity, const ivec2 & size)
{
	glViewport(0, 0, size.x, size.y);

	glClear(GL_COLOR_BUFFER_BIT);

	_quad2dEntityColorRenderer->bind();

	_quad2dEntityColorRenderer->render(entity);

	_quad2dEntityColorRenderer->unbind();

	glViewport(0, 0, Configuration::getInst().getWindowSize().x, Configuration::getInst().getWindowSize().y);
}

void MasterRenderer::render3dEntities()
{
	_worldColorCaptureBuffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_renderStorage->setTriangleCountingEnabled(true);
	_renderSkyEntity();
	_renderTerrainEntity();
	_renderWaterEntity();
	_renderOpaqueModelEntities();
	_renderOpaqueQuad3dEntities();
	_renderOpaqueText3dEntities();
	_renderAabbEntities();
	_renderTransparentModelEntities();
	_renderTransparentQuad3dEntities();
	_renderTransparentText3dEntities();
	_renderStorage->setTriangleCountingEnabled(false);
	_worldColorCaptureBuffer->unbind();
	_renderStorage->setPrimarySceneMap(_worldColorCaptureBuffer->getTexture(0));
	_renderStorage->setSecondarySceneMap(_worldColorCaptureBuffer->getTexture(1));
	_renderStorage->setFinalSceneMap(_renderStorage->getPrimarySceneTextureBuffer());
}

void MasterRenderer::render2dEntities()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(Configuration::getInst().getDisplayPosition().x, Configuration::getInst().getDisplayPosition().y, Configuration::getInst().getDisplaySize().x, Configuration::getInst().getDisplaySize().y);
	_renderFinalScene();
	glViewport(0, 0, Configuration::getInst().getWindowSize().x, Configuration::getInst().getWindowSize().y);

	_renderStorage->setTriangleCountingEnabled(true);
	_renderGUI();
	_renderStorage->setTriangleCountingEnabled(false);
}

void MasterRenderer::_renderSkyEntity()
{
	if(_skyEntityManager->getSelectedEntity() != nullptr)
	{
		_skyEntityColorRenderer->bind();

		_skyEntityColorRenderer->render(_skyEntityManager->getSelectedEntity());

		_skyEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTerrainEntity()
{
	if(_terrainEntityManager->getSelectedEntity() != nullptr)
	{
		_terrainEntityColorRenderer->bind();

		_terrainEntityColorRenderer->processPointlightEntities(_pointlightEntityManager->getEntities());

		_terrainEntityColorRenderer->processSpotlightEntities(_spotlightEntityManager->getEntities());

		_terrainEntityColorRenderer->render(_terrainEntityManager->getSelectedEntity());

		_terrainEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderWaterEntity()
{
	if(_waterEntityManager->getSelectedEntity() != nullptr)
	{
		_waterEntityColorRenderer->bind();

		_waterEntityColorRenderer->processPointlightEntities(_pointlightEntityManager->getEntities());

		_waterEntityColorRenderer->processSpotlightEntities(_spotlightEntityManager->getEntities());

		_waterEntityColorRenderer->render(_waterEntityManager->getSelectedEntity());

		_waterEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderOpaqueModelEntities()
{
	if(!_modelEntityManager->getEntities().empty())
	{
		_modelEntityColorRenderer->bind();

		_modelEntityColorRenderer->processPointlightEntities(_pointlightEntityManager->getEntities());

		_modelEntityColorRenderer->processSpotlightEntities(_spotlightEntityManager->getEntities());

		for(const auto & [entityId, entity] : _modelEntityManager->getEntities())
		{
			bool isTransparent = false;

			for(const auto & partId : entity->getPartIds())
			{
				if(entity->getOpacity(partId) < 1.0f)
				{
					isTransparent = true;
				}
			}

			if(isTransparent)
			{
				continue;
			}

			if(entity->isLevelOfDetailed())
			{
				const auto levelOfDetailEntity = _modelEntityManager->getEntities().find(entity->getLevelOfDetailEntityId())->second;
				const auto originalPosition = levelOfDetailEntity->getBasePosition();
				const auto originalRotation = levelOfDetailEntity->getBaseRotation();
				const auto originalSize = levelOfDetailEntity->getBaseSize();
				const auto originalVisibility = levelOfDetailEntity->isVisible();

				levelOfDetailEntity->setBasePosition(entity->getBasePosition());
				levelOfDetailEntity->setBaseRotation(entity->getBaseRotation());
				levelOfDetailEntity->setBaseSize(entity->getBaseSize());
				levelOfDetailEntity->setVisible(entity->isVisible());
				levelOfDetailEntity->updateTransformation();

				_modelEntityColorRenderer->render(levelOfDetailEntity, _captorEntityManager->getEntities());

				levelOfDetailEntity->setBasePosition(originalPosition);
				levelOfDetailEntity->setBaseRotation(originalRotation);
				levelOfDetailEntity->setBaseSize(originalSize);
				levelOfDetailEntity->setVisible(originalVisibility);
				levelOfDetailEntity->updateTransformation();
			}
			else
			{
				_modelEntityColorRenderer->render(entity, _captorEntityManager->getEntities());
			}
		}

		_modelEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTransparentModelEntities()
{
	if(!_modelEntityManager->getEntities().empty())
	{
		_modelEntityColorRenderer->bind();

		_modelEntityColorRenderer->processPointlightEntities(_pointlightEntityManager->getEntities());

		_modelEntityColorRenderer->processSpotlightEntities(_spotlightEntityManager->getEntities());

		for(const auto & [entityId, entity] : _modelEntityManager->getEntities())
		{
			bool isTransparent = false;

			for(const auto & partId : entity->getPartIds())
			{
				if(entity->getOpacity(partId) < 1.0f)
				{
					isTransparent = true;

					break;
				}
			}

			if(!isTransparent)
			{
				continue;
			}

			if(entity->isLevelOfDetailed())
			{
				const auto levelOfDetailEntity = _modelEntityManager->getEntities().find(entity->getLevelOfDetailEntityId())->second;
				const auto originalPosition = levelOfDetailEntity->getBasePosition();
				const auto originalRotation = levelOfDetailEntity->getBaseRotation();
				const auto originalSize = levelOfDetailEntity->getBaseSize();
				const auto originalVisibility = levelOfDetailEntity->isVisible();

				levelOfDetailEntity->setBasePosition(entity->getBasePosition());
				levelOfDetailEntity->setBaseRotation(entity->getBaseRotation());
				levelOfDetailEntity->setBaseSize(entity->getBaseSize());
				levelOfDetailEntity->setVisible(entity->isVisible());
				levelOfDetailEntity->updateTransformation();

				_modelEntityColorRenderer->render(levelOfDetailEntity, _captorEntityManager->getEntities());

				levelOfDetailEntity->setBasePosition(originalPosition);
				levelOfDetailEntity->setBaseRotation(originalRotation);
				levelOfDetailEntity->setBaseSize(originalSize);
				levelOfDetailEntity->setVisible(originalVisibility);
				levelOfDetailEntity->updateTransformation();
			}
			else
			{
				_modelEntityColorRenderer->render(entity, _captorEntityManager->getEntities());
			}
		}

		_modelEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderOpaqueQuad3dEntities()
{
	if(!_quad3dEntityManager->getEntities().empty())
	{
		_quad3dEntityColorRenderer->bind();

		for(const auto & [entityId, entity] : _quad3dEntityManager->getEntities())
		{
			if(entity->getOpacity() < 1.0f)
			{
				continue;
			}

			_quad3dEntityColorRenderer->render(entity);
		}

		_quad3dEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTransparentQuad3dEntities()
{
	if(!_quad3dEntityManager->getEntities().empty())
	{
		_quad3dEntityColorRenderer->bind();

		for(const auto & [entityId, entity] : _quad3dEntityManager->getEntities())
		{
			if(entity->getOpacity() == 1.0f)
			{
				continue;
			}

			_quad3dEntityColorRenderer->render(entity);
		}

		_quad3dEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderOpaqueText3dEntities()
{
	if(!_text3dEntityManager->getEntities().empty())
	{
		_quad3dEntityColorRenderer->bind();

		for(const auto & [entityId, entity] : _text3dEntityManager->getEntities())
		{
			if(entity->getOpacity() < 1.0f)
			{
				continue;
			}

			for(const auto & characterEntity : entity->getCharacterEntities())
			{
				_quad3dEntityColorRenderer->render(characterEntity);
			}
		}

		_quad3dEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTransparentText3dEntities()
{
	if(!_text3dEntityManager->getEntities().empty())
	{
		_quad3dEntityColorRenderer->bind();

		for(const auto & [entityId, entity] : _text3dEntityManager->getEntities())
		{
			if(entity->getOpacity() == 1.0f)
			{
				continue;
			}

			for(const auto & characterEntity : entity->getCharacterEntities())
			{
				_quad3dEntityColorRenderer->render(characterEntity);
			}
		}

		_quad3dEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderAabbEntities()
{
	if(!_aabbEntityManager->getEntities().empty())
	{
		_aabbEntityColorRenderer->bind();

		for(const auto & [entityId, entity] : _aabbEntityManager->getEntities())
		{
			_aabbEntityColorRenderer->render(entity);
		}

		_aabbEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderFinalScene()
{
	_renderSurface->setDiffuseMap(_renderStorage->getFinalSceneTextureBuffer());

	_quad2dEntityColorRenderer->bind();
	_quad2dEntityColorRenderer->render(_renderSurface);
	_quad2dEntityColorRenderer->unbind();
}

void MasterRenderer::_renderGUI()
{
	if(!_quad2dEntityManager->getEntities().empty() || !_text2dEntityManager->getEntities().empty())
	{
		_quad2dEntityColorRenderer->bind();

		map<unsigned int, shared_ptr<BaseEntity>> orderedQuad2dEntities;
		for(const auto & [entityId, entity] : _quad2dEntityManager->getEntities())
		{
			if(entity->getId() != _renderStorage->getCursorEntityId())
			{
				orderedQuad2dEntities.insert({entity->getDepth(), entity});
			}
		}
		for(const auto & [entityId, entity] : _text2dEntityManager->getEntities())
		{
			orderedQuad2dEntities.insert({entity->getDepth(), entity});
		}

		for(const auto & [entityId, entity] : orderedQuad2dEntities)
		{
			auto castedQuad2dEntity = dynamic_pointer_cast<Quad2dEntity>(entity);
			auto castedText2dEntity = dynamic_pointer_cast<Text2dEntity>(entity);

			if(castedQuad2dEntity != nullptr)
			{
				_quad2dEntityColorRenderer->render(castedQuad2dEntity);
			}

			if(castedText2dEntity != nullptr)
			{
				for(const auto & characterEntity : castedText2dEntity->getCharacterEntities())
				{
					_quad2dEntityColorRenderer->render(characterEntity);
				}
			}
		}

		if(!_renderStorage->getCursorEntityId().empty())
		{
			_quad2dEntityColorRenderer->render(_quad2dEntityManager->getEntities().at(_renderStorage->getCursorEntityId()));
		}

		_quad2dEntityColorRenderer->unbind();
	}
}