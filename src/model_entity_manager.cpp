#include "model_entity_manager.hpp"
#include "logger.hpp"

#include <map>

using std::make_shared;
using std::max;
using std::map;

const shared_ptr<ModelEntity> ModelEntityManager::getEntity(const string & id) const
{
	auto iterator = _entities.find(id);

	if(iterator == _entities.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<ModelEntity>> & ModelEntityManager::getEntities() const
{
	return _entities;
}

void ModelEntityManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void ModelEntityManager::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

void ModelEntityManager::inject(shared_ptr<Timer> timer)
{
	_timer = timer;
}

void ModelEntityManager::inject(shared_ptr<ReflectionEntityManager> reflectionManager)
{
	_reflectionManager = reflectionManager;
}

void ModelEntityManager::inject(shared_ptr<MeshLoader> meshLoader)
{
	_meshLoader = meshLoader;
}

void ModelEntityManager::inject(shared_ptr<VertexBufferCache> vertexBufferCache)
{
	_vertexBufferCache = vertexBufferCache;
}

void ModelEntityManager::createEntity(const string & id, const string & meshPath)
{
	if(isEntityExisting(id))
	{
		abort();
	}

	auto mesh = _meshLoader->loadMesh(meshPath);

	if(mesh == nullptr)
	{
		return;
	}

	auto entity = make_shared<ModelEntity>(id);

	for(const auto & part : mesh->getParts())
	{
		vector<float> bufferData;

		for(unsigned int index = 0; index < static_cast<unsigned int>(part->getPositions().size()); index++)
		{
			bufferData.push_back(part->getPositions()[index].x);
			bufferData.push_back(part->getPositions()[index].y);
			bufferData.push_back(part->getPositions()[index].z);

			bufferData.push_back(part->getUvs()[index].x);
			bufferData.push_back(part->getUvs()[index].y);

			bufferData.push_back(part->getNormals()[index].x);
			bufferData.push_back(part->getNormals()[index].y);
			bufferData.push_back(part->getNormals()[index].z);

			bufferData.push_back(part->getTangents()[index].x);
			bufferData.push_back(part->getTangents()[index].y);
			bufferData.push_back(part->getTangents()[index].z);
		}

		entity->createPart(part->getName());

		auto vertexBuffer = _vertexBufferCache->getBuffer(meshPath, part->getName());

		if(vertexBuffer == nullptr)
		{
			vertexBuffer = make_shared<VertexBuffer>(VertexBufferType::POS_UV_NOR_TAN, &bufferData[0], static_cast<unsigned int>(bufferData.size()));

			_vertexBufferCache->storeBuffer(meshPath, part->getName(), vertexBuffer);
		}

		entity->setVertexBuffer(part->getName(), vertexBuffer);
	}

	entity->setMeshPath(meshPath);

	_entities.insert({id, entity});
}

void ModelEntityManager::deleteEntity(const string & id)
{
	if(!isEntityExisting(id))
	{
		abort();
	}

	_entities.erase(id);
}

void ModelEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool ModelEntityManager::isEntityExisting(const string & id) const
{
	return (_entities.find(id) != _entities.end());
}

const bool ModelEntityManager::isEntitiesExisting() const
{
	return !_entities.empty();
}

void ModelEntityManager::update()
{
	for(const auto & [key, entity] : _entities)
	{
		entity->updateTarget();

		if(!entity->isVisible())
		{
			continue;
		}

		if(entity->getLevelOfDetailEntityId().empty())
		{
			entity->setLevelOfDetailed(false);
		}
		else
		{
			if(getEntities().find(entity->getLevelOfDetailEntityId()) == getEntities().end())
			{
				abort();
			}

			const auto cameraPosition = _camera->getPosition();
			const auto entityPosition = entity->getBasePosition();
			const auto absolsuteDistance = Mathematics::calculateDistance(cameraPosition, entityPosition);

			entity->setLevelOfDetailed((absolsuteDistance > entity->getLevelOfDetailDistance()));
		}

		if(_reflectionManager->getEntities().find(entity->getPreviousReflectionEntityId()) == _reflectionManager->getEntities().end())
		{
			entity->setPreviousReflectionEntityId("");
			entity->setCubeReflectionMixValue(1.0f);
		}
		if(_reflectionManager->getEntities().find(entity->getCurrentReflectionEntityId()) == _reflectionManager->getEntities().end())
		{
			entity->setCurrentReflectionEntityId("");
			entity->setCubeReflectionMixValue(1.0f);
		}
		if(entity->getPreviousReflectionEntityId() == entity->getCurrentReflectionEntityId())
		{
			entity->setPreviousReflectionEntityId("");
			entity->setCubeReflectionMixValue(1.0f);
		}

		if((_renderStorage->getCubeReflectionInterval() == 0) || (_timer->getPassedUpdateCount() % _renderStorage->getCubeReflectionInterval()) == 0)
		{
			map<float, shared_ptr<ReflectionEntity>> orderedReflectionEntities;

			for(const auto & [key, reflectionEntity] : _reflectionManager->getEntities())
			{
				if(reflectionEntity->isVisible())
				{
					const auto absoluteDistance = Mathematics::calculateDistance(entity->getBasePosition(), reflectionEntity->getPosition());

					orderedReflectionEntities.insert({absoluteDistance, reflectionEntity});
				}
			}

			if(!orderedReflectionEntities.empty())
			{
				const auto closestReflectionEntityId = orderedReflectionEntities.begin()->second->getId();

				if(entity->getCurrentReflectionEntityId() != closestReflectionEntityId)
				{
					entity->setPreviousReflectionEntityId(entity->getCurrentReflectionEntityId());
					entity->setCurrentReflectionEntityId(closestReflectionEntityId);

					if(!entity->getPreviousReflectionEntityId().empty())
					{
						entity->setCubeReflectionMixValue(0.0f);
					}
				}
			}

			entity->setCubeReflectionMixValue(entity->getCubeReflectionMixValue() + CUBE_REFLECTION_OVERLAP_SPEED);
		}

		entity->updateTransformation();
	}
}