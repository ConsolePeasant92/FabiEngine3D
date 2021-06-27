#include "base_entity_manager.hpp"
#include "logger.hpp"

using std::make_shared;

BaseEntityManager::BaseEntityManager(EntityType type, MeshLoader& meshLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	_type(type),
	_meshLoader(meshLoader),
	_textureLoader(texLoader),
	_renderBus(renderBus)
{
	
}

void BaseEntityManager::_createEntity(const string& ID)
{
	// Check for uniqueness of ID & create new entity
	switch (_type)
	{
		case(EntityType::SKY):
		{
			if (_getSkyEntity(ID) != nullptr)
			{
				Logger::throwError("Cannot create sky entity: \"" + ID + "\" already exists!");
			}
			else
			{
				_skyEntities.insert(make_pair(ID, make_shared<SkyEntity>(ID)));
			}

			break;
		}

		case(EntityType::TERRAIN):
		{
			if (_getTerrainEntity(ID) != nullptr)
			{
				Logger::throwError("Cannot create terrain entity: \"" + ID + "\" already exists!");
			}
			else
			{
				_terrainEntities.insert(make_pair(ID, make_shared<TerrainEntity>(ID)));
			}

			break;
		}

		case(EntityType::WATER):
		{
			if (_getWaterEntity(ID) != nullptr)
			{
				Logger::throwError("Cannot create water entity: \"" + ID + "\" already exists!");
			}
			else
			{
				_waterEntities.insert(make_pair(ID, make_shared<WaterEntity>(ID)));
			}

			break;
		}

		case(EntityType::MODEL):
		{
			if (_getModelEntity(ID) != nullptr)
			{
				Logger::throwError("Cannot create model entity: \"" + ID + "\" already exists!");
			}
			else
			{
				_modelEntities.insert(make_pair(ID, make_shared<ModelEntity>(ID)));
			}

			break;
		}

		case(EntityType::BILLBOARD):
		{
			if (_getBillboardEntity(ID) != nullptr)
			{
				Logger::throwError("Cannot create billboard entity: \"" + ID + "\" already exists!");
			}
			else
			{
				_billboardEntities.insert(make_pair(ID, make_shared<BillboardEntity>(ID)));
			}

			break;
		}

		case(EntityType::AABB):
		{
			if (_getAabbEntity(ID) != nullptr)
			{
				Logger::throwError("Cannot create AABB entity: \"" + ID + "\" already exists!");
			}
			else
			{
				_aabbEntities.insert(make_pair(ID, make_shared<AabbEntity>(ID)));
			}

			break;
		}

		case(EntityType::LIGHT):
		{
			if (_getLightEntity(ID) != nullptr)
			{
				Logger::throwError("Cannot create light entity: \"" + ID + "\" already exists!");
			}
			else
			{
				_lightEntities.insert(make_pair(ID, make_shared<LightEntity>(ID)));
			}

			break;
		}

		case(EntityType::IMAGE):
		{
			if (_getImageEntity(ID) != nullptr)
			{
				Logger::throwError("Cannot create image entity: \"" + ID + "\" already exists!");
			}
			else
			{
				_imageEntities.insert(make_pair(ID, make_shared<ImageEntity>(ID)));
				_getImageEntity(ID)->setDepth(_guiDepth);
				_guiDepth++;
			}

			break;
		}

		case(EntityType::TEXT):
		{
			if (_getTextEntity(ID) != nullptr)
			{
				Logger::throwError("Cannot create text entity: \"" + ID + "\" already exists!");
			}
			else
			{
				_textEntities.insert(make_pair(ID, make_shared<TextEntity>(ID)));
				_getTextEntity(ID)->setDepth(_guiDepth);
				_guiDepth++;
			}

			break;
		}
	}
}

void BaseEntityManager::deleteEntity(const string& ID)
{
	switch (_type)
	{
		case(EntityType::SKY):
		{
			if (_skyEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::TERRAIN):
		{
			if (_terrainEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::WATER):
		{
			if (_waterEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::MODEL):
		{
			if (_modelEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::BILLBOARD):
		{
			if (_billboardEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::AABB):
		{
			if (_aabbEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::LIGHT):
		{
			if (_lightEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::IMAGE):
		{
			if (_imageEntities.erase(ID))
			{
				return;
			}

			break;
		}

		case(EntityType::TEXT):
		{
			if (_textEntities.erase(ID))
			{
				return;
			}

			break;
		}
	}

	// Temporary type2string map
	std::map<EntityType, string> temp;
	temp[EntityType::SKY] = "SKY"; temp[EntityType::TERRAIN] = "TERRAIN"; temp[EntityType::WATER] = "WATER";
	temp[EntityType::MODEL] = "MODEL"; temp[EntityType::BILLBOARD] = "BILLBOARD"; temp[EntityType::AABB] = "AABB";
	temp[EntityType::LIGHT] = "LIGHT"; temp[EntityType::IMAGE] = "GUI"; temp[EntityType::TEXT] = "TEXT";

	// Error logging
	Logger::throwError("Non-existing " + temp[_type] + " entity with ID \"" + ID + "\" requested for removal!");
}

void BaseEntityManager::deleteAllEntities()
{
	_aabbEntities.clear();
	_billboardEntities.clear();
	_modelEntities.clear();
	_imageEntities.clear();
	_lightEntities.clear();
	_skyEntities.clear();
	_terrainEntities.clear();
	_textEntities.clear();
	_waterEntities.clear();
}