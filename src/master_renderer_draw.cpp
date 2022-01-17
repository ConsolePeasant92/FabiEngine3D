#include "master_renderer.hpp"
#include "render_bus.hpp"

#include <functional>

using std::make_shared;
using std::dynamic_pointer_cast;
using std::function;

void MasterRenderer::_renderSkyEntity()
{
	if(_skyEntityManager->getSelectedMainSky() != nullptr)
	{
		_skyEntityColorRenderer.bind();

		_skyEntityColorRenderer.render(_skyEntityManager->getSelectedMainSky(), _skyEntityManager->getSelectedMixSky());

		_skyEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderTerrainEntity()
{
	if(_terrainEntityManager->getSelectedTerrain() != nullptr)
	{
		_terrainEntityColorRenderer.bind();

		_terrainEntityColorRenderer.processPointlightEntities(_pointlightEntityManager->getEntities());

		_terrainEntityColorRenderer.processSpotlightEntities(_spotlightEntityManager->getEntities());

		_terrainEntityColorRenderer.render(_terrainEntityManager->getSelectedTerrain());

		_terrainEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderWaterEntity()
{
	if(_waterEntityManager->getSelectedWater() != nullptr)
	{
		_waterEntityColorRenderer.bind();

		_waterEntityColorRenderer.processPointlightEntities(_pointlightEntityManager->getEntities());

		_waterEntityColorRenderer.processSpotlightEntities(_spotlightEntityManager->getEntities());

		_waterEntityColorRenderer.render(_waterEntityManager->getSelectedWater());

		_waterEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderModelEntities()
{
	auto modelEntities = _modelEntityManager->getEntities();

	if(!modelEntities.empty())
	{
		_modelEntityColorRenderer.bind();

		_modelEntityColorRenderer.processPointlightEntities(_pointlightEntityManager->getEntities());

		_modelEntityColorRenderer.processSpotlightEntities(_spotlightEntityManager->getEntities());

		for(const auto& [key, modelEntity] : modelEntities)
		{
			for(const auto& partID : modelEntity->getPartIDs())
			{
				if(modelEntity->getTransparency(partID) != 1.0f)
				{
					goto CONTINUE;
				}
			}

			if(modelEntity->isLevelOfDetailed())
			{
				auto levelOfDetailEntity = modelEntities.find(modelEntity->getLevelOfDetailEntityID())->second;

				fvec3 initialPosition = levelOfDetailEntity->getBasePosition();
				fvec3 initialRotation = levelOfDetailEntity->getBaseRotation();
				fvec3 initialSize = levelOfDetailEntity->getBaseSize();
				bool initialVisibility = levelOfDetailEntity->isVisible();

				levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
				levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
				levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
				levelOfDetailEntity->setVisible(modelEntity->isVisible());
				levelOfDetailEntity->updateTransformationMatrix();

				_modelEntityColorRenderer.render(levelOfDetailEntity, _reflectionEntityManager->getEntities());

				levelOfDetailEntity->setBasePosition(initialPosition);
				levelOfDetailEntity->setBaseRotation(initialRotation);
				levelOfDetailEntity->setBaseSize(initialSize);
				levelOfDetailEntity->setVisible(initialVisibility);
				levelOfDetailEntity->updateTransformationMatrix();
			}
			else
			{
				_modelEntityColorRenderer.render(modelEntity, _reflectionEntityManager->getEntities());
			}

			CONTINUE:;
		}

		for(const auto& [key, modelEntity] : modelEntities)
		{
			bool isSolid = true;
			for(const auto& partID : modelEntity->getPartIDs())
			{
				if(modelEntity->getTransparency(partID) != 1.0f)
				{
					isSolid = false;
					break;
				}
			}
			if(isSolid)
			{
				continue;
			}

			if(modelEntity->isLevelOfDetailed())
			{
				auto levelOfDetailEntity = modelEntities.find(modelEntity->getLevelOfDetailEntityID())->second;

				fvec3 initialPosition = levelOfDetailEntity->getBasePosition();
				fvec3 initialRotation = levelOfDetailEntity->getBaseRotation();
				fvec3 initialSize = levelOfDetailEntity->getBaseSize();
				bool initialVisibility = levelOfDetailEntity->isVisible();

				levelOfDetailEntity->setBasePosition(modelEntity->getBasePosition());
				levelOfDetailEntity->setBaseRotation(modelEntity->getBaseRotation());
				levelOfDetailEntity->setBaseSize((modelEntity->getBaseSize() / modelEntity->getLevelOfDetailSize()) * initialSize);
				levelOfDetailEntity->setVisible(modelEntity->isVisible());
				levelOfDetailEntity->updateTransformationMatrix();

				_modelEntityColorRenderer.render(levelOfDetailEntity, _reflectionEntityManager->getEntities());

				levelOfDetailEntity->setBasePosition(initialPosition);
				levelOfDetailEntity->setBaseRotation(initialRotation);
				levelOfDetailEntity->setBaseSize(initialSize);
				levelOfDetailEntity->setVisible(initialVisibility);
				levelOfDetailEntity->updateTransformationMatrix();
			}
			else
			{
				_modelEntityColorRenderer.render(modelEntity, _reflectionEntityManager->getEntities());
			}
		}

		_modelEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderBillboardEntities()
{
	auto billboardEntities = _billboardEntityManager->getEntities();

	if(!billboardEntities.empty())
	{
		_billboardEntityColorRenderer.bind();

		for(const auto& [key, entity] : billboardEntities)
		{
			_billboardEntityColorRenderer.render(entity);
		}

		_billboardEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderAabbEntities()
{
	if(_renderBus->isAabbFrameRenderingEnabled())
	{
		auto aabbEntities = _aabbEntityManager->getEntities();

		if(!aabbEntities.empty())
		{
			_aabbEntityColorRenderer.bind();

			for(const auto& [key, entity] : aabbEntities)
			{
				_aabbEntityColorRenderer.render(entity);
			}

			_aabbEntityColorRenderer.unbind();
		}
	}
}

void MasterRenderer::_renderFinalSceneMap()
{
	_renderQuad->setDiffuseMap(_renderBus->getFinalSceneMap());

	_quad2dEntityColorRenderer.bind();
	_quad2dEntityColorRenderer.render(_renderQuad);
	_quad2dEntityColorRenderer.unbind();
}

void MasterRenderer::_renderGUI()
{
	if(!_quad2dEntityManager->getEntities().empty() || !_textEntityManager->getEntities().empty())
	{
		_quad2dEntityColorRenderer.bind();

		map<unsigned int, shared_ptr<BaseEntity>> orderedEntityMap;
		for(const auto& [key, quad2dEntity] : _quad2dEntityManager->getEntities())
		{
			if(quad2dEntity->getID() != _renderBus->getCursorEntityID())
			{
				orderedEntityMap.insert(make_pair(quad2dEntity->getDepth(), quad2dEntity));
			}
		}
		for(const auto& [key, textEntity] : _textEntityManager->getEntities())
		{
			orderedEntityMap.insert(make_pair(textEntity->getDepth(), textEntity));
		}

		for(const auto& [key, entity] : orderedEntityMap)
		{
			auto castedQuad2dEntity = dynamic_pointer_cast<Quad2dEntity>(entity);
			auto castedTextEntity = dynamic_pointer_cast<TextEntity>(entity);

			if(castedQuad2dEntity != nullptr)
			{
				_quad2dEntityColorRenderer.render(castedQuad2dEntity);
			}

			if(castedTextEntity != nullptr)
			{
				for(const auto& characterEntity : castedTextEntity->getCharacterEntities())
				{
					_quad2dEntityColorRenderer.render(characterEntity);
				}
			}
		}

		_quad2dEntityColorRenderer.unbind();
	}
}

void MasterRenderer::_renderCursor()
{
	for(const auto& [key, entity] : _quad2dEntityManager->getEntities())
	{
		if(entity->getID() == _renderBus->getCursorEntityID())
		{
			_quad2dEntityColorRenderer.bind();
			_quad2dEntityColorRenderer.render(entity);
			_quad2dEntityColorRenderer.unbind();
		}
	}
}