#include "sound3d_player.hpp"

using std::future_status;
using std::chrono::seconds;

void Sound3dPlayer::inject(shared_ptr<Sound3dManager> sound3dManager)
{
	_sound3dManager = sound3dManager;
}

void Sound3dPlayer::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

const bool Sound3dPlayer::isDeviceConnected() const
{
	return (waveOutGetNumDevs() > 0);
}

const bool Sound3dPlayer::isSound3dStarted(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if(_startedSound3ds.find(sound3dId) == _startedSound3ds.end())
	{
		return false;
	}

	return (index < _startedSound3ds.at(sound3dId).size());
}

const bool Sound3dPlayer::isSound3dPaused(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if(!isSound3dStarted(sound3dId, index))
	{
		abort();
	}

	return _startedSound3ds.at(sound3dId)[index]->isPaused();
}

const float Sound3dPlayer::getSound3dVolume(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if(!isSound3dStarted(sound3dId, index))
	{
		abort();
	}

	return _startedSound3ds.at(sound3dId)[index]->getVolume();
}

const float Sound3dPlayer::getSound3dLeftIntensity(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if(!isSound3dStarted(sound3dId, index))
	{
		abort();
	}

	return _startedSound3ds.at(sound3dId)[index]->getLeftIntensity();
}

const float Sound3dPlayer::getSound3dRightIntensity(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if(!isSound3dStarted(sound3dId, index))
	{
		abort();
	}

	return _startedSound3ds.at(sound3dId)[index]->getRightIntensity();
}

const int Sound3dPlayer::getSound3dPlayCount(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if(!isSound3dStarted(sound3dId, index))
	{
		abort();
	}

	return _startedSound3ds.at(sound3dId)[index]->getPlayCount();
}

const int Sound3dPlayer::getStartedSound3dCount(const string & sound3dId) const
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if(_startedSound3ds.find(sound3dId) == _startedSound3ds.end())
	{
		return 0;
	}

	return static_cast<int>(_startedSound3ds.at(sound3dId).size());
}


void Sound3dPlayer::_terminateSound3ds()
{
	for(const auto & [sound3dId, startedSound3ds] : _startedSound3ds)
	{
		for(int index = 0; index < static_cast<int>(startedSound3ds.size()); index++)
		{
			_terminateSound3d(sound3dId, 0);
		}
	}
}

void Sound3dPlayer::_terminateSound3d(const string & sound3dId, int index)
{
	if(!_volumeThreadQueue.empty())
	{
		if((sound3dId == _volumeThreadQueue.front().first) && (index == _volumeThreadQueue.front().second))
		{
			while(true)
			{
				if(_volumeThread.wait_for(seconds(0)) == future_status::ready)
				{
					break;
				}
			}
		}
	}

	delete[] _startedSound3ds.at(sound3dId)[index]->getHeader()->lpData;
	delete _startedSound3ds.at(sound3dId)[index]->getHeader();

	_startedSound3ds.at(sound3dId).erase(_startedSound3ds.at(sound3dId).begin() + index);

	if(_startedSound3ds.at(sound3dId).empty())
	{
		_startedSound3ds.erase(sound3dId);
	}
}

void Sound3dPlayer::_updateSamplesVolume(int originalSampleCount, int startedSampleCount, short * originalSamples, short * startedSamples, float volume, float leftIntensity, float rightIntensity)
{
	const auto startIndex = (originalSampleCount - startedSampleCount);

	for(int index = startIndex; index < originalSampleCount; index++)
	{
		if(((index + 1) % 2) == 0)
		{
			startedSamples[index - startIndex] = static_cast<short>(static_cast<float>(originalSamples[index]) * volume * rightIntensity);
		}
		else
		{
			startedSamples[index - startIndex] = static_cast<short>(static_cast<float>(originalSamples[index]) * volume * leftIntensity);
		}
	}
}

const float Sound3dPlayer::getSound3dCurrentTime(const string & sound3dId, int index) const
{
	if(!_sound3dManager->isSound3dExisting(sound3dId))
	{
		abort();
	}

	if(!isSound3dStarted(sound3dId, index))
	{
		abort();
	}

	auto currentTime = new MMTIME();

	currentTime->wType = TIME_BYTES;

	waveOutGetPosition(_startedSound3ds.at(sound3dId)[index]->getHandle(), currentTime, sizeof(MMTIME));

	const auto originalByteCount = _sound3dManager->getSound3d(sound3dId)->getWaveBuffer()->getHeader()->dwBufferLength;
	const auto startedByteCount = _startedSound3ds.at(sound3dId)[index]->getHeader()->dwBufferLength;
	const auto byteIndex = (currentTime->u.cb + (originalByteCount - startedByteCount));
	const auto result = fmodf((static_cast<float>(byteIndex) / static_cast<float>(originalByteCount)), 1.0f);

	delete currentTime;

	return result;
}