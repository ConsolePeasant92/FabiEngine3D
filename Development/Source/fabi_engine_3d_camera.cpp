#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::camera_load(float fov, float nearZ, float farZ, Vec3 startPosition, float yaw, float pitch)
{
	_core->_camera.reset();
	_core->_camera.setPosition(startPosition);
	_core->_camera.setFOV(fov);
	_core->_camera.setYaw(yaw);
	_core->_camera.setPitch(pitch);
	_core->_camera.setNearZ(nearZ);
	_core->_camera.setFarZ(farZ);
}

void FabiEngine3D::camera_enableLookatView()
{
	_core->_camera.enableLookatView();
}

void FabiEngine3D::camera_disableLookatView()
{
	_core->_camera.disableLookatView();
}

void FabiEngine3D::camera_enableFirstPersonView()
{
	_core->_camera.enableFirstPersonView();
}

void FabiEngine3D::camera_disableFirstPersonView()
{
	_core->_camera.disableFirstPersonView();
}

void FabiEngine3D::camera_translateFollowX(float speed)
{
	_core->_camera.translateFollowX(speed);
}

void FabiEngine3D::camera_translateFollowZY(float speed)
{
	_core->_camera.translateFollowZY(speed);
}

void FabiEngine3D::camera_translateFollowZ(float speed)
{
	_core->_camera.translateFollowZ(speed);
}

void FabiEngine3D::camera_translate(Vec3 translation)
{
	_core->_camera.translate(translation);
}

void FabiEngine3D::camera_setPosition(Vec3 position)
{
	_core->_camera.setPosition(position);
}

void FabiEngine3D::camera_setLookatPosition(Vec3 position)
{
	_core->_camera.setLookatPosition(position);
}

void FabiEngine3D::camera_lockYaw()
{
	_core->_camera.lockYaw();
}

void FabiEngine3D::camera_unlockYaw()
{
	_core->_camera.unlockYaw();
}

void FabiEngine3D::camera_lockPitch()
{
	_core->_camera.lockPitch();
}

void FabiEngine3D::camera_unlockPitch()
{
	_core->_camera.unlockPitch();
}

void FabiEngine3D::camera_setFOV(float fov)
{
	_core->_camera.setFOV(fov);
}

void FabiEngine3D::camera_setMouseSensitivity(float speed)
{
	_core->_camera.setMouseSensitivity(speed);
}

void FabiEngine3D::camera_setYaw(float yaw)
{
	_core->_camera.setYaw(yaw);
}

void FabiEngine3D::camera_setPitch(float pitch)
{
	_core->_camera.setPitch(pitch);
}

void FabiEngine3D::camera_setNearDistance(float nearZ)
{
	_core->_camera.setNearZ(nearZ);
}

void FabiEngine3D::camera_setFarDistance(float farZ)
{
	_core->_camera.setFarZ(farZ);
}

void FabiEngine3D::camera_setMaxPitch(float pitch)
{
	_core->_camera.setMaxPitch(pitch);
}

const float FabiEngine3D::camera_getYaw()
{
	return _core->_camera.getYaw();
}

const float FabiEngine3D::camera_getPitch()
{
	return _core->_camera.getPitch();
}

const float FabiEngine3D::camera_getNearDistance()
{
	return _core->_camera.getNearZ();
}

const float FabiEngine3D::camera_getFarDistance()
{
	return _core->_camera.getFarZ();
}

const float FabiEngine3D::camera_getMouseOffset()
{
	return _core->_camera.getMouseOffset();
}

const float FabiEngine3D::camera_getMaxPitch()
{
	return _core->_camera.getMaxPitch();
}

const float FabiEngine3D::camera_getFOV()
{
	return _core->_camera.getFOV();
}

const float FabiEngine3D::getAspectRatio()
{
	return _core->_camera.getAspectRatio();
}

const float FabiEngine3D::camera_getMouseSensitivity()
{
	return _core->_camera.getMouseSensitivity();
}

const Vec3 FabiEngine3D::camera_getPosition()
{
	return _core->_camera.getPosition();
}

const Vec3 FabiEngine3D::camera_getLookatPosition()
{
	return _core->_camera.getLookatPosition();
}

const bool FabiEngine3D::camera_isLookatViewEnabled()
{
	return _core->_camera.isLookatViewEnabled();
}

const bool FabiEngine3D::camera_isFirstPersonViewEnabled()
{
	return _core->_camera.isFirstPersonViewEnabled();
}