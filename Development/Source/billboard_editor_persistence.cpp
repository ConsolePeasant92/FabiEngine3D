#include "billboard_editor.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

const vector<string> BillboardEditor::getAllTexturePathsFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded --> BillboardEditor::getAllTexturePathsFromFile()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\billboard.fe3d";

	// Check if billboard file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Temporary values
		std::ifstream file(filePath);
		string line;
		vector<string> texturePaths;

		// Read billboard data
		while (std::getline(file, line))
		{
			// Temporary values
			string billboardID, diffuseMapPath, fontPath, textContent;
			Vec2 size;
			Vec3 color;
			float lightness;
			bool facingX, facingY, transparent, playing;
			int rows, columns, framestep;
			std::istringstream iss(line);

			// Extract data
			iss >>
				billboardID >>
				size.x >>
				size.y >>
				color.r >>
				color.g >>
				color.b >>
				facingX >>
				facingY >>
				diffuseMapPath;

			// Perform empty string & space conversions
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');

			// Save file paths
			if (!diffuseMapPath.empty())
			{
				texturePaths.push_back(diffuseMapPath);
			}
		}

		// Close file
		file.close();

		// Return
		return texturePaths;
	}
	else
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectName + "\" corrupted: billboard.fe3d missing!");
	}

	return {};
}

void BillboardEditor::loadBillboardEntitiesFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("No current project loaded --> BillboardEditor::loadBillboardEntitiesFromFile()");
	}

	// Clear names list from previous loads
	_billboardIDs.clear();

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\billboard.fe3d";

	// Check if billboard file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;

		// Read billboard data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string billboardID, diffuseMapPath, fontPath, textContent;
			Vec2 size;
			Vec3 color;
			float lightness;
			bool facingX, facingY, transparent, playing;
			int rows, columns, framestep;

			// For file extraction
			std::istringstream iss(line);

			// Extract from file
			iss >>
				billboardID >>
				size.x >>
				size.y >>
				color.r >>
				color.g >>
				color.b >>
				facingX >>
				facingY >>
				diffuseMapPath >>
				transparent >>
				fontPath >>
				textContent >>
				playing >>
				rows >>
				columns >>
				framestep >>
				lightness;

			// Perform empty string & space conversions
			diffuseMapPath = (diffuseMapPath == "?") ? "" : diffuseMapPath;
			fontPath = (fontPath == "?") ? "" : fontPath;
			textContent = (textContent == "?") ? "" : textContent;
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), '?', ' ');
			std::replace(fontPath.begin(), fontPath.end(), '?', ' ');
			std::replace(textContent.begin(), textContent.end(), '?', ' ');

			// Add billboard name
			_billboardIDs.push_back(billboardID);

			// Determine billboard type
			if (diffuseMapPath != "") // Textured billboard
			{
				_fe3d.billboardEntity_add(billboardID, diffuseMapPath, _billboardPosition, Vec3(0.0f), size, transparent, facingX, facingY, false);
				_fe3d.billboardEntity_setColor(billboardID, color);

				// Playing sprite animation
				if (playing)
				{
					_fe3d.billboardEntity_setAnimationFramestep(billboardID, framestep);
					_fe3d.billboardEntity_setAnimationRows(billboardID, rows);
					_fe3d.billboardEntity_setAnimationColumns(billboardID, columns);
					_fe3d.billboardEntity_playSpriteAnimation(billboardID, -1);
				}
			}
			else if (fontPath != "") // Text billboard
			{
				_fe3d.billboardEntity_add(billboardID, textContent, fontPath, color, _billboardPosition, Vec3(0.0f), size, facingX, facingY, false);
			}
			else // Colored billboard
			{
				_fe3d.billboardEntity_add(billboardID, color, _billboardPosition, Vec3(0.0f), size, facingX, facingY, false);
			}

			// Miscellaneous
			_fe3d.billboardEntity_setLightness(billboardID, lightness);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Billboard data from project \"" + _currentProjectName + "\" loaded!");
	}
	else
	{
		_fe3d.logger_throwWarning("Project \"" + _currentProjectName + "\" corrupted: billboard.fe3d missing!");
	}
}

void BillboardEditor::saveBillboardEntitiesToFile()
{
	if (_isEditorLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("No current project loaded --> BillboardEditor::saveBillboardEntitiesToFile()");
		}

		// Create or overwrite billboard file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "user\\projects\\" + _currentProjectName + "\\data\\billboard.fe3d");

		// Write billboard data into file
		for (auto& billboardID : _billboardIDs)
		{
			// Retrieve all values
			auto size = _fe3d.billboardEntity_getSize(billboardID);
			auto color = _fe3d.billboardEntity_getColor(billboardID);
			auto diffuseMapPath = _fe3d.billboardEntity_getDiffuseMapPath(billboardID);
			auto fontPath = _fe3d.billboardEntity_getFontPath(billboardID);
			auto textContent = _fe3d.billboardEntity_getTextContent(billboardID);
			auto isFacingX = _fe3d.billboardEntity_isFacingCameraX(billboardID);
			auto isFacingY = _fe3d.billboardEntity_isFacingCameraY(billboardID);
			auto isTransparent = _fe3d.billboardEntity_isTransparent(billboardID);
			auto isAnimated = _fe3d.billboardEntity_isAnimationPlaying(billboardID);
			auto animationRows = _fe3d.billboardEntity_getAnimationRows(billboardID);
			auto animationColumns = _fe3d.billboardEntity_getAnimationColumns(billboardID);
			auto animationFramestep = _fe3d.billboardEntity_getAnimationFramestep(billboardID);
			auto lightness = _fe3d.billboardEntity_getLightness(billboardID);

			// Perform empty string & space conversions
			diffuseMapPath = (diffuseMapPath == "") ? "?" : diffuseMapPath;
			fontPath = (fontPath == "") ? "?" : fontPath;
			textContent = (textContent == "") ? "?" : textContent;
			std::replace(diffuseMapPath.begin(), diffuseMapPath.end(), ' ', '?');
			std::replace(fontPath.begin(), fontPath.end(), ' ', '?');
			std::replace(textContent.begin(), textContent.end(), ' ', '?');

			// Export data
			file <<
				billboardID << " " <<
				size.x << " " <<
				size.y << " " <<
				color.r << " " <<
				color.g << " " <<
				color.b << " " <<
				isFacingX << " " <<
				isFacingY << " " <<
				diffuseMapPath << " " <<
				isTransparent << " " <<
				fontPath << " " <<
				textContent << " " <<
				isAnimated << " " <<
				animationRows << " " <<
				animationColumns << " " <<
				animationFramestep << " " <<
				lightness << std::endl;
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Billboard data from project \"" + _currentProjectName + "\" saved!");
	}
}