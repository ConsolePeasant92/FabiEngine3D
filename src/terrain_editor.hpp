#pragma once

#include "fe3d.hpp"
#include "gui_manager.hpp"

class TerrainEditor final
{
public:
	TerrainEditor(FabiEngine3D& fe3d, GuiManager& gui);

	// VOID
	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();

	// STRING
	const vector<string> getBitmapPathsFromFile() const;
	const vector<string> getTexturePathsFromFile() const;
	const vector<string>& getLoadedIDs();

	// BOOL
	const bool loadFromFile();
	const bool saveToFile() const;
	const bool isLoaded() const;

private:
	// VOID
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateDiffuseMapMenu();
	void _updateBlendMapMenu();
	void _updateNormalMapMenu();
	void _updateLightingMenu();
	void _updateMiscellaneousMenu();
	void _updateTerrainCreating();
	void _updateTerrainChoosing();
	void _updateTerrainDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	// STRING
	vector <string> _loadedTerrainIDs;
	string _currentProjectID = "";
	string _currentTerrainID = "";

	// FLOAT
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float CURSOR_SENSITIVITY = 0.025f;
	static inline const float INITIAL_CAMERA_YAW = 45.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	static inline const float GRID_Y_OFFSET = 1.5f;
	static inline const float GRID_SIZE = 1024.0f;
	static inline const float GRID_UV = 10.0f;
	static inline const float CAMERA_DISTANCE_SPEED = 5.0f;
	static inline const float MIN_CAMERA_DISTANCE = 0.5f;

	// BOOL
	bool _isCreatingTerrain = false;
	bool _isChoosingTerrain = false;
	bool _isDeletingTerrain = false;
	bool _isEditorLoaded = false;

	// MISCELLANEOUS
	FabiEngine3D& _fe3d;
	GuiManager& _gui;
};