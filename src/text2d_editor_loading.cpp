#include "text2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ifstream;
using std::istringstream;

const vector<string> Text2dEditor::getImagePathsFromFile() const
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\text2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text2d.fe3d` does not exist");
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
			if(!Config::getInst().isApplicationExported())
			{
				fontMapPath = string("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
			}

			imagePaths.push_back(fontMapPath);
		}
	}

	file.close();

	return imagePaths;
}

const bool Text2dEditor::loadFromFile()
{
	if(!Config::getInst().isApplicationExported() && getCurrentProjectId().empty())
	{
		abort();
	}

	_loadedTextIds.clear();

	const auto isExported = Config::getInst().isApplicationExported();
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + getCurrentProjectId() + "\\")) + "data\\text2d.fe3d");

	auto file = ifstream(filePath);
	if(!file)
	{
		Logger::throwWarning("Project corrupted: file `text2d.fe3d` does not exist");
		return false;
	}

	string line;
	while(getline(file, line))
	{
		string textId;
		string fontMapPath;
		fvec3 color;
		float opacity;

		istringstream iss(line);

		iss
			>> textId
			>> fontMapPath
			>> color.r
			>> color.g
			>> color.b
			>> opacity;

		fontMapPath = (fontMapPath == "?") ? "" : fontMapPath;

		replace(fontMapPath.begin(), fontMapPath.end(), '?', ' ');

		if(!Config::getInst().isApplicationExported())
		{
			fontMapPath = string("projects\\" + getCurrentProjectId() + "\\" + fontMapPath);
		}

		_fe3d->text2d_create(textId, fontMapPath, true);

		if(_fe3d->text2d_isExisting(textId))
		{
			_loadedTextIds.push_back(textId);

			_fe3d->text2d_setVisible(textId, false);
			_fe3d->text2d_setPosition(textId, Tools::convertPositionRelativeToViewport(fvec2(0.0f)));
			_fe3d->text2d_setSize(textId, Tools::convertSizeRelativeToViewport(fvec2(TEXT_SIZE.x, (TEXT_SIZE.y * Tools::getWindowAspectRatio()))));
			_fe3d->text2d_setColor(textId, color);
			_fe3d->text2d_setOpacity(textId, opacity);
			_fe3d->text2d_setContent(textId, TEXT_CONTENT);
		}
	}

	file.close();

	Logger::throwInfo("Text2D editor data loaded");

	return true;
}