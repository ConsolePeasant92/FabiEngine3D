#pragma once

#include "base_editor.hpp"

class WaterEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedEntities();

	const vector<string> getImagePathsFromFile() const;
	const vector<string>& getLoadedEntityIds() const;

	const bool loadEntitiesFromFile();
	const bool saveEntitiesToFile() const;

private:
	void _load();
	void _unload();
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

	vector <string> _loadedEntityIds;
	string _currentWaterId = "";

	static inline constexpr float CW = 0.115f;
	static inline constexpr float CH = 0.0875f;
	static inline constexpr float CURSOR_SENSITIVITY = 0.025f;
	static inline constexpr float INITIAL_CAMERA_YAW = 45.0f;
	static inline constexpr float INITIAL_CAMERA_PITCH = 45.0f;
	static inline constexpr float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline constexpr float MIN_CAMERA_PITCH = 1.0f;
	static inline constexpr float GRID_Y_OFFSET = 5.0f;
	static inline constexpr float GRID_SIZE = 1024.0f;
	static inline constexpr float GRID_REPEAT = 10.0f;
	static inline constexpr float CAMERA_DISTANCE_SPEED = 5.0f;
	static inline constexpr float MIN_CAMERA_DISTANCE = 0.5f;

	bool _isCreatingWater = false;
	bool _isChoosingWater = false;
	bool _isDeletingWater = false;
};