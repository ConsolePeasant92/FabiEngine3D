#include "mesh_loader.hpp"
#include "mesh_loader.hpp"
#include "mesh_loader.hpp"
#include "logger.hpp"

#include <future>
#include <set>

using std::set;
using std::future;
using std::launch;

const vector<shared_ptr<MeshPart>>* MeshLoader::loadMesh(const string& filePath)
{
	BEGIN:;
	auto cacheIterator = _meshCache.find(filePath);

	if(cacheIterator != _meshCache.end())
	{
		return &cacheIterator->second;
	}

	auto returnValue = _loadMesh(filePath);

	if(returnValue.second.empty())
	{
		Logger::throwWarning(returnValue.first);
		return nullptr;
	}
	else
	{
		_meshCache.insert(make_pair(filePath, returnValue.second));

		Logger::throwInfo("Loaded mesh: \"" + filePath + "\"");

		goto BEGIN;
	}
}

void MeshLoader::cacheMesh(const string& filePath)
{
	loadMesh(filePath);
}

void MeshLoader::cacheMeshes(const vector<string>& meshPaths)
{
	vector<future<pair<string, vector<shared_ptr<MeshPart>>>>> threads;
	vector<bool> threadStatuses;

	auto tempFilePaths = set<string>(meshPaths.begin(), meshPaths.end());
	auto uniqueFilePaths = vector<string>(tempFilePaths.begin(), tempFilePaths.end());

	for(const auto& filePath : uniqueFilePaths)
	{
		if(_meshCache.find(filePath) == _meshCache.end())
		{
			threads.push_back(async(launch::async, &MeshLoader::_loadMesh, this, filePath));
			threadStatuses.push_back(false);
		}
		else
		{
			threadStatuses.push_back(true);
		}
	}

	for(size_t i = 0; i < threadStatuses.size(); i++)
	{
		if(!threadStatuses[i])
		{
			auto returnValue = threads[i].get();

			if(returnValue.second.empty())
			{
				Logger::throwWarning(returnValue.first);
			}
			else
			{
				_meshCache[uniqueFilePaths[i]] = returnValue.second;

				Logger::throwInfo("Loaded mesh: \"" + uniqueFilePaths[i] + "\"");
			}
		}
	}
}

void MeshLoader::clearMeshCache(const string& filePath)
{
	if(_meshCache.find(filePath) != _meshCache.end())
	{
		_meshCache.erase(filePath);
	}
}

void MeshLoader::clearMeshesCache()
{
	_meshCache.clear();
}