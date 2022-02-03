#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <SDL.h>

using std::istringstream;

Config::Config()
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto filePath = string(rootPath + "config.fe3d");

	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	_monitorSize.x = DM.w;
	_monitorSize.y = DM.h;

	if(Tools::isFileExisting(filePath))
	{
		auto file = ifstream(filePath);
		if(!file)
		{
			Logger::throwError("Cannot load `config.fe3d`");
		}

		_processOption(file, _windowSizeMultiplier, "window_size");
		_processOption(file, _isWindowFullscreen, "window_fullscreen");
		_processOption(file, _isWindowBorderless, "window_borderless");
		_processOption(file, _windowTitle, "window_title");

		if((_windowSizeMultiplier < 0.0f) || (_windowSizeMultiplier > 1.0f))
		{
			Logger::throwError("Configuration file @ option `window_size`: must be between 0.0 and 1.0");
		}

		_windowSize.x = static_cast<int>(static_cast<float>(_monitorSize.x) * _windowSizeMultiplier);
		_windowSize.y = static_cast<int>(static_cast<float>(_monitorSize.y) * _windowSizeMultiplier);
		_viewportSize.x = static_cast<int>(static_cast<float>(_windowSize.x));
		_viewportSize.y = static_cast<int>(static_cast<float>(_windowSize.y));
		_viewportPosition.x = 0;
		_viewportPosition.y = 0;

		_isApplicationExported = true;
	}
	else
	{
		_windowSizeMultiplier = DEFAULT_WINDOW_SIZE_MULTIPLIER;
		_isWindowFullscreen = false;
		_isWindowBorderless = false;
		_windowSize.x = static_cast<int>(static_cast<float>(_monitorSize.x) * _windowSizeMultiplier);
		_windowSize.y = static_cast<int>(static_cast<float>(_monitorSize.y) * _windowSizeMultiplier);
		_viewportSize.x = static_cast<int>(static_cast<float>(_windowSize.x) * VIEWPORT_SIZE_MULTIPLIER.x);
		_viewportSize.y = static_cast<int>(static_cast<float>(_windowSize.y) * VIEWPORT_SIZE_MULTIPLIER.y);
		_viewportPosition.x = static_cast<int>(static_cast<float>(_windowSize.x) * VIEWPORT_POSITION_MULTIPLIER.x);
		_viewportPosition.y = static_cast<int>(static_cast<float>(_windowSize.y) * VIEWPORT_POSITION_MULTIPLIER.y);

		_isApplicationExported = false;
	}
}

void Config::_processOption(ifstream& file, string& option, const string& name)
{
	string line;
	string field;
	string equals;

	getline(file, line);

	istringstream iss(line);

	iss
		>> field
		>> equals;

	if(field == name)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + name + "`: invalid option field");
	}
}

void Config::_processOption(ifstream& file, float& option, const string& name)
{
	string line;
	string field;
	string equals;

	getline(file, line);

	istringstream iss(line);

	iss
		>> field
		>> equals;

	if(field == name)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + name + "`: invalid option field");
	}
}

void Config::_processOption(ifstream& file, int& option, const string& name)
{
	string line;
	string field;
	string equals;

	getline(file, line);

	istringstream iss(line);

	iss
		>> field
		>> equals;

	if(field == name)
	{
		iss >> option;
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + name + "`: invalid option field");
	}
}

void Config::_processOption(ifstream& file, bool& option, const string& name)
{
	string line;
	string field;
	string equals;
	string value;

	getline(file, line);

	istringstream iss(line);

	iss
		>> field
		>> equals
		>> value;

	if(field == name)
	{
		if(value == "true")
		{
			option = true;
		}
		else if(value == "false")
		{
			option = false;
		}
		else
		{
			Logger::throwError("Configuration file @ option `" + name + "`: invalid boolean value");
		}
	}
	else
	{
		Logger::throwError("Configuration file @ option `" + name + "`: invalid option field");
	}
}

const string& Config::getWindowTitle() const
{
	return _windowTitle;
}

const ivec2& Config::getMonitorSize() const
{
	return _monitorSize;
}

const ivec2& Config::getWindowSize() const
{
	return _windowSize;
}

const ivec2& Config::getViewportPosition() const
{
	return _viewportPosition;
}

const float Config::getWindowSizeMultiplier() const
{
	return _windowSizeMultiplier;
}

const ivec2& Config::getViewportSize() const
{
	return _viewportSize;
}

const bool Config::isWindowFullscreen() const
{
	return _isWindowFullscreen;
}

const bool Config::isWindowBorderless() const
{
	return _isWindowBorderless;
}

const bool Config::isApplicationExported() const
{
	return _isApplicationExported;
}