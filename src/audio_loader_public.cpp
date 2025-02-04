#include "audio_loader.hpp"
#include "logger.hpp"

#include <future>
#include <set>

using std::set;
using std::future;
using std::launch;
using std::future_status;
using std::chrono::seconds;

const shared_ptr<Audio> AudioLoader::getAudio(const string & filePath)
{
	const auto iterator = _cache.find(filePath);

	if(iterator != _cache.end())
	{
		return iterator->second;
	}

	auto loadedAudio = _getAudio(filePath);

	if(loadedAudio == nullptr)
	{
		Logger::throwWarning("Cannot load audio: \"" + filePath + "\"");

		return nullptr;
	}

	_cache.insert({filePath, loadedAudio});

	Logger::throwInfo("Loaded audio: \"" + filePath + "\"");

	return loadedAudio;
}

void AudioLoader::cacheAudio(const string & filePath, bool isCrucial)
{
	const auto iterator = _cache.find(filePath);

	if(iterator != _cache.end())
	{
		return;
	}

	auto loadedAudio = _getAudio(filePath);

	if(loadedAudio == nullptr)
	{
		if(isCrucial)
		{
			Logger::throwError("Cannot load audio: \"" + filePath + "\"");
		}
		else
		{
			Logger::throwWarning("Cannot load audio: \"" + filePath + "\"");
		}

		return;
	}

	_cache.insert({filePath, loadedAudio});

	Logger::throwInfo("Loaded audio: \"" + filePath + "\"");
}

void AudioLoader::cacheAudios(const vector<string> & filePaths, bool isCrucial)
{
	vector<future<shared_ptr<Audio>>> threads = {};
	vector<string> threadFilePaths = {};
	vector<bool> threadStatuses = {};
	int finishedThreadCount = 0;

	const auto tempFilePaths = set<string>(filePaths.begin(), filePaths.end());
	const auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for(const auto & filePath : uniqueFilePaths)
	{
		if(_cache.find(filePath) == _cache.end())
		{
			threads.push_back(async(launch::async, &AudioLoader::_getAudio, this, filePath));
			threadFilePaths.push_back(filePath);
			threadStatuses.push_back(false);
		}
	}

	while(finishedThreadCount != threadStatuses.size())
	{
		for(int index = 0; index < static_cast<int>(threadStatuses.size()); index++)
		{
			if(!threadStatuses[index])
			{
				if(threads[index].wait_for(seconds(0)) == future_status::ready)
				{
					threadStatuses[index] = true;
					finishedThreadCount++;

					const auto loadedAudio = threads[index].get();

					if(loadedAudio == nullptr)
					{
						if(isCrucial)
						{
							Logger::throwError("Cannot load audio: \"" + threadFilePaths[index] + "\"");
						}
						else
						{
							Logger::throwWarning("Cannot load audio: \"" + threadFilePaths[index] + "\"");
						}

						continue;
					}

					_cache.insert({threadFilePaths[index], loadedAudio});

					Logger::throwInfo("Loaded audio: \"" + threadFilePaths[index] + "\"");
				}
			}
		}
	}
}

void AudioLoader::clearAudioCache(const string & filePath)
{
	if(_cache.find(filePath) != _cache.end())
	{
		_cache.erase(filePath);
	}
}

void AudioLoader::clearAudiosCache()
{
	_cache.clear();
}