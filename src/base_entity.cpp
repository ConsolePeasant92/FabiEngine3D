#include "base_entity.hpp"
#include "logger.hpp"

BaseEntity::BaseEntity(const string& id)
	:
	_ID(id)
{
	if(id.empty())
	{
		Logger::throwError("BaseEntity::BaseEntity");
	}
}

void BaseEntity::setVisible(bool value)
{
	_isVisible = value;
}

const string& BaseEntity::getID() const
{
	return _ID;
}

const bool BaseEntity::isVisible() const
{
	return _isVisible;
}