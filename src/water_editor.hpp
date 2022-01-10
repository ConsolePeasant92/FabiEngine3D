#pragma once

#include "base_editor.hpp"

class WaterEditor final : public BaseEditor
{
public:
	void setCurrentProjectID(const string& projectID);
	void load();
	void update();
	void unload();

	const vector<string> getImagePathsFromFile() const;
	const vector<string>& getLoadedIDs();

	const bool loadFromFile();
	const bool saveToFile() const;
	const bool isLoaded() const;

private:
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateTexturingMenu();
	void _updateLightingMenu();
	void _updateMiscellaneousMenu();
	void _updateWaterCreating();
	void _updateWaterChoosing();
	void _updateWaterDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	vector <string> _loadedWaterIDs;
	string _currentProjectID = "";
	string _currentWaterID = "";

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

	bool _isCreatingWater = false;
	bool _isChoosingWater = false;
	bool _isDeletingWater = false;
	bool _isEditorLoaded = false;
};