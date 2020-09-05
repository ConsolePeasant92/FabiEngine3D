#include "aabb_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

AabbEntityManager::AabbEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus) :
	BaseEntityManager(objLoader, texLoader, renderBus)
{
	
}

AabbEntity * AabbEntityManager::getEntity(const string& ID)
{
	return dynamic_cast<AabbEntity*>(_getBaseEntity(ID, EntityType::AABB));
}

const vector<AabbEntity*> AabbEntityManager::getEntities()
{
	vector<AabbEntity*> newVector;

	for (auto& entity : _getBaseEntities())
	{
		newVector.push_back(dynamic_cast<AabbEntity*>(entity));
	}

	return newVector;
}

void AabbEntityManager::addAabbEntity(const string& ID, vec3 T, vec3 R, vec3 S, bool responsive)
{
	// Load OBJ model
	float box_data[] =
	{
		-0.5f,  1.0f, -0.5f,
		 0.5f,  1.0f, -0.5f,
		 0.5f,  0.0f, -0.5f,
		-0.5f,  0.0f, -0.5f,
		-0.5f,  1.0f, -0.5f,
		-0.5f,  1.0f,  0.5f,
		 0.5f,  1.0f,  0.5f,
		 0.5f,  0.0f,  0.5f,
		-0.5f,  0.0f,  0.5f,
		-0.5f,  1.0f,  0.5f,
		 0.5f,  1.0f,  0.5f,
		 0.5f,  1.0f, -0.5f,
		 0.5f,  0.0f, -0.5f,
		 0.5f,  0.0f,  0.5f,
		-0.5f,  0.0f,  0.5f,
		-0.5f,  0.0f, -0.5f
	};

	// Create entity
	_createEntity(EntityType::AABB, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(BufferType::AABB, box_data, sizeof(box_data) / sizeof(float)));

	// Other
	getEntity(ID)->setTranslation(T);
	getEntity(ID)->setRotation(R);
	getEntity(ID)->setScaling(S);
	getEntity(ID)->setResponsiveness(responsive);
}

void AabbEntityManager::bindAabbEntity(const string& ID, const string& parentID, vec3 R, vec3 S, bool responsive)
{
	addAabbEntity(ID, vec3(0.0f), R, S, responsive);
	getEntity(ID)->setParentID(parentID);
}

void AabbEntityManager::update(const vector<GameEntity*> & gameEntities)
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary billboard entity object
		auto * entity = getEntity(baseEntity->getID());

		// Optional translation update
		if (entity->getParentID() != "")
		{
			bool found = false;

			for (auto & gameEntity : gameEntities) // Loop over game entities
			{
				if (entity->getParentID() == gameEntity->getID()) // Check for match
				{
					entity->setTranslation(gameEntity->getTranslation()); // Update translation
					found = true;
				}
			}

			// Error checking
			if (!found)
			{
				Logger::getInst().throwError("Collision entity \"" + entity->getID() + "\" bound to nonexisting game entity \"" + entity->getParentID() + "\"!");
			}
		}

		// Calculate model matrix
		if (entity->isVisible())
		{
			entity->updateModelMatrix();
		}
	}
}