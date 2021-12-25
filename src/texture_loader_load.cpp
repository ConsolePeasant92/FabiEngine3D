#include "texture_loader.hpp"
#include "logger.hpp"

#include <future>

using std::future;
using std::launch;

const TextureID TextureLoader::load2dTexture(const string& filePath, bool isMipmapped, bool isAnisotropic)
{
	BEGIN:;
	auto cacheIterator = _2dTextureCache.find(filePath);

	if(cacheIterator != _2dTextureCache.end())
	{
		return cacheIterator->second;
	}

	auto loadedSurface = _loadSurface(filePath);

	if(loadedSurface == nullptr)
	{
		Logger::throwWarning("Cannot load image: \"" + filePath + "\"!");
		return 0;
	}
	else
	{
		// Load OpenGL texture
		auto loadedTexture = _convertInto2dTexture(loadedSurface, filePath, isMipmapped, isAnisotropic);

		// Memory management
		SDL_FreeSurface(loadedSurface);

		// Check texture status
		if(loadedTexture == 0)
		{
			return 0;
		}
		else
		{
			// Cache texture
			_2dTextureCache.insert(make_pair(filePath, loadedTexture));

			// Return cached texture
			goto BEGIN;
		}
	}
}

const TextureID TextureLoader::load3dTexture(const array<string, 6>& filePaths)
{
	BEGIN:;
	auto cacheIterator = _3dTextureCache.find(filePaths);

	if(cacheIterator != _3dTextureCache.end())
	{
		return cacheIterator->second;
	}

	vector<future<SDL_Surface*>> threads;
	array<SDL_Surface*, 6> loadedSurfaces = {};

	for(size_t i = 0; i < filePaths.size(); i++)
	{
		threads.push_back(async(launch::async, &TextureLoader::_loadSurface, this, filePaths[i]));
	}

	for(size_t i = 0; i < threads.size(); i++)
	{
		// Save loaded surface
		loadedSurfaces[i] = threads[i].get();

		// Error logging
		if((loadedSurfaces[i] == nullptr) && !filePaths[i].empty())
		{
			Logger::throwWarning("Cannot load image: \"" + filePaths[i] + "\"!");
		}
	}

	TextureID loadedTexture = _convertInto3dTexture(loadedSurfaces, filePaths);

	for(const auto& surface : loadedSurfaces)
	{
		// Only if memory is present
		if(surface != nullptr)
		{
			SDL_FreeSurface(surface);
		}
	}

	if(loadedTexture == 0)
	{
		return 0;
	}
	else
	{
		// Cache texture
		_3dTextureCache.insert(make_pair(filePaths, loadedTexture));

		// Return cached texture
		goto BEGIN;
	}
}

const vector<float>* TextureLoader::loadBitmap(const string& filePath)
{
	BEGIN:;
	auto cacheIterator = _bitmapCache.find(filePath);

	if(cacheIterator != _bitmapCache.end())
	{
		return &cacheIterator->second;
	}

	auto loadedBitmap = _loadBitmap(filePath);

	if(loadedBitmap.empty())
	{
		Logger::throwWarning("Cannot load bitmap: \"" + filePath + "\"!");
		return nullptr;
	}
	else
	{
		// Cache bitmap
		_bitmapCache.insert(make_pair(filePath, loadedBitmap));

		// Logging
		Logger::throwInfo("Loaded bitmap: \"" + filePath + "\"");

		// Return cached bitmap
		goto BEGIN;
	}
}

const TextureID TextureLoader::load2dTexture(const string& textContent, const string& fontPath)
{
	BEGIN:;
	TTF_Font* font = nullptr;

	auto textCacheIterator = _textCache.find(make_pair(textContent, fontPath));

	if(textCacheIterator != _textCache.end())
	{
		return textCacheIterator->second;
	}

	auto fontCacheIterator = _fontCache.find(fontPath);

	if(fontCacheIterator == _fontCache.end())
	{
		// Load font
		font = _loadFont(fontPath);

		// Check font status
		if(font == nullptr)
		{
			Logger::throwWarning("Cannot load font: \"" + fontPath + "\"!");
			return 0;
		}
		else
		{
			// Cache font
			_fontCache.insert(make_pair(fontPath, font));

			// Logging
			Logger::throwInfo("Loaded font: \"" + fontPath + "\"");
		}
	}
	else
	{
		font = fontCacheIterator->second;
	}

	TextureID loadedTexture = _convertInto2dTexture(font, textContent);

	if(loadedTexture == 0)
	{
		return 0;
	}
	else
	{
		// Cache texture
		_textCache.insert(make_pair(make_pair(textContent, fontPath), loadedTexture));

		// Return cached texture
		goto BEGIN;
	}
}