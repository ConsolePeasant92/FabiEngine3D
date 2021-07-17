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
	bool _addModel(const string& modelName, string meshPath, string diffuseMapPath, string lightMapPath, string reflectionMapPath, string normalMapPath,
		Vec3 size, bool isFaceCulled, bool isTransparent, bool isSpecular, ReflectionType reflectionType,
		float specularFactor, float specularIntensity, float lightness, Vec3 color, float uvRepeat, string lodEntityID,
		bool isInstanced, bool isBright, vector<string> aabbNames, vector<Vec3> aabbPositions, vector<Vec3> aabbSizes);
	void _loadMesh();
	void _loadDiffuseMap();
	void _loadLightMap();
	void _loadReflectionMap();
	void _loadNormalMap();
	void _updateManagementScreen();
	void _updateModelCreating();
	void _updateModelChoosing();
	void _updateEditingScreen();
	void _updateModelEditingMesh();
	void _updateModelEditingOptions();
	void _updateModelEditingLighting();
	void _updateModelEditingSize();
	void _updateModelEditingAabb();
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

	// Vectors
	static inline const Vec3 INITIAL_CAMERA_POSITION = Vec3(0.0f, 5.0f, 0.0f);
	Vec3 _cameraLookatPosition = Vec3(0.0f);

	// Floats
	static inline const float MOUSE_SENSITIVITY = 0.025f;
	static inline const float LOOKAT_MOVEMENT_SPEED = 0.05f;
	static inline const float INITIAL_CAMERA_YAW = 0.0f;
	static inline const float INITIAL_CAMERA_PITCH = 45.0f;
	static inline const float INITIAL_CAMERA_DISTANCE = 5.0f;
	static inline const float MIN_CAMERA_PITCH = 1.0f;
	static inline const float MODEL_Y_OFFSET = 0.001f;
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