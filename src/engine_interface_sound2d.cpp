#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::sound2d_create(const string& id, const string& audioPath)
{
	_core->getSound2dManager()->createSound(id, audioPath);
}

void EngineInterface::sound2d_delete(const string& id)
{
	for(unsigned int i = 0; i < _core->getSound2dPlayer()->getStartedSoundCount(id); i++)
	{
		_core->getSound2dPlayer()->stopSound(id, 0);
	}

	_core->getSound2dManager()->deleteSound(id);
}

void EngineInterface::sound2d_start(const string& id, int playCount)
{
	_core->getSound2dPlayer()->startSound(id, playCount);
}

void EngineInterface::sound2d_pause(const string& id, unsigned int index)
{
	_core->getSound2dPlayer()->pauseSound(id, index);
}

void EngineInterface::sound2d_resume(const string& id, unsigned int index)
{
	_core->getSound2dPlayer()->resumeSound(id, index);
}

void EngineInterface::sound2d_stop(const string& id, unsigned int index)
{
	_core->getSound2dPlayer()->stopSound(id, index);
}

void EngineInterface::sound2d_setVolume(const string& id, unsigned int index, float value)
{
	_core->getSound2dPlayer()->setSoundVolume(id, index, value);
}

void EngineInterface::sound2d_setSpeed(const string& id, unsigned int index, float value)
{
	_core->getSound2dPlayer()->setSoundSpeed(id, index, value);
}

void EngineInterface::sound2d_setPitch(const string& id, unsigned int index, float value)
{
	_core->getSound2dPlayer()->setSoundPitch(id, index, value);
}

const vector<string> EngineInterface::sound2d_getIds() const
{
	vector<string> result;

	for(const auto& [key, sound] : _core->getSound2dManager()->getSounds())
	{
		result.push_back(sound->getId());
	}

	return result;
}

const string& EngineInterface::sound2d_getAudioPath(const string& id) const
{
	return _core->getSound2dManager()->getSound(id)->getAudioPath();
}

const bool EngineInterface::sound2d_isExisting(const string& id) const
{
	return _core->getSound2dManager()->isSoundExisting(id);
}

const bool EngineInterface::sound2d_isStarted(const string& id, unsigned int index) const
{
	return _core->getSound2dPlayer()->isSoundStarted(id, index);
}

const bool EngineInterface::sound2d_isPaused(const string& id, unsigned int index) const
{
	return _core->getSound2dPlayer()->isSoundPaused(id, index);
}

const bool EngineInterface::sound2d_isChannelAvailable() const
{
	return _core->getSound2dPlayer()->isChannelAvailable();
}

const bool EngineInterface::sound2d_isDeviceConnected() const
{
	return _core->getSound2dPlayer()->isDeviceConnected();
}

const float EngineInterface::sound2d_getVolume(const string& id, unsigned int index) const
{
	return _core->getSound2dPlayer()->getSoundVolume(id, index);
}

const float EngineInterface::sound2d_getSpeed(const string& id, unsigned int index) const
{
	return _core->getSound2dPlayer()->getSoundSpeed(id, index);
}

const float EngineInterface::sound2d_getPitch(const string& id, unsigned int index) const
{
	return _core->getSound2dPlayer()->getSoundPitch(id, index);
}

const unsigned int EngineInterface::sound2d_getStartedCount(const string& id) const
{
	return _core->getSound2dPlayer()->getStartedSoundCount(id);
}