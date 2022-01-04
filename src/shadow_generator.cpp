#include "shadow_generator.hpp"
#include "render_bus.hpp"
#include "configuration.hpp"

using std::max;

void ShadowGenerator::update(RenderBus& renderBus)
{
	if(_isEnabled)
	{
		if(_passedFrames >= _interval)
		{
			_passedFrames = 0;

			generate(renderBus);
		}
		else
		{
			_passedFrames++;
		}
	}
}

void ShadowGenerator::generate(RenderBus& renderBus)
{
	auto newEyePosition = _eyePosition;
	auto newCenterPosition = _centerPosition;
	auto newSize = _size;
	auto newReach = _reach;
	auto newLightness = _lightness;
	auto newQuality = _quality;
	auto newEnabled = _isEnabled;

	if(_isFollowingCamera)
	{
		auto cameraPosition = renderBus.getCameraPosition();

		newEyePosition.x += cameraPosition.x;
		newEyePosition.z += cameraPosition.z;
		newCenterPosition.x += cameraPosition.x;
		newCenterPosition.z += cameraPosition.z;
	}

	renderBus.setShadowEyePosition(newEyePosition);
	renderBus.setShadowCenterPosition(newCenterPosition);
	renderBus.setShadowSize(newSize);
	renderBus.setShadowReach(newReach);
	renderBus.setShadowLightness(newLightness);
	renderBus.setShadowQuality(newQuality);
	renderBus.setShadowsEnabled(newEnabled);

	renderBus.setShadowMatrix(_createShadowMatrix(newEyePosition, newCenterPosition, newSize, newReach));
}

const mat44 ShadowGenerator::_createShadowMatrix(fvec3 eyePosition, fvec3 centerPosition, float size, float reach) const
{
	float left = -(size / 2.0f);
	float right = (size / 2.0f);
	float bottom = -(size / 2.0f);
	float top = (size / 2.0f);
	float near = NEAR_DISTANCE;
	float far = reach;

	auto viewMatrix = Math::createViewMatrix(eyePosition, centerPosition, fvec3(0.0f, 1.0f, 0.0f));
	auto projectionMatrix = Math::createOrthographicProjectionMatrix(left, right, bottom, top, near, far);

	return (projectionMatrix * viewMatrix);
}

void ShadowGenerator::setInterval(unsigned int value)
{
	_interval = value;
	_passedFrames = 0;
}

void ShadowGenerator::setEnabled(bool value)
{
	_isEnabled = value;
}

void ShadowGenerator::setFollowingCamera(bool value)
{
	_isFollowingCamera = value;
}

void ShadowGenerator::setEyePosition(fvec3 value)
{
	_eyePosition = value;
}

void ShadowGenerator::setCenterPosition(fvec3 value)
{
	_centerPosition = value;
}

void ShadowGenerator::setSize(float value)
{
	_size = value;
}

void ShadowGenerator::setReach(float value)
{
	_reach = value;
}

void ShadowGenerator::setLightness(float value)
{
	_lightness = value;
}

void ShadowGenerator::setQuality(unsigned int value)
{
	_quality = value;
}

const fvec3 ShadowGenerator::getEyePosition() const
{
	return _eyePosition;
}

const fvec3 ShadowGenerator::getCenterPosition() const
{
	return _centerPosition;
}

const float ShadowGenerator::getSize() const
{
	return _size;
}

const float ShadowGenerator::getReach() const
{
	return _reach;
}

const float ShadowGenerator::getLightness() const
{
	return _lightness;
}

const unsigned int ShadowGenerator::getQuality() const
{
	return _quality;
}

const unsigned int ShadowGenerator::getInterval() const
{
	return _interval;
}

const bool ShadowGenerator::isEnabled()
{
	return _isEnabled;
}

const bool ShadowGenerator::isFollowingCamera() const
{
	return _isFollowingCamera;
}