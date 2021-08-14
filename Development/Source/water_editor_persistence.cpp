#include "water_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::istringstream;

const vector<string> WaterEditor::getAllWaterTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("WaterEditor::getAllWaterTexturePathsFromFile");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\water.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"water.fe3d\" file missing!");
		return {};
	}

	// Load water file
	ifstream file(filePath);

	// Read water data
	vector<string> texturePaths;
	string line;
	while (getline(file, line))
	{
		// Temporary values
		string waterID, dudvMapPath, normalMapPath, displacementMapPath;
		istringstream iss(line);

		// Load base data
		iss >>
			waterID >>
			dudvMapPath >>
			normalMapPath >>
			displacementMapPath;

		// Perform empty string & space conversions
		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);
		replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(displacementMapPath.begin(), displacementMapPath.end(), '?', ' ');

		// Save file paths
		if (!dudvMapPath.empty())
		{
			texturePaths.push_back(dudvMapPath);
		}
		if (!normalMapPath.empty())
		{
			texturePaths.push_back(normalMapPath);
		}
		if (!displacementMapPath.empty())
		{
			texturePaths.push_back(displacementMapPath);
		}
	}

	// Close file
	file.close();

	// Return
	return texturePaths;
}

bool WaterEditor::loadWaterEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("WaterEditor::loadWaterEntitiesFromFile");
	}

	// Clear IDs from previous loads
	_loadedWaterIDs.clear();

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\water.fe3d";

	// Warning checking
	if (!_fe3d.misc_isFileExisting(filePath))
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"water.fe3d\" file missing!");
		return false;
	}

	// Load water file
	ifstream file(filePath);

	// Read water data
	string line;
	while (getline(file, line))
	{
		istringstream iss(line);

		// Values
		string waterID, dudvMapPath, normalMapPath, displacementMapPath;
		Vec3 color, position;
		Vec2 speed;
		float size, uvRepeat, waveHeight, transparency, specularFactor, specularIntensity;
		unsigned int quality;
		bool isWaving, isRippling, isSpecularLighted, isReflective, isRefractive;

		// Load base data
		iss >>
			waterID >>
			dudvMapPath >>
			normalMapPath >>
			displacementMapPath >>
			isWaving >>
			isRippling >>
			isSpecularLighted >>
			isReflective >>
			isRefractive >>
			color.r >>
			color.g >>
			color.b >>
			size >>
			position.x >>
			position.y >>
			position.z >>
			uvRepeat >>
			waveHeight >>
			quality >>
			speed.x >>
			speed.y >>
			transparency >>
			specularFactor >>
			specularIntensity;

		// Perform empty string & space conversions
		dudvMapPath = (dudvMapPath == "?" ? "" : dudvMapPath);
		normalMapPath = (normalMapPath == "?" ? "" : normalMapPath);
		displacementMapPath = (displacementMapPath == "?" ? "" : displacementMapPath);
		replace(dudvMapPath.begin(), dudvMapPath.end(), '?', ' ');
		replace(normalMapPath.begin(), normalMapPath.end(), '?', ' ');
		replace(displacementMapPath.begin(), displacementMapPath.end(), '?', ' ');

		// Create water
		_fe3d.waterEntity_create(waterID);

		// Check if water creation went well
		if (_fe3d.waterEntity_isExisting(waterID))
		{
			// Add water ID
			_loadedWaterIDs.push_back(waterID);

			// DUDV map
			if (dudvMapPath != "")
			{
				_fe3d.waterEntity_setDudvMap(waterID, dudvMapPath);
			}

			// Normal map
			if (normalMapPath != "")
			{
				_fe3d.waterEntity_setNormalMap(waterID, normalMapPath);
			}

			// Displacement map
			if (displacementMapPath != "")
			{
				_fe3d.waterEntity_setDisplacementMap(waterID, displacementMapPath);
			}

			// Set properties
			_fe3d.waterEntity_setPosition(waterID, position);
			_fe3d.waterEntity_setSize(waterID, size);
			_fe3d.waterEntity_setWaving(waterID, isWaving);
			_fe3d.waterEntity_setRippling(waterID, isRippling);
			_fe3d.waterEntity_setSpecularLighted(waterID, isSpecularLighted);
			_fe3d.waterEntity_setReflective(waterID, isReflective);
			_fe3d.waterEntity_setRefractive(waterID, isRefractive);
			_fe3d.waterEntity_setWaveHeight(waterID, waveHeight);
			_fe3d.waterEntity_setQuality(waterID, static_cast<WaterQuality>(quality));
			_fe3d.waterEntity_setSpecularLightingFactor(waterID, specularFactor);
			_fe3d.waterEntity_setSpecularLightingIntensity(waterID, specularIntensity);
			_fe3d.waterEntity_setTransparency(waterID, transparency);
			_fe3d.waterEntity_setColor(waterID, color);
			_fe3d.waterEntity_setUvRepeat(waterID, uvRepeat);
			_fe3d.waterEntity_setSpeed(waterID, speed);
		}
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Water data from project \"" + _currentProjectID + "\" loaded!");

	// Return
	return true;
}

