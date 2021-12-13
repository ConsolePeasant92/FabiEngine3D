#include "animation2d.hpp"
#include "logger.hpp"

Animation2d::Animation2d(const string& ID)
	:
	_ID(ID)
{

}

const string& Animation2d::getID() const
{
	return _ID;
}

const string& Animation2d::getPreviewTexturePath() const
{
	return _previewTexturePath;
}

const int Animation2d::getTimesToPlay() const
{
	return _timesToPlay;
}

const unsigned int Animation2d::getPassedFrames() const
{
	return _passedFrames;
}

const unsigned int Animation2d::getFramestep() const
{
	return _framestep;
}

const unsigned int Animation2d::getRowCount() const
{
	return _rowCount;
}

const unsigned int Animation2d::getColumnCount() const
{
	return _columnCount;
}

const unsigned int Animation2d::getRowIndex() const
{
	return _rowIndex;
}

const unsigned int Animation2d::getColumnIndex() const
{
	return _columnIndex;
}

const bool Animation2d::isPaused() const
{
	return _isPaused;
}

void Animation2d::setTimesToPlay(int value)
{
	_timesToPlay = value;
}

void Animation2d::setPaused(bool value)
{
	_isPaused = value;
}

void Animation2d::setRowIndex(unsigned int value)
{
	_rowIndex = value;
}

void Animation2d::setColumnIndex(unsigned int value)
{
	_columnIndex = value;
}

void Animation2d::setRowCount(unsigned int value)
{
	_rowCount = value;
}

void Animation2d::setColumnCount(unsigned int value)
{
	_columnCount = value;
}

void Animation2d::setFramestep(unsigned int value)
{
	_framestep = value;
}

void Animation2d::setPassedFrames(unsigned int value)
{
	_passedFrames = value;
}

void Animation2d::setPreviewTexturePath(const string& value)
{
	_previewTexturePath = value;
}