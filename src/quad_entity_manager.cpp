#include "quad_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

QuadEntityManager::QuadEntityManager(RenderBus& renderBus)
	:
	_renderBus(renderBus),
	_centeredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true)),
	_corneredRenderBuffer(make_shared<RenderBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false))
{

}

shared_ptr<QuadEntity> QuadEntityManager::getEntity(const string& ID)
{
	auto iterator = _entities.find(ID);

	if(iterator == _entities.end())
	{
		Logger::throwError("QuadEntityManager::getEntity");
	}
	else
	{
		return iterator->second;
	}
}

const unordered_map<string, shared_ptr<QuadEntity>>& QuadEntityManager::getEntities()
{
	return _entities;
}

void QuadEntityManager::createEntity(const string& ID, bool isCentered)
{
	_entities.insert(make_pair(ID, make_shared<QuadEntity>(ID)));
	getEntity(ID)->setRenderBuffer(isCentered ? _centeredRenderBuffer : _corneredRenderBuffer);
	getEntity(ID)->setCentered(isCentered);
	getEntity(ID)->setDepth(_renderBus.getGuiDepth());
	_renderBus.setGuiDepth(_renderBus.getGuiDepth() + 1);
}

void QuadEntityManager::deleteEntity(const string& ID)
{
	if(!isEntityExisting(ID))
	{
		Logger::throwError("QuadEntityManager::deleteEntity");
	}

	_entities.erase(ID);
}

void QuadEntityManager::deleteEntities()
{
	_entities.clear();
}

const bool QuadEntityManager::isEntityExisting(const string& ID)
{
	return (_entities.find(ID) != _entities.end());
}

void QuadEntityManager::update()
{
	for(const auto& [key, entity] : _entities)
	{
		entity->updateTransformation();

		if(entity->isVisible())
		{
			entity->updateTransformationMatrix();
		}
	}
}