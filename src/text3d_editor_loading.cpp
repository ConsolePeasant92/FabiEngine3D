#include "text3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

const vector<string> Text3dEditor::getImagePathsFromFile() const
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\text3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text3d.fe3d` does not exist");
		return {};
	}

	vector<string> imagePaths;
	string line;
	while(getline(file, line))
	{
		string textId;
		string fontMapPath;

		istringstream iss(line);

		iss
			>> textId
			>> fontMapPath;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		if(!fontMapPath.empty())
		{
			if(!Configuration::getInst().isApplicationExported())
			{
				fontMapPath = ("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
			}

			imagePaths.push_back(fontMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool Text3dEditor::loadEntitiesFromFile()
{
	if(!Configuration::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Configuration::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = (rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\text3d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text3d.fe3d` does not exist");

		return false;
	}

	string line;
	while(getline(file, line))
	{
		string textId;
		string fontMapPath;
		fvec2 size;
		fvec3 color;
		float lightness;
		float opacity;
		float minTextureAlpha;
		int rotationOrder;
		bool isFacingCameraHorizontally;
		bool isFacingCameraVertically;
		bool isHorizontallyFlipped;
		bool isVerticallyFlipped;
		bool isReflected;
		bool isShadowed;
		bool isBright;
		bool hasAabb;

		istringstream iss(line);

		iss
			>> textId
			>> fontMapPath
			>> size.x
			>> size.y
			>> color.r
			>> color.g
			>> color.b
			>> isFacingCameraHorizontally
			>> isFacingCameraVertically
			>> isHorizontallyFlipped
			>> isVerticallyFlipped
			>> isReflected
			>> isShadowed
			>> lightness
			>> isBright
			>> opacity
			>> minTextureAlpha
			>> rotationOrder
			>> hasAabb;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		if(!Configuration::getInst().isApplicationExported())
		{
			fontMapPath = ("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
		}

		_fe3d->text3d_create(textId, fontMapPath, false);

		if(_fe3d->text3d_isExisting(textId))
		{
			_loadedEntityIds.push_back(textId);
			sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

			_fe3d->text3d_setVisible(textId, false);
			_fe3d->text3d_setSize(textId, size);
			_fe3d->text3d_setColor(textId, color);
			_fe3d->text3d_setLightness(textId, lightness);
			_fe3d->text3d_setFacingCameraHorizontally(textId, isFacingCameraHorizontally);
			_fe3d->text3d_setFacingCameraVertically(textId, isFacingCameraVertically);
			_fe3d->text3d_setHorizontallyFlipped(textId, isHorizontallyFlipped);
			_fe3d->text3d_setVerticallyFlipped(textId, isVerticallyFlipped);
			_fe3d->text3d_setShadowed(textId, isShadowed);
			_fe3d->text3d_setReflected(textId, isReflected);
			_fe3d->text3d_setBright(textId, isBright);
			_fe3d->text3d_setOpacity(textId, opacity);
			_fe3d->text3d_setMinTextureAlpha(textId, minTextureAlpha);
			_fe3d->text3d_setRotationOrder(textId, DirectionOrderType(rotationOrder));

			if(hasAabb)
			{
				_fe3d->aabb_create(textId, false);
				_fe3d->aabb_setParentId(textId, textId);
				_fe3d->aabb_setParentType(textId, AabbParentType::TEXT);
			}
		}
	}

	file.close();

	Logger::throwInfo("Text3D editor data loaded");

	return true;
}