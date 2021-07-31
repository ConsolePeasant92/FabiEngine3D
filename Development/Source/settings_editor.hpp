#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class SettingsEditor final
{
public:
	SettingsEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	void loadDefaultSettings();
	bool loadSettingsFromFile();
	bool saveSettingsToFile();

	bool isLoaded();

private:
	void _loadGUI();
	void _unloadGUI();

	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	string _currentProjectID = "";

	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;

	bool _isEditorLoaded = false;
};