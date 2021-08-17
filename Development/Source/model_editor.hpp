#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"
#include "direction.hpp"
#include "reflection_type.hpp"

class ModelEditor final
{
public:
	ModelEditor(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void setCurrentProjectID(const string& projectID);
	void load();
	void unload();
	void update();
	bool loadModelEntitiesFromFile();
	bool saveModelEntitiesToFile();

	bool isLoaded();

	const vector<string> getAllTexturePathsFromFile();
	const vector<string>& getLoadedModelIDs();

private:
	void _loadGUI();
	void _unloadGUI();
	void _loadDiffuseMap();
	void _loadEmissionMap();
	void _loadReflectionMap();
	void _loadNormalMap();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateMeshMenu();
	void _updateOptionsMenu();
	void _updateLightingSettingsMenu();
	void _updateSizeMenu();
	void _updateAabbMenu();
	void _updateModelCreating();
	void _updateModelChoosing();
	void _updateModelDeleting();
	void _updateCamera();
	void _updateMiscellaneous();

	// Instances
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;

	// Strings
	vector<string> _loadedModelIDs;
	string _currentModelID = "";
	string _currentAabbID = "";
	string _currentProjectID = "";
	string _hoveredModelID = "";

	// Floats
	static inline const float CW = 0.115f;
	static inline const float CH = 0.0875f;
	static inline const float MOUSE_SENSITIVITY = 0.025f;
	static inline const float INITIAL_CAMERA_YAW = 45.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 2.5f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	static inline const float GRID_Y_OFFSET = 0.001f;
	static inline const float GRID_SIZE = 60.0f;
	static inline const float GRID_UV = 6.0f;
	static inline const float MIN_CAMERA_DISTANCE = 1.5f;
	static inline const float CAMERA_DISTANCE_SPEED = 0.25f;
	static inline const float CAMERA_LOOKAT_SPEED = 0.05f;
	float _aabbTransformationSpeed = 0.1f;

	// Booleans
	bool _isCreatingModel = false;
	bool _isChoosingModel = false;
	bool _isEditingModel = false;
	bool _isDeletingModel = false;
	bool _isMovingToggled = false;
	bool _isResizingToggled = false;
	bool _isEditorLoaded = false;

	// Miscellaneous
	Direction _transformationDirection = Direction::X;
};