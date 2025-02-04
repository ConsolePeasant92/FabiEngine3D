#include "sound3d_manager.hpp"

using std::make_shared;

void Sound3dManager::deleteSound3ds()
{
	_sound3ds.clear();
}

void Sound3dManager::deleteSound3d(const string & sound3dId)
{
	if(!isSound3dExisting(sound3dId))
	{
		abort();
	}

	_sound3ds.erase(sound3dId);
}

void Sound3dManager::inject(shared_ptr<AudioLoader> audioLoader)
{
	_audioLoader = audioLoader;
}

void Sound3dManager::inject(shared_ptr<WaveBufferCache> waveBufferCache)
{
	_waveBufferCache = waveBufferCache;
}

void Sound3dManager::update()
{
	for(const auto & [sound3dId, sound3d] : _sound3ds)
	{
		sound3d->updateTarget();
	}
}

void Sound3dManager::createSound3d(const string & sound3dId, const string & audioPath)
{
	if(isSound3dExisting(sound3dId))
	{
		abort();
	}

	const auto audio = _audioLoader->getAudio(audioPath);

	if(audio == nullptr)
	{
		return;
	}

	const auto sound3d = make_shared<Sound3d>(sound3dId);

	auto waveBuffer = _waveBufferCache->getBuffer(audioPath);

	if(waveBuffer == nullptr)
	{
		const auto audio = _audioLoader->getAudio(audioPath);

		if(audio == nullptr)
		{
			return;
		}

		waveBuffer = make_shared<WaveBuffer>(audio);

		_waveBufferCache->storeBuffer(audioPath, waveBuffer);
	}

	sound3d->setWaveBuffer(waveBuffer);
	sound3d->setAudioPath(audioPath);

	_sound3ds.insert({sound3dId, sound3d});
}

const bool Sound3dManager::isSound3dExisting(const string & sound3dId) const
{
	return (_sound3ds.find(sound3dId) != _sound3ds.end());
}

const bool Sound3dManager::isSound3dsExisting() const
{
	return !_sound3ds.empty();
}

const unordered_map<string, shared_ptr<Sound3d>> & Sound3dManager::getSound3ds() const
{
	return _sound3ds;
}

const shared_ptr<Sound3d> Sound3dManager::getSound3d(const string & sound3dId) const
{
	const auto iterator = _sound3ds.find(sound3dId);

	if(iterator == _sound3ds.end())
	{
		abort();
	}

	return iterator->second;
}