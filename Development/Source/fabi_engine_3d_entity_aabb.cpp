#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"
#include "logger.hpp"

void FabiEngine3D::aabbEntity_add(const string& ID, Vec3 position, Vec3 size, bool raycastResponsive, bool collisionResponsive, bool isVisible)
{
	_core->_aabbEntityManager.addAabbEntity(ID, position, size, raycastResponsive, collisionResponsive);
	_core->_aabbEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::aabbEntity_bindToModelEntity(const string& parentID, Vec3 position, Vec3 size, 
	bool raycastResponsive, bool collisionResponsive, const string& customAabbID)
{
	if (customAabbID.empty()) // Use parent ID
	{
		if (_core->_modelEntityManager.isExisting(parentID))
		{
			_core->_aabbEntityManager.bindAabbEntity(parentID, parentID, AabbParentType::MODEL_ENTITY, position, size, raycastResponsive, collisionResponsive);
		}
		else
		{
			Logger::throwError("Tried to bind AABB entity to non-existing model entity with ID \"" + parentID + "\"");
		}
	}
	else // Use custom ID
	{
		if (_core->_modelEntityManager.isExisting(parentID))
		{
			_core->_aabbEntityManager.bindAabbEntity(customAabbID, parentID, AabbParentType::MODEL_ENTITY, position, size, raycastResponsive, collisionResponsive);
		}
		else
		{
			Logger::throwError("Tried to bind AABB entity with ID \"" + customAabbID + "\" to non-existing model entity with ID \"" + parentID + "\"");
		}
	}
}

void FabiEngine3D::aabbEntity_bindToBillboardEntity(const string& parentID, bool raycastResponsive, bool collisionResponsive, const string& customAabbID)
{
	if (customAabbID.empty()) // Use parent ID
	{
		if (_core->_billboardEntityManager.isExisting(parentID))
		{
			_core->_aabbEntityManager.bindAabbEntity(parentID, parentID, AabbParentType::BILLBOARD_ENTITY, Vec3(0.0f), Vec3(0.0f), raycastResponsive, collisionResponsive);
		}
		else
		{
			Logger::throwError("Tried to bind AABB entity to non-existing billboard entity with ID \"" + parentID + "\"");
		}
	}
	else // Use custom ID
	{
		if (_core->_billboardEntityManager.isExisting(parentID))
		{
			_core->_aabbEntityManager.bindAabbEntity(customAabbID, parentID, AabbParentType::BILLBOARD_ENTITY, Vec3(0.0f), Vec3(0.0f), raycastResponsive, collisionResponsive);
		}
		else
		{
			Logger::throwError("Tried to bind AABB entity with ID \"" + customAabbID + "\" to non-existing billboard entity with ID \"" + parentID + "\"");
		}
	}
}

void FabiEngine3D::aabbEntity_deleteAll()
{
	_core->_aabbEntityManager.deleteAllEntities();
}

void FabiEngine3D::aabbEntity_delete(const string& ID)
{
	_core->_aabbEntityManager.deleteEntity(ID);
}

void FabiEngine3D::aabbEntity_setVisible(const string& ID, bool isVisible)
{
	_core->_aabbEntityManager.getEntity(ID)->setVisible(isVisible);
}

void FabiEngine3D::aabbEntity_setRaycastResponsive(const string& ID, bool responsive)
{
	_core->_aabbEntityManager.getEntity(ID)->setRaycastResponsive(responsive);
}

void FabiEngine3D::aabbEntity_setCollisionResponsive(const string& ID, bool responsive)
{
	_core->_aabbEntityManager.getEntity(ID)->setCollisionResponsive(responsive);
}

void FabiEngine3D::aabbEntity_setPosition(const string& ID, Vec3 position, bool noLocal)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "" || noLocal) // Standalone entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setTranslation(position);
	}
	else // Bound entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setLocalTranslation(position);
	}
}

void FabiEngine3D::aabbEntity_move(const string& ID, Vec3 factor, bool noLocal)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "" || noLocal) // Standalone entity
	{
		_core->_aabbEntityManager.getEntity(ID)->translate(factor);
	}
	else // Bound entity
	{
		_core->_aabbEntityManager.getEntity(ID)->translate(factor);
	}
}

void FabiEngine3D::aabbEntity_scale(const string& ID, Vec3 factor, bool noLocal)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "" || noLocal) // Standalone entity
	{
		_core->_aabbEntityManager.getEntity(ID)->scale(factor);
	}
	else // Bound entity
	{
		_core->_aabbEntityManager.getEntity(ID)->scale(factor);
	}
}

void FabiEngine3D::aabbEntity_setSize(const string& ID, Vec3 size, bool noLocal)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "" || noLocal) // Standalone entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setScaling(size);
	}
	else // Bound entity
	{
		_core->_aabbEntityManager.getEntity(ID)->setLocalScaling(size);
	}
}

const Vec3 FabiEngine3D::aabbEntity_getPosition(const string& ID, bool noLocal)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "" || noLocal) // Standalone entity
	{
		return _core->_aabbEntityManager.getEntity(ID)->getTranslation();
	}
	else // Bound entity
	{
		return _core->_aabbEntityManager.getEntity(ID)->getLocalTranslation();
	}
}

const Vec3 FabiEngine3D::aabbEntity_getSize(const string& ID, bool noLocal)
{
	if (_core->_aabbEntityManager.getEntity(ID)->getParentID() == "" || noLocal) // Standalone entity
	{
		return _core->_aabbEntityManager.getEntity(ID)->getScaling();
	}
	else // Bound entity
	{
		return _core->_aabbEntityManager.getEntity(ID)->getLocalScaling();
	}
}

const bool FabiEngine3D::aabbEntity_isRaycastResponsive(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->isRaycastResponsive();
}

const bool FabiEngine3D::aabbEntity_isCollisionResponsive(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->isCollisionResponsive();
}

const bool FabiEngine3D::aabbEntity_isExisting(const string& ID)
{
	return _core->_aabbEntityManager.isExisting(ID);
}

const bool FabiEngine3D::aabbEntity_isVisible(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::aabbEntity_hasParent(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->hasParent();
}

const vector<string> FabiEngine3D::aabbEntity_getBoundIDs(const string& parentID, bool modelEntity, bool billboardEntity)
{
	vector<string> IDs;

	// Iterate through AABB entities
	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		// Check if AABB has parent
		if (entity->hasParent())
		{
			// Check if parent matches
			if (parentID == entity->getParentID() && (
				(entity->getParentType() == AabbParentType::MODEL_ENTITY && modelEntity) ||
				(entity->getParentType() == AabbParentType::BILLBOARD_ENTITY && billboardEntity)))
			{
				IDs.push_back(entity->getID());
			}
		}
	}

	return IDs;
}

const vector<string> FabiEngine3D::aabbEntity_getAllIDs()
{
	vector<string> IDs;

	for (const auto& [keyID, entity] : _core->_aabbEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const string& FabiEngine3D::aabbEntity_getParentID(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getParentID();
}

const AabbParentType FabiEngine3D::aabbEntity_getParentType(const string& ID)
{
	return _core->_aabbEntityManager.getEntity(ID)->getParentType();
}