#pragma once

#include "obj_loader.hpp"
#include "texture_loader.hpp"
#include "render_bus.hpp"
#include "base_entity.hpp"
#include "sky_entity.hpp"
#include "terrain_entity.hpp"
#include "water_entity.hpp"
#include "game_entity.hpp"
#include "billboard_entity.hpp"
#include "aabb_entity.hpp"
#include "light_entity.hpp"
#include "gui_entity.hpp"
#include "text_entity.hpp"
#include "entity_type.hpp"

class BaseEntityManager
{
public:
	BaseEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus);
	virtual ~BaseEntityManager();

	void deleteEntity(const string& ID, EntityType type);
	void deleteEntities();

	bool isExisting(const string& ID);

	virtual BaseEntity * getEntity(const string& ID) = 0;

	virtual void update() = 0;

protected:
	OBJLoader&     _objLoader;
	TextureLoader& _texLoader;
	RenderBus&     _renderBus;

	BaseEntity * _createEntity(EntityType type, const string& ID);

	vector<BaseEntity*> & _getBaseEntities();
	
	BaseEntity * _getBaseEntity(const string& ID, EntityType type);

private:
	vector<BaseEntity*> _entities;
};