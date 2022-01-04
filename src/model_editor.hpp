#pragma once

#include "fe3d.hpp"
#include "gui_manager.hpp"
#include "reflection_type.hpp"

class ModelEditor final
{
public:
	ModelEditor(FabiEngine3D& fe3d, GuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();

	const vector<string> getMeshPathsFromFile() const;
	const vector<string> getImagePathsFromFile() const;
	const vector<string>& getLoadedIDs();

	const bool loadFromFile();
	const bool saveToFile() const;
	const bool isLoaded() const;

private:
	void _loadGUI();
	void _unloadGUI();
	void _tryPartChoosing(const string& nextActiveScreenID);
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateTexturingMenu();
	void _updateLightingMenu();
	void _updateMiscellaneousMenu();
	void _updateMainAabbMenu();
	void _updateChoiceAabbMenu();
	void _updateModelCreating();
	void _updateModelChoosing();
	void _updateModelDeleting();
	void _updatePartChoosing();
	void _updateAabbCreating();
	void _updateAabbChoosing();
	void _updateAabbDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	vector<string> _loadedModelIDs;
	string _currentProjectID = "";
	string _currentModelID = "";
	string _currentPartID = "";
	string _currentAabbID = "";
	string _hoveredModelID = "";
	string _hoveredPartID = "";
	string _nextActiveScreenID = "";

	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float CURSOR_SENSITIVITY = 0.025f;
	static inline const float INITIAL_CAMERA_YAW = 45.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	static inline const float GRID_Y_OFFSET = 0.001f;
	static inline const float GRID_SIZE = 60.0f;
	static inline const float GRID_UV = 6.0f;
	static inline const float MIN_CAMERA_DISTANCE = 0.5f;
	static inline const float CAMERA_DISTANCE_SPEED = 0.25f;
	static inline const float CAMERA_LOOKAT_SPEED = 0.025f;
	static inline const float PART_HIGHLIGHT_SPEED = 0.025f;

	int _selectedPartHighlightDirection = 1;

	bool _isCreatingModel = false;
	bool _isChoosingModel = false;
	bool _isDeletingModel = false;
	bool _isChoosingPart = false;
	bool _isCreatingAabb = false;
	bool _isChoosingAabb = false;
	bool _isDeletingAabb = false;
	bool _isEditorLoaded = false;

	FabiEngine3D& _fe3d;
	GuiManager& _gui;
};