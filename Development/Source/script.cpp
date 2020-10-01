#include "script.hpp"
#include "logger.hpp"

Script::Script(FabiEngine3D& fe3d) :
	_fe3d(fe3d)
{

}

void Script::addScriptFile(const string& ID)
{
	// Check if non-existent
	for (auto& file : _scriptFiles)
	{
		if(file->getID() == ID)
		{
			_fe3d.logger_throwError("Could not add script file, already exists: " + ID);
		}
	}

	// Add new script file
	_scriptFiles.push_back(make_shared<ScriptFile>(_fe3d, ID));
}

void Script::removeScriptFile(const string& ID)
{
	int index = 0;

	for (auto& file : _scriptFiles)
	{
		if (file->getID() == ID)
		{
			_scriptFiles.erase(_scriptFiles.begin() + index);
			return;
		}
		index++;
	}

	_fe3d.logger_throwError("Could not remove script file with ID: " + ID);
}

void Script::reset()
{
	_scriptFiles.clear();
}

int Script::getScriptFileCount()
{
	return _scriptFiles.size();
}

bool Script::isScriptFileExisting(const string& ID)
{
	for (auto& file : _scriptFiles)
	{
		if (file->getID() == ID)
		{
			return true;
		}
	}

	return false;
}

shared_ptr<ScriptFile> Script::getScriptFile(const string& ID)
{
	for (auto& file : _scriptFiles)
	{
		if (file->getID() == ID)
		{
			return file;
		}
	}

	_fe3d.logger_throwError("Could not find script file with ID: " + ID);
}

const vector<string> Script::getAllScriptFileIDs()
{
	vector<string> result;

	for (auto& file : _scriptFiles)
	{
		result.push_back(file->getID());
	}

	return result;
}