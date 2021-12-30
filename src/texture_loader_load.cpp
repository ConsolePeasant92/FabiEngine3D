#include "texture_loader.hpp"
#include "logger.hpp"

#include <future>

using std::future;
using std::launch;

const TextureID TextureLoader::load2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic)
{
BEGIN:;
	auto cacheIterator = _2dTextureCache.find(filePath);

	if (cacheIterator != _2dTextureCache.end())
	{
		return cacheIterator->second;
	}

	auto loadedSurface = _loadTextureData(filePath);

	if (loadedSurface == nullptr)
	{
		Logger::throwWarning("Cannot load image: \"" + filePath + "\"!");
		return 0;
	}
	else
	{
		auto loadedTexture = _create2dTexture(loadedSurface, filePath, isMipmapped, isAnisotropic);

		if (loadedTexture == 0)
		{
			return 0;
		}
		else
		{
			_2dTextureCache.insert(make_pair(filePath, loadedTexture));

			goto BEGIN;
		}
	}
}

const TextureID TextureLoader::load3dTexture(const array<string, 6>& filePaths)
{
BEGIN:;
	auto cacheIterator = _3dTextureCache.find(filePaths);

	if (cacheIterator != _3dTextureCache.end())
	{
		return cacheIterator->second;
	}

	vector<future<shared_ptr<TextureData>>> threads;
	array<shared_ptr<TextureData>, 6> loadedSurfaces = {};

	for (size_t i = 0; i < filePaths.size(); i++)
	{
		threads.push_back(async(launch::async, &TextureLoader::_loadTextureData, this, filePaths[i]));
	}

	for (size_t i = 0; i < threads.size(); i++)
	{
		loadedSurfaces[i] = threads[i].get();

		if ((loadedSurfaces[i] == nullptr) && !filePaths[i].empty())
		{
			Logger::throwWarning("Cannot load image: \"" + filePaths[i] + "\"!");
		}
	}

	TextureID loadedTexture = _create3dTexture(loadedSurfaces, filePaths);

	if (loadedTexture == 0)
	{
		return 0;
	}
	else
	{
		_3dTextureCache.insert(make_pair(filePaths, loadedTexture));

		goto BEGIN;
	}
}

const vector<float>* TextureLoader::loadBitmap(const string& filePath)
{
BEGIN:;
	auto cacheIterator = _bitmapCache.find(filePath);

	if (cacheIterator != _bitmapCache.end())
	{
		return &cacheIterator->second;
	}

	auto loadedBitmap = _loadBitmapData(filePath);

	if (loadedBitmap.empty())
	{
		Logger::throwWarning("Cannot load bitmap: \"" + filePath + "\"!");
		return nullptr;
	}
	else
	{
		_bitmapCache.insert(make_pair(filePath, loadedBitmap));

		Logger::throwInfo("Loaded bitmap: \"" + filePath + "\"");

		goto BEGIN;
	}
}