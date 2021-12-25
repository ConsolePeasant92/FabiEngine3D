#include "sky_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <fstream>

using std::ofstream;

const bool SkyEditor::saveToFile() const
{
	if(!_isEditorLoaded)
	{
		return false;
	}

	if(_currentProjectID.empty())
	{
		Logger::throwError("SkyEditor::saveToFile");
	}

	ofstream file(Tools::getRootDirectoryPath() + "projects\\" + _currentProjectID + "\\data\\sky.fe3d");

	for(const auto& skyID : _loadedSkyIDs)
	{
		// Values
		auto cubeMapPaths = _fe3d.sky_getCubeMapPaths(skyID);
		auto rotation = _fe3d.sky_getRotation(skyID);
		auto lightness = _fe3d.sky_getLightness(skyID);
		auto color = _fe3d.sky_getColor(skyID);

		// Iterate through paths
		for(auto& cubeMapPath : cubeMapPaths)
		{
			// Convert to short path
			cubeMapPath = string(cubeMapPath.empty() ? "" : cubeMapPath.substr(string("projects\\" + _currentProjectID + "\\").size()));

			// Convert empty string
			cubeMapPath = (cubeMapPath.empty()) ? "?" : cubeMapPath;

			// Convert spaces
			replace(cubeMapPath.begin(), cubeMapPath.end(), ' ', '?');
		}

		// Write ID to file
		file << skyID << " ";

		// Write paths to file
		for(const auto& cubeMapPath : cubeMapPaths)
		{
			file << cubeMapPath << " ";
		}

		// Write data to file
		file <<
			rotation << " " <<
			lightness << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << endl;
	}

	file.close();

	Logger::throwInfo("Sky data saved!");

	return true;
}