bool WaterEditor::saveWaterEntitiesToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if (_currentProjectID.empty())
	{
		Logger::throwError("WaterEditor::saveWaterEntitiesToFile");
	}

	// Compose file path
	const string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\data\\water.fe3d";

	// Load water file
	ofstream file(filePath);

	// Write water data
	for (const auto& waterID : _loadedWaterIDs)
	{
		// Values
		auto dudvMapPath = _fe3d.waterEntity_getDudvMapPath(waterID);
		auto normalMapPath = _fe3d.waterEntity_getNormalMapPath(waterID);
		auto displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath(waterID);
		auto color = _fe3d.waterEntity_getColor(waterID);
		auto position = _fe3d.waterEntity_getPosition(waterID);
		auto speed = _fe3d.waterEntity_getSpeed(waterID);
		auto size = _fe3d.waterEntity_getSize(waterID);
		auto uvRepeat = _fe3d.waterEntity_getUvRepeat(waterID);
		auto waveHeight = _fe3d.waterEntity_getWaveHeight(waterID);
		auto transparency = _fe3d.waterEntity_getTransparency(waterID);
		auto specularFactor = _fe3d.waterEntity_getSpecularLightingFactor(waterID);
		auto specularIntensity = _fe3d.waterEntity_getSpecularLightingIntensity(waterID);
		auto quality = static_cast<unsigned int>(_fe3d.waterEntity_getQuality(waterID));
		auto isWaving = _fe3d.waterEntity_isWaving(waterID);
		auto isRippling = _fe3d.waterEntity_isRippling(waterID);
		auto isSpecularLighted = _fe3d.waterEntity_isSpecularLighted(waterID);
		auto isReflective = _fe3d.waterEntity_isReflective(waterID);
		auto isRefractive = _fe3d.waterEntity_isRefractive(waterID);

		// Perform empty string & space conversions
		dudvMapPath = (dudvMapPath.empty() ? "?" : dudvMapPath);
		normalMapPath = (normalMapPath.empty() ? "?" : normalMapPath);
		displacementMapPath = (displacementMapPath.empty() ? "?" : displacementMapPath);
		replace(dudvMapPath.begin(), dudvMapPath.end(), ' ', '?');
		replace(normalMapPath.begin(), normalMapPath.end(), ' ', '?');
		replace(displacementMapPath.begin(), displacementMapPath.end(), ' ', '?');

		// Write data to file
		file <<
			waterID << " " <<
			dudvMapPath << " " <<
			normalMapPath << " " <<
			displacementMapPath << " " <<
			isWaving << " " <<
			isRippling << " " <<
			isSpecularLighted << " " <<
			isReflective << " " <<
			isRefractive << " " <<
			color.r << " " <<
			color.g << " " <<
			color.b << " " <<
			size << " " <<
			position.x << " " <<
			position.y << " " <<
			position.z << " " <<
			uvRepeat << " " <<
			waveHeight << " " <<
			quality << " " <<
			speed.x << " " <<
			speed.y << " " <<
			transparency << " " <<
			specularFactor << " " <<
			specularIntensity << endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Water data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}