#pragma once
#include "WaterEntity.hpp"

void WaterEntity::setColor(vec3 val)
{
	_color = val;
}

void WaterEntity::setDudvMap(GLuint val)
{
	_dudvMap = val;
}

void WaterEntity::setNormalMap(GLuint val)
{
	_normalMap = val;
}

void WaterEntity::setWaveValue(float val)
{
	_waveValue = val;
}

void WaterEntity::setTileRepeat(float val)
{
	_tileRepeat = val;
}

void WaterEntity::setWavingSpeed(float val)
{
	_wavingSpeed = val;
}

void WaterEntity::setTimeX(float val)
{
	_timeX = val;
}

void WaterEntity::setTimeZ(float val)
{
	_timeZ = val;
}

void WaterEntity::setShininess(float val)
{
	_shininess = val;
}

void WaterEntity::setWaving(bool val)
{
	_waving = val;
}

void WaterEntity::setRippling(bool val)
{
	_rippling = val;
}

void WaterEntity::setSurfaceHeight(float val)
{
	_surfaceHeight = val;
}

void WaterEntity::setTransparency(float val)
{
	_transparency = val;
}

const vec3 WaterEntity::getColor() const
{
	return _color;
}

const GLuint WaterEntity::getDudvMap() const
{
	return _dudvMap;
}

const GLuint WaterEntity::getNormalMap() const
{
	return _normalMap;
}

const float WaterEntity::getWaveValue() const
{
	return _waveValue;
}

const float WaterEntity::getTileRepeat() const
{
	return _tileRepeat;
}

const float WaterEntity::getWavingSpeed() const
{
	return _wavingSpeed;
}

const float WaterEntity::getTimeX() const
{
	return _timeX;
}

const float WaterEntity::getTimeZ() const
{
	return _timeZ;
}

const float WaterEntity::getShininess() const
{
	return _shininess;
}

const float WaterEntity::getSurfaceHeight() const
{
	return _surfaceHeight;
}

const float WaterEntity::getTransparency() const
{
	return _transparency;
}

const bool WaterEntity::isWaving() const
{
	return _waving;
}

const bool WaterEntity::isRippling() const
{
	return _rippling;
}
