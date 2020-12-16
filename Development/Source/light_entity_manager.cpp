#include "light_entity_manager.hpp"
#include "configuration.hpp"
#include "logger.hpp"

LightEntityManager::LightEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(EntityType::LIGHT, objLoader, texLoader, renderBus)
{

}

shared_ptr<LightEntity> LightEntityManager::getEntity(const string& ID)
{
	auto result = _getLightEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Nonexisting LIGHT entity with ID \"" + ID + "\" requested");
	}

	return result;
}

const unordered_map<string, shared_ptr<LightEntity>>& LightEntityManager::getEntities()
{
	return _getLightEntities();
}

void LightEntityManager::addLightEntity(const string& ID, Vec3 position, Vec3 color, float intensity, float distanceFactor)
{
	// Create entity
	_createEntity(ID);
	auto entity = getEntity(ID);

	// Fill entity
	entity->setPosition(position);
	entity->setColor(color);
	entity->setIntensity(intensity);
	entity->setDistanceFactor(distanceFactor);
}

void LightEntityManager::update()
{

}