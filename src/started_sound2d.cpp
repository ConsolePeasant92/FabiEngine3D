#include "started_sound2d.hpp"

#include <algorithm>

using std::clamp;

void StartedSound2D::setPaused(bool value)
{
	_isPaused = value;
}

void StartedSound2D::setPlayCount(int value)
{
	_playCount = value;
}

void StartedSound2D::setVolume(float value)
{
	_volume = clamp(value, 0.0f, 1.0f);
}

void StartedSound2D::setLeftIntensity(float value)
{
	_leftIntensity = clamp(value, 0.0f, 1.0f);
}

void StartedSound2D::setRightIntensity(float value)
{
	_rightIntensity = clamp(value, 0.0f, 1.0f);
}

void StartedSound2D::setHandle(HWAVEOUT value)
{
	_handle = value;
}

void StartedSound2D::setHeader(PWAVEHDR value)
{
	_header = value;
}

const float StartedSound2D::getVolume() const
{
	return _volume;
}

const int StartedSound2D::getPlayCount() const
{
	return _playCount;
}

const bool StartedSound2D::isPaused() const
{
	return _isPaused;
}

const HWAVEOUT StartedSound2D::getHandle() const
{
	return _handle;
}

const float StartedSound2D::getLeftIntensity() const
{
	return _leftIntensity;
}

const float StartedSound2D::getRightIntensity() const
{
	return _rightIntensity;
}

const PWAVEHDR StartedSound2D::getHeader() const
{
	return _header;
}