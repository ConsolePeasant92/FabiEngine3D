#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::pointlight_isExisting(const string& ID) const
{
	return _core->_pointlightEntityManager.isExisting(ID);
}

const  bool FabiEngine3D::pointlight_isVisible(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->isVisible();
}

const PointlightShape FabiEngine3D::pointlight_getShape(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->getShape();
}

const fvec3 FabiEngine3D::pointlight_getPosition(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->getPosition();
}

const fvec3 FabiEngine3D::pointlight_getRadius(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->getRadius();
}

const fvec3 FabiEngine3D::pointlight_getColor(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->getColor();
}

const float FabiEngine3D::pointlight_getIntensity(const string& ID) const
{
	return _core->_pointlightEntityManager.getEntity(ID)->getIntensity();
}

const vector<string> FabiEngine3D::pointlight_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_pointlightEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}