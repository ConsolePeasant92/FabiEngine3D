#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::text_isExisting(const string& ID) const
{
	return _core->_textEntityManager.isExisting(ID);
}

const bool FabiEngine3D::text_isVisible(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->isVisible();
}

const fvec2 FabiEngine3D::text_getPosition(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getPosition();
}

const float FabiEngine3D::text_getRotation(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getRotation();
}

const float FabiEngine3D::text_getTransparency(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getTransparency();
}

const fvec2 FabiEngine3D::text_getSize(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getSize();
}

const fvec2 FabiEngine3D::text_getMinPosition(const string& ID) const
{
	return  _core->_textEntityManager.getEntity(ID)->getMinPosition();
}

const fvec2 FabiEngine3D::text_getMaxPosition(const string& ID) const
{
	return  _core->_textEntityManager.getEntity(ID)->getMaxPosition();
}

const fvec3 FabiEngine3D::text_getColor(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getColor();
}

const string& FabiEngine3D::text_getTextContent(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getTextContent();
}

const vector<string> FabiEngine3D::text_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_textEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const string& FabiEngine3D::text_getFontPath(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getFontPath();
}