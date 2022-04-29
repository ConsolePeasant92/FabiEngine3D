#include "master_renderer.hpp"
#include "render_storage.hpp"

#include <functional>
#include <map>

using std::make_shared;
using std::dynamic_pointer_cast;
using std::function;
using std::map;

void MasterRenderer::renderLogo(shared_ptr<Quad2dEntity> quad, const ivec2 & size)
{
	glViewport(0, 0, size.x, size.y);

	glClear(GL_COLOR_BUFFER_BIT);

	_quad2dEntityColorRenderer->bind();

	_quad2dEntityColorRenderer->render(quad);

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
	if(_skyManager->getSelectedEntity() != nullptr)
	{
		_skyEntityColorRenderer->bind();

		_skyEntityColorRenderer->render(_skyManager->getSelectedEntity());

		_skyEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTerrainEntity()
{
	if(_terrainManager->getSelectedTerrain() != nullptr)
	{
		_terrainEntityColorRenderer->bind();

		_terrainEntityColorRenderer->processPointlights(_pointlightManager->getEntities());

		_terrainEntityColorRenderer->processSpotlights(_spotlightManager->getSpotlights());

		_terrainEntityColorRenderer->render(_terrainManager->getSelectedTerrain());

		_terrainEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderWaterEntity()
{
	if(_waterManager->getSelectedWater() != nullptr)
	{
		_waterEntityColorRenderer->bind();

		_waterEntityColorRenderer->processPointlights(_pointlightManager->getEntities());

		_waterEntityColorRenderer->processSpotlights(_spotlightManager->getSpotlights());

		_waterEntityColorRenderer->render(_waterManager->getSelectedWater());

		_waterEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderOpaqueModelEntities()
{
	if(!_modelManager->getEntities().empty())
	{
		_modelEntityColorRenderer->bind();

		_modelEntityColorRenderer->processPointlights(_pointlightManager->getEntities());

		_modelEntityColorRenderer->processSpotlights(_spotlightManager->getSpotlights());

		for(const auto & [modelId, model] : _modelManager->getEntities())
		{
			bool isTransparent = false;

			for(const auto & partId : model->getPartIds())
			{
				if(model->getOpacity(partId) < 1.0f)
				{
					isTransparent = true;
				}
			}

			if(isTransparent)
			{
				continue;
			}

			if(model->isLevelOfDetailed())
			{
				const auto levelOfDetailModel = _modelManager->getEntities().find(model->getLevelOfDetailId())->second;
				const auto originalPosition = levelOfDetailModel->getBasePosition();
				const auto originalRotation = levelOfDetailModel->getBaseRotation();
				const auto originalSize = levelOfDetailModel->getBaseSize();
				const auto originalVisibility = levelOfDetailModel->isVisible();

				levelOfDetailModel->setBasePosition(model->getBasePosition());
				levelOfDetailModel->setBaseRotation(model->getBaseRotation());
				levelOfDetailModel->setBaseSize(model->getBaseSize());
				levelOfDetailModel->setVisible(model->isVisible());
				levelOfDetailModel->updateTransformation();

				_modelEntityColorRenderer->render(levelOfDetailModel, _captorManager->getEntities());

				levelOfDetailModel->setBasePosition(originalPosition);
				levelOfDetailModel->setBaseRotation(originalRotation);
				levelOfDetailModel->setBaseSize(originalSize);
				levelOfDetailModel->setVisible(originalVisibility);
				levelOfDetailModel->updateTransformation();
			}
			else
			{
				_modelEntityColorRenderer->render(model, _captorManager->getEntities());
			}
		}

		_modelEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTransparentModelEntities()
{
	if(!_modelManager->getEntities().empty())
	{
		_modelEntityColorRenderer->bind();

		_modelEntityColorRenderer->processPointlights(_pointlightManager->getEntities());

		_modelEntityColorRenderer->processSpotlights(_spotlightManager->getSpotlights());

		for(const auto & [modelId, model] : _modelManager->getEntities())
		{
			bool isTransparent = false;

			for(const auto & partId : model->getPartIds())
			{
				if(model->getOpacity(partId) < 1.0f)
				{
					isTransparent = true;

					break;
				}
			}

			if(!isTransparent)
			{
				continue;
			}

			if(model->isLevelOfDetailed())
			{
				const auto levelOfDetailModel = _modelManager->getEntities().find(model->getLevelOfDetailId())->second;
				const auto originalPosition = levelOfDetailModel->getBasePosition();
				const auto originalRotation = levelOfDetailModel->getBaseRotation();
				const auto originalSize = levelOfDetailModel->getBaseSize();
				const auto originalVisibility = levelOfDetailModel->isVisible();

				levelOfDetailModel->setBasePosition(model->getBasePosition());
				levelOfDetailModel->setBaseRotation(model->getBaseRotation());
				levelOfDetailModel->setBaseSize(model->getBaseSize());
				levelOfDetailModel->setVisible(model->isVisible());
				levelOfDetailModel->updateTransformation();

				_modelEntityColorRenderer->render(levelOfDetailModel, _captorManager->getEntities());

				levelOfDetailModel->setBasePosition(originalPosition);
				levelOfDetailModel->setBaseRotation(originalRotation);
				levelOfDetailModel->setBaseSize(originalSize);
				levelOfDetailModel->setVisible(originalVisibility);
				levelOfDetailModel->updateTransformation();
			}
			else
			{
				_modelEntityColorRenderer->render(model, _captorManager->getEntities());
			}
		}

		_modelEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderOpaqueQuad3dEntities()
{
	if(!_quad3dManager->getEntities().empty())
	{
		_quad3dEntityColorRenderer->bind();

		for(const auto & [quad3dId, quad3d] : _quad3dManager->getEntities())
		{
			if(quad3d->getOpacity() < 1.0f)
			{
				continue;
			}

			_quad3dEntityColorRenderer->render(quad3d);
		}

		_quad3dEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTransparentQuad3dEntities()
{
	if(!_quad3dManager->getEntities().empty())
	{
		_quad3dEntityColorRenderer->bind();

		for(const auto & [quad3dId, quad3d] : _quad3dManager->getEntities())
		{
			if(quad3d->getOpacity() == 1.0f)
			{
				continue;
			}

			_quad3dEntityColorRenderer->render(quad3d);
		}

		_quad3dEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderOpaqueText3dEntities()
{
	if(!_text3dManager->getText3ds().empty())
	{
		_quad3dEntityColorRenderer->bind();

		for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
		{
			if(text3d->getOpacity() < 1.0f)
			{
				continue;
			}

			for(const auto & characterEntity : text3d->getCharacterEntities())
			{
				_quad3dEntityColorRenderer->render(characterEntity);
			}
		}

		_quad3dEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderTransparentText3dEntities()
{
	if(!_text3dManager->getText3ds().empty())
	{
		_quad3dEntityColorRenderer->bind();

		for(const auto & [text3dId, text3d] : _text3dManager->getText3ds())
		{
			if(text3d->getOpacity() == 1.0f)
			{
				continue;
			}

			for(const auto & characterEntity : text3d->getCharacterEntities())
			{
				_quad3dEntityColorRenderer->render(characterEntity);
			}
		}

		_quad3dEntityColorRenderer->unbind();
	}
}

void MasterRenderer::_renderAabbEntities()
{
	if(!_aabbManager->getAabbs().empty())
	{
		_aabbEntityColorRenderer->bind();

		for(const auto & [aabbId, aabb] : _aabbManager->getAabbs())
		{
			_aabbEntityColorRenderer->render(aabb);
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
	if(!_quad2dManager->getEntities().empty() || !_text2dManager->getEntities().empty())
	{
		_quad2dEntityColorRenderer->bind();

		map<int, shared_ptr<BaseEntity>> orderedQuad2dEntities;
		for(const auto & [quad2dId, quad2d] : _quad2dManager->getEntities())
		{
			if(quad2d->getId() != _renderStorage->getCursorEntityId())
			{
				orderedQuad2dEntities.insert({quad2d->getDepth(), quad2d});
			}
		}
		for(const auto & [text2dId, text2d] : _text2dManager->getEntities())
		{
			orderedQuad2dEntities.insert({text2d->getDepth(), text2d});
		}

		for(const auto & [quad2dId, quad2d] : orderedQuad2dEntities)
		{
			auto castedQuad2dEntity = dynamic_pointer_cast<Quad2dEntity>(quad2d);
			auto castedText2dEntity = dynamic_pointer_cast<Text2dEntity>(quad2d);

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
			_quad2dEntityColorRenderer->render(_quad2dManager->getEntities().at(_renderStorage->getCursorEntityId()));
		}

		_quad2dEntityColorRenderer->unbind();
	}
}