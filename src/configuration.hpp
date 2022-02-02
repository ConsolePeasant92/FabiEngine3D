#pragma once

#include "mathematics.hpp"

#include <fstream>
#include <sstream>
#include <string>

using std::string;
using std::ifstream;

class Config final
{
public:
	Config(Config const&) = delete;

	void operator=(Config const&) = delete;

	const string& getWindowTitle() const;

	const ivec2& getMonitorSize() const;
	const ivec2& getWindowSize()	const;
	const ivec2& getViewportSize() const;
	const ivec2& getViewportPosition() const;

	const float getWindowSizeMultiplier() const;

	const bool isWindowFullscreen()	const;
	const bool isWindowBorderless()	const;
	const bool isApplicationExported() const;

	static Config& getInst()
	{
		static Config instance;
		return instance;
	}

private:
	Config();

	void _processOption(ifstream& file, string& option, const string& name);
	void _processOption(ifstream& file, float& option, const string& name);
	void _processOption(ifstream& file, int& option, const string& name);
	void _processOption(ifstream& file, bool& option, const string& name);

	string _windowTitle = "";

	ivec2 _monitorSize = ivec2(0);
	ivec2 _windowSize = ivec2(0);
	ivec2 _viewportSize = ivec2(0);
	ivec2 _viewportPosition = ivec2(0);

	float _windowSizeMultiplier = 0.0f;

	bool _isWindowFullscreen = false;
	bool _isWindowBorderless = false;
	bool _isApplicationExported = false;

	static inline const fvec2 VIEWPORT_POSITION_MULTIPLIER = fvec2(0.125f, 0.2f);
	static inline const fvec2 VIEWPORT_SIZE_MULTIPLIER = fvec2(0.75f, 0.75f);

	static inline constexpr float DEFAULT_WINDOW_SIZE_MULTIPLIER = 0.9f;
};