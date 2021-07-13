#include "audio_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <algorithm>

const vector<string> AudioEditor::getAllAudioPathsFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("AudioEditor::getAllAudioPathsFromFile() --> no current project loaded!");
	}

	// Clear names list from previous loads
	_loadedAudioIDs.clear();

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\audio.fe3d";

	// Check if audio file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;
		vector<string> audioPaths;

		// Read model data
		while (std::getline(file, line))
		{
			// Temporary values
			string audioID, audioPath;
			std::istringstream iss(line);

			// Extract from file
			iss >> audioID >> audioPath;

			// Perform empty string & space conversions
			audioPath = (audioPath == "?") ? "" : audioPath;
			std::replace(audioPath.begin(), audioPath.end(), '?', ' ');

			// Save file path
			audioPaths.push_back(audioPath);
		}

		// Close file
		file.close();

		return audioPaths;
	}
	else
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"audio.fe3d\" missing!");
	}

	return {};
}

void AudioEditor::loadAudioEntitiesFromFile()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("AudioEditor::loadAudioEntitiesFromFile() --> no current project loaded!");
	}

	// Clear names list from previous loads
	_loadedAudioIDs.clear();

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\audio.fe3d";

	// Check if audio file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		std::ifstream file(filePath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string audioID, audioPath;

			// For file extraction
			std::istringstream iss(line);

			// Extract from file
			iss >> audioID >> audioPath;

			// Perform empty string & space conversions
			audioPath = (audioPath == "?") ? "" : audioPath;
			std::replace(audioPath.begin(), audioPath.end(), '?', ' ');

			// Add audio ID
			_loadedAudioIDs.push_back(audioID);
			_fe3d.soundEntity_add(audioID, audioPath);
		}

		// Close file
		file.close();

		// Logging
		Logger::throwInfo("Audio data from project \"" + _currentProjectID + "\" loaded!");
	}
	else
	{
		Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"audio.fe3d\" missing!");
	}
}

void AudioEditor::saveAudioEntitiesToFile()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return;
	}

	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("AudioEditor::saveAudioEntitiesToFile() --> no current project loaded!");
	}

	// Create or overwrite audio file
	std::ofstream file;
	file.open(_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\data\\audio.fe3d");

	// Write audio data into file
	for (const auto& audioID : _loadedAudioIDs)
	{
		// Retrieve all values
		auto audioPath = _fe3d.soundEntity_getFilePath(audioID);

		// Perform empty string & space conversions
		audioPath = (audioPath == "") ? "?" : audioPath;
		std::replace(audioPath.begin(), audioPath.end(), ' ', '?');

		// Export data
		file << audioID << " " << audioPath << std::endl;
	}

	// Close file
	file.close();

	// Logging
	Logger::throwInfo("Audio data from project \"" + _currentProjectID + "\" saved!");
}