#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::reflection_create(const string& ID)
{
	_core->getReflectionEntityManager()->createEntity(ID);
}

void EngineInterface::reflection_deleteAll()
{
	_core->getReflectionEntityManager()->deleteEntities();
}

void EngineInterface::reflection_delete(const string& ID)
{
	_core->getReflectionEntityManager()->deleteEntity(ID);
}

void EngineInterface::reflection_setVisible(const string& ID, bool value)
{
	_core->getReflectionEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::reflection_setPosition(const string& ID, const fvec3& value)
{
	_core->getReflectionEntityManager()->getEntity(ID)->setPosition(value);
}

void EngineInterface::reflection_move(const string& ID, const fvec3& change)
{
	_core->getReflectionEntityManager()->getEntity(ID)->move(change);
}

void EngineInterface::reflection_moveTo(const string& ID, const fvec3& target, float speed)
{
	_core->getReflectionEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::reflection_capture(const string& ID)
{
	_core->getReflectionEntityManager()->getEntity(ID)->capture();
}

const vector<string> EngineInterface::reflection_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getReflectionEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const fvec3& EngineInterface::reflection_getPosition(const string& ID) const
{
	return _core->getReflectionEntityManager()->getEntity(ID)->getPosition();
}

const bool EngineInterface::reflection_isExisting(const string& ID) const
{
	return _core->getReflectionEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::reflection_isVisible(const string& ID) const
{
	return _core->getReflectionEntityManager()->getEntity(ID)->isVisible();
}