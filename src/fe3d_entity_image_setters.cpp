#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::image_deleteAll()
{
	_core->_imageEntityManager.deleteAllEntities();
}

void FabiEngine3D::image_create(const string& ID, bool isCentered)
{
	_core->_imageEntityManager.createEntity(ID, isCentered);
}

void FabiEngine3D::image_delete(const string& ID)
{
	_core->_imageEntityManager.deleteEntity(ID);
}

void FabiEngine3D::image_setVisible(const string& ID, bool value)
{
	_core->_imageEntityManager.getEntity(ID)->setVisible(value);
}

void FabiEngine3D::image_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_imageEntityManager.getEntity(ID)->setDiffuseMap(0);
		_core->_imageEntityManager.getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		_core->_imageEntityManager.getEntity(ID)->setDiffuseMap(_core->_textureLoader.loadTexture2D(value, false, false));
		_core->_imageEntityManager.getEntity(ID)->setDiffuseMapPath(value);
	}
}

void FabiEngine3D::image_setPosition(const string& ID, fvec2 position)
{
	_core->_imageEntityManager.getEntity(ID)->setPosition(position);
}

void FabiEngine3D::image_setRotation(const string& ID, float rotation)
{
	_core->_imageEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::image_setSize(const string& ID, fvec2 size)
{
	_core->_imageEntityManager.getEntity(ID)->setSize(size);
}

void FabiEngine3D::image_move(const string& ID, fvec2 position)
{
	_core->_imageEntityManager.getEntity(ID)->move(position);
}

void FabiEngine3D::image_rotate(const string& ID, float rotation)
{
	_core->_imageEntityManager.getEntity(ID)->rotate(rotation);
}

void FabiEngine3D::image_scale(const string& ID, fvec2 size)
{
	_core->_imageEntityManager.getEntity(ID)->scale(size);
}

void FabiEngine3D::image_moveTo(const string& ID, fvec2 target, float speed)
{
	_core->_imageEntityManager.getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::image_rotateTo(const string& ID, float target, float speed)
{
	_core->_imageEntityManager.getEntity(ID)->rotateTo(target, speed);
}

void FabiEngine3D::image_scaleTo(const string& ID, fvec2 target, float speed)
{
	_core->_imageEntityManager.getEntity(ID)->scaleTo(target, speed);
}

void FabiEngine3D::image_setColor(const string& ID, fvec3 value)
{
	_core->_imageEntityManager.getEntity(ID)->setColor(value);
}

void FabiEngine3D::image_setTransparency(const string& ID, float value)
{
	_core->_imageEntityManager.getEntity(ID)->setTransparency(value);
}

void FabiEngine3D::image_setMinPosition(const string& ID, fvec2 value)
{
	_core->_imageEntityManager.getEntity(ID)->setMinPosition(value);
}

void FabiEngine3D::image_setMaxPosition(const string& ID, fvec2 value)
{
	_core->_imageEntityManager.getEntity(ID)->setMaxPosition(value);
}

void FabiEngine3D::image_startSpriteAnimation(const string& ID, int loops)
{
	auto entity = _core->_imageEntityManager.getEntity(ID);

	if(entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to start sprite animation on image with ID \"" + ID + "\": animation already started!");
		return;
	}
	if(loops < -1)
	{
		Logger::throwWarning("Tried to start sprite animation on image with ID \"" + ID + "\": invalid loops amount!");
		return;
	}

	entity->startSpriteAnimation(loops);
}

void FabiEngine3D::image_pauseSpriteAnimation(const string& ID)
{
	auto entity = _core->_imageEntityManager.getEntity(ID);

	if(!entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to pause sprite animation on image with ID \"" + ID + "\" animation not started!");
		return;
	}
	else if(entity->isSpriteAnimationPaused())
	{
		Logger::throwWarning("Tried to pause sprite animation on image with ID \"" + ID + "\" animation already paused!");
		return;
	}

	entity->pauseSpriteAnimation();
}

void FabiEngine3D::image_resumeSpriteAnimation(const string& ID)
{
	auto entity = _core->_imageEntityManager.getEntity(ID);

	if(!entity->isSpriteAnimationPaused())
	{
		Logger::throwWarning("Tried to resume sprite animation on image with ID \"" + ID + "\" animation not paused!");
		return;
	}

	entity->resumeSpriteAnimation();
}

void FabiEngine3D::image_stopSpriteAnimation(const string& ID)
{
	auto entity = _core->_imageEntityManager.getEntity(ID);

	if(!entity->isSpriteAnimationStarted())
	{
		Logger::throwWarning("Tried to stop sprite animation on image with ID \"" + ID + "\" animation not started!");
		return;
	}

	entity->stopSpriteAnimationAnimation();
}

void FabiEngine3D::image_setSpriteAnimationRowCount(const string& ID, int value)
{
	_core->_imageEntityManager.getEntity(ID)->setTotalSpriteAnimationRowCount(value);
}

void FabiEngine3D::image_setSpriteAnimationColumnCount(const string& ID, int value)
{
	_core->_imageEntityManager.getEntity(ID)->setTotalSpriteAnimationColumnCount(value);
}

void FabiEngine3D::image_setSpriteAnimationFramestep(const string& ID, int value)
{
	_core->_imageEntityManager.getEntity(ID)->setSpriteAnimationFramestep(value);
}

void FabiEngine3D::image_setWireframed(const string& ID, bool value)
{
	_core->_imageEntityManager.getEntity(ID)->setWireframed(value);
}

void FabiEngine3D::image_setWireframeColor(const string& ID, fvec3 value)
{
	_core->_imageEntityManager.getEntity(ID)->setWireframeColor(value);
}

void FabiEngine3D::image_setSpriteAnimationRowIndex(const string& ID, unsigned int value)
{
	_core->_imageEntityManager.getEntity(ID)->setSpriteAnimationRowIndex(value);
}

void FabiEngine3D::image_setSpriteAnimationColumnIndex(const string& ID, unsigned int value)
{
	_core->_imageEntityManager.getEntity(ID)->setSpriteAnimationColumnIndex(value);
}

void FabiEngine3D::image_setMirroredHorizontally(const string& ID, bool value)
{
	_core->_imageEntityManager.getEntity(ID)->setMirroredHorizontally(value);
}

void FabiEngine3D::image_setMirroredVertically(const string& ID, bool value)
{
	_core->_imageEntityManager.getEntity(ID)->setMirroredVertically(value);
}