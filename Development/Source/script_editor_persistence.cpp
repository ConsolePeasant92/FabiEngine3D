#include "script_editor.hpp"
#include "logger.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>

using std::ifstream;
using std::ofstream;
using std::istringstream;

bool ScriptEditor::loadScriptFiles(bool isLoggingEnabled)
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("ScriptEditor::loadScriptsFromFile() ---> no current project loaded!");
	}

	// Clear last script
	_script.reset();

	// Compose directory path
	const string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\scripts\\");

	// Warning checking
	if (!_fe3d.misc_isDirectoryExisting(directoryPath))
	{
		if (isLoggingEnabled)
		{
			Logger::throwWarning("Project \"" + _currentProjectID + "\" corrupted: \"scripts\\\" directory missing!");
		}
		return false;
	}

	// Retrieve all filenames in the scripts directory
	for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
	{
		// Extract filename
		string fileName = string(entry.path().u8string());
		fileName.erase(0, directoryPath.size());

		// Check if script file exists & check if the file extension is correct
		if (_fe3d.misc_isFileExisting(directoryPath + fileName) && (fileName.substr(fileName.size() - 5, 5) == ".fe3d"))
		{
			// Load script file
			ifstream file(directoryPath + fileName);
			string line;

			// Add software script file to script
			string scriptName = fileName.substr(0, fileName.size() - 5); // No file extension
			_script.addScriptFile(scriptName);

			// Extract cursor indices
			unsigned int cursorLineIndex, cursorCharIndex;
			getline(file, line);
			istringstream iss(line);
			iss >> cursorLineIndex >> cursorCharIndex;
			_script.getScriptFile(scriptName)->setCursorLineIndex(cursorLineIndex);
			_script.getScriptFile(scriptName)->setCursorCharIndex(cursorCharIndex);

			// Extract script lines
			unsigned int lineIndex = 0;
			while (getline(file, line))
			{
				// Add new scriptline
				_script.getScriptFile(scriptName)->insertNewLine(lineIndex, line);
				lineIndex++;
			}

			// Close file
			file.close();
		}
	}

	// Logging
	if (isLoggingEnabled)
	{
		Logger::throwInfo("Script data from project \"" + _currentProjectID + "\" loaded!");
	}

	// Miscellaneous
	_isScriptLoadedFromFile = true;

	// Return
	return true;
}

bool ScriptEditor::saveScriptFiles()
{
	// Editor must be loaded
	if (!_isEditorLoaded)
	{
		return false;
	}

	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("ScriptEditor::saveScriptsToFile() ---> no current project loaded!");
	}

	// Compose directory path
	const string directoryPath = (_fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" :
		("projects\\" + _currentProjectID)) + "\\scripts\\");

	// Delete all text files containing deleted scripts
	for (const auto& scriptName : _scriptFileNamesToDelete)
	{
		const string finalPath = directoryPath + scriptName + ".fe3d";

		// Check if file exists
		if (_fe3d.misc_isFileExisting(finalPath))
		{
			DeleteFile(LPCSTR(finalPath.c_str()));
		}
	}
	_scriptFileNamesToDelete.clear();

	// Write every script to a text file
	for (const auto& scriptName : _script.getAllScriptFileIDs())
	{
		// Create or overwrite script file
		ofstream file;
		file.open(directoryPath + scriptName + ".fe3d");

		// Write cursor indices to file
		file << _script.getScriptFile(scriptName)->getCursorLineIndex() << " " << _script.getScriptFile(scriptName)->getCursorCharIndex() << endl;

		// Write every scriptline to file
		for (unsigned int lineIndex = 0; lineIndex < _script.getScriptFile(scriptName)->getLineCount(); lineIndex++)
		{
			file << _script.getScriptFile(scriptName)->getLineText(lineIndex) << endl;
		}

		// Close file
		file.close();
	}

	// Logging
	Logger::throwInfo("Script data from project \"" + _currentProjectID + "\" saved!");

	// Return
	return true;
}