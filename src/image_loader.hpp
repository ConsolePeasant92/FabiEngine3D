#pragma once

#include "image.hpp"

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

using std::vector;
using std::string;
using std::unordered_map;
using std::shared_ptr;

class ImageLoader final
{
public:
	void cacheImage(const string & filePath, bool isCrucial);
	void cacheImages(const vector<string> & filePaths, bool isCrucial);
	void clearImageCache(const string & filePath);
	void clearImagesCache();

	const shared_ptr<Image> getImage(const string & filePath);

private:
	shared_ptr<Image> _getImage(const string & filePath) const;

	unordered_map<string, shared_ptr<Image>> _cache = {};
};