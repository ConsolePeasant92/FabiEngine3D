#pragma once

#include "base_editor.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "quad3d_editor.hpp"
#include "text3d_editor.hpp"
#include "animation3d_editor.hpp"
#include "animation2d_editor.hpp"
#include "aabb_editor.hpp"
#include "pointlight_editor.hpp"
#include "spotlight_editor.hpp"
#include "sound3d_editor.hpp"
#include "transformation_type.hpp"
#include "duplicator.hpp"

class WorldEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void inject(shared_ptr<SkyEditor> skyEditor);
	void inject(shared_ptr<TerrainEditor> terrainEditor);
	void inject(shared_ptr<WaterEditor> waterEditor);
	void inject(shared_ptr<ModelEditor> modelEditor);
	void inject(shared_ptr<Quad3dEditor> quad3dEditor);
	void inject(shared_ptr<Text3dEditor> text3dEditor);
	void inject(shared_ptr<Animation3dEditor> animation3dEditor);
	void inject(shared_ptr<Animation2dEditor> animation2dEditor);
	void inject(shared_ptr<AabbEditor> aabbEditor);
	void inject(shared_ptr<PointlightEditor> pointlightEditor);
	void inject(shared_ptr<SpotlightEditor> spotlightEditor);
	void inject(shared_ptr<Sound3dEditor> sound3dEditor);
	void inject(shared_ptr<Duplicator> duplicator);
	void update();
	void clearLoadedWorld();

	const string & getLoadedWorldId() const;

	const bool loadWorldFromFile(const string & fileName);
	const bool saveWorldToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateSkyMenu();
	void _updateSkyPlacingMenu();
	void _updateTerrainMenu();
	void _updateTerrainPlacingMenu();
	void _updateWaterMenu();
	void _updateWaterPlacingMenu();
	void _updateModelMenu();
	void _updateModelPlacingMenu();
	void _updateModelChoosingMenu();
	void _updateModelPlacing();
	void _updateModelEditing();
	void _updateQuad3dMenu();
	void _updateQuad3dPlacingMenu();
	void _updateQuad3dChoosingMenu();
	void _updateQuad3dPlacing();
	void _updateQuad3dEditing();
	void _updateText3dMenu();
	void _updateText3dPlacingMenu();
	void _updateText3dChoosingMenu();
	void _updateText3dPlacing();
	void _updateText3dEditing();
	void _updateAabbMenu();
	void _updateAabbPlacingMenu();
	void _updateAabbChoosingMenu();
	void _updateAabbPlacing();
	void _updateAabbEditing();
	void _updatePointlightMenu();
	void _updatePointlightPlacingMenu();
	void _updatePointlightChoosingMenu();
	void _updatePointlightPlacing();
	void _updatePointlightEditing();
	void _updateSpotlightMenu();
	void _updateSpotlightPlacingMenu();
	void _updateSpotlightChoosingMenu();
	void _updateSpotlightPlacing();
	void _updateSpotlightEditing();
	void _updateSound3dMenu();
	void _updateSound3dPlacingMenu();
	void _updateSound3dChoosingMenu();
	void _updateSound3dPlacing();
	void _updateSound3dEditing();
	void _updateCaptorMenu();
	void _updateCaptorChoosingMenu();
	void _updateCaptorPlacing();
	void _updateCaptorEditing();
	void _updateSettingsMenu();
	void _updateLightingSettingsMenu();
	void _updateAmbientLightingSettingsMenu();
	void _updateDirectionalLightingSettingsMenu();
	void _updateGraphicsSettingsMenu();
	void _updateShadowsGraphicsSettingsMenu();
	void _updateReflectionsGraphicsSettingsMenu();
	void _updateRefractionsGraphicsSettingsMenu();
	void _updateDofGraphicsSettingsMenu();
	void _updateFogGraphicsSettingsMenu();
	void _updateLensFlareGraphicsSettingsMenu();
	void _updateSkyExposureGraphicsSettingsMenu();
	void _updateBloomGraphicsSettingsMenu();
	void _updateWorldCreating();
	void _updateWorldChoosing();
	void _updateWorldDeleting();
	void _updateExceptionChoosing();
	void _updateAnimation3dChoosing();
	void _updateAnimation2dChoosing();
	void _updateCamera();
	void _updateMiscellaneous();
	void _deleteWorldFile(const string & worldId);
	void _selectModel(const string & modelId);
	void _selectQuad3d(const string & quad3dId);
	void _selectText3d(const string & text3dId);
	void _selectAabb(const string & aabbId);
	void _selectPointlight(const string & pointlightId);
	void _selectSpotlight(const string & spotlightId);
	void _selectSound3d(const string & sound3dId);
	void _selectCaptor(const string & captorId);
	void _deselectModel(const string & modelId);
	void _deselectQuad3d(const string & quad3dId);
	void _deselectText3d(const string & text3dId);
	void _deselectAabb(const string & aabbId);
	void _deselectPointlight(const string & pointlightId);
	void _deselectSpotlight(const string & spotlightId);
	void _deselectSound3d(const string & sound3dId);
	void _deselectCaptor(const string & captorId);
	void _activateModel(const string & modelId);
	void _activateQuad3d(const string & quad3dId);
	void _activateText3d(const string & text3dId);
	void _activateAabb(const string & aabbId);
	void _activatePointlight(const string & pointlightId);
	void _activateSpotlight(const string & spotlightId);
	void _activateSound3d(const string & sound3dId);
	void _activateCaptor(const string & captorId);
	void _deactivateModel();
	void _deactivateQuad3d();
	void _deactivateText3d();
	void _deactivateAabb();
	void _deactivatePointlight();
	void _deactivateSpotlight();
	void _deactivateSound3d();
	void _deactivateCaptor();
	void _handleInputBox(const string & screenId, const string & leftButtonId, const string & inputBoxId, const string & rightButtonId, float & value, float delta = 0.0f, float multiplier = 1.0f, float minimum = -FLT_MAX, float maximum = FLT_MAX);

	const vector<string> _getWorldIds() const;

	static inline const string GRID_ID = "@@grid";
	static inline const string GRID_MESH_PATH = "engine\\assets\\mesh\\plane.obj";
	static inline const string GRID_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\grid.tga";
	static inline const string LAMP_ID = "@@lamp";
	static inline const string LAMP_MESH_PATH = "engine\\assets\\mesh\\lamp.obj";
	static inline const string TORCH_ID = "@@torch";
	static inline const string TORCH_MESH_PATH = "engine\\assets\\mesh\\torch.obj";
	static inline const string LENS_ID = "@@lens";
	static inline const string LENS_MESH_PATH = "engine\\assets\\mesh\\lens.obj";
	static inline const string SPEAKER_ID = "@@speaker";
	static inline const string SPEAKER_MESH_PATH = "engine\\assets\\mesh\\speaker.obj";
	static inline const string ACTIVE_TITLE_ID = "active_title";
	static inline const string SELECTED_TITLE_ID = "selected_title";
	static inline const string CURSOR_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga";

	static inline const fvec3 MODEL_TERRAIN_OFFSET = fvec3(0.0f, 0.0f, 0.0f);
	static inline const fvec3 QUAD3D_TERRAIN_OFFSET = fvec3(0.0f, 0.0f, 0.0f);
	static inline const fvec3 TEXT3D_TERRAIN_OFFSET = fvec3(0.0f, 0.0f, 0.0f);
	static inline const fvec3 AABB_TERRAIN_OFFSET = fvec3(0.0f, 0.0f, 0.0f);
	static inline const fvec3 POINTLIGHT_TERRAIN_OFFSET = fvec3(0.0f, 1.5f, 0.0f);
	static inline const fvec3 SPOTLIGHT_TERRAIN_OFFSET = fvec3(0.0f, 1.5f, 0.0f);
	static inline const fvec3 SOUND3D_TERRAIN_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 CAPTOR_TERRAIN_OFFSET = fvec3(0.0f, 0.5f, 0.0f);
	static inline const fvec3 LAMP_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 LAMP_AABB_SIZE = fvec3(0.6f, 1.0f, 0.6f);
	static inline const fvec3 TORCH_ROTATION = fvec3(0.0f, 0.0f, -90.0f);
	static inline const fvec3 TORCH_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 TORCH_AABB_SIZE = fvec3(1.0f, 0.25f, 0.3f);
	static inline const fvec3 LENS_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 LENS_AABB_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 SPEAKER_SIZE = fvec3(1.0f, 1.0f, 1.0f);
	static inline const fvec3 SPEAKER_AABB_SIZE = fvec3(1.05f, 1.05f, 0.9f);

	static inline constexpr float MODEL_POSITION_SPEED_DIVIDER = 100.0f;
	static inline constexpr float MODEL_ROTATION_SPEED = 0.5f;
	static inline constexpr float MODEL_SIZE_SPEED_DIVIDER = 100.0f;
	static inline constexpr float MODEL_SIZE_FACTOR = 100.0f;
	static inline constexpr float QUAD3D_POSITION_SPEED_DIVIDER = 100.0f;
	static inline constexpr float QUAD3D_ROTATION_SPEED = 0.5f;
	static inline constexpr float QUAD3D_SIZE_SPEED_DIVIDER = 100.0f;
	static inline constexpr float QUAD3D_SIZE_FACTOR = 100.0f;
	static inline constexpr float TEXT3D_POSITION_SPEED_DIVIDER = 100.0f;
	static inline constexpr float TEXT3D_ROTATION_SPEED = 0.5f;
	static inline constexpr float TEXT3D_SIZE_SPEED_DIVIDER = 100.0f;
	static inline constexpr float TEXT3D_SIZE_FACTOR = 100.0f;
	static inline constexpr float AABB_POSITION_SPEED_DIVIDER = 100.0f;
	static inline constexpr float AABB_SIZE_SPEED_DIVIDER = 100.0f;
	static inline constexpr float AABB_SIZE_FACTOR = 100.0f;
	static inline constexpr float POINTLIGHT_POSITION_SPEED_DIVIDER = 100.0f;
	static inline constexpr float POINTLIGHT_RADIUS_SPEED_DIVIDER = 100.0f;
	static inline constexpr float POINTLIGHT_COLOR_SPEED = 0.005f;
	static inline constexpr float POINTLIGHT_INTENSITY_SPEED = 0.1f;
	static inline constexpr float POINTLIGHT_RADIUS = 5.0f;
	static inline constexpr float POINTLIGHT_INTENSITY = 10.0f;
	static inline constexpr float SPOTLIGHT_POSITION_SPEED_DIVIDER = 100.0f;
	static inline constexpr float SPOTLIGHT_COLOR_SPEED = 0.005f;
	static inline constexpr float SPOTLIGHT_YAW_SPEED = 0.5f;
	static inline constexpr float SPOTLIGHT_PITCH_SPEED = 0.5f;
	static inline constexpr float SPOTLIGHT_INTENSITY_SPEED = 0.1f;
	static inline constexpr float SPOTLIGHT_ANGLE_SPEED = 0.1f;
	static inline constexpr float SPOTLIGHT_DISTANCE_SPEED_DIVIDER = 100.0f;
	static inline constexpr float SPOTLIGHT_INTENSITY_FACTOR = 10.0f;
	static inline constexpr float SPOTLIGHT_PITCH = -90.0f;
	static inline constexpr float SPOTLIGHT_INTENSITY = 10.0f;
	static inline constexpr float SPOTLIGHT_ANGLE = 25.0f;
	static inline constexpr float SPOTLIGHT_DISTANCE = 10.0f;
	static inline constexpr float SOUND3D_POSITION_SPEED_DIVIDER = 100.0f;
	static inline constexpr float SOUND3D_DISTANCE_SPEED_DIVIDER = 100.0f;
	static inline constexpr float SOUND3D_VOLUME_FACTOR = 100.0f;
	static inline constexpr float SOUND3D_VOLUME_SPEED = 0.01f;
	static inline constexpr float SOUND3D_MAX_VOLUME = 1.0f;
	static inline constexpr float SOUND3D_MAX_DISTANCE = 25.0f;
	static inline constexpr float CAPTOR_POSITION_SPEED_DIVIDER = 100.0f;
	static inline constexpr float GRID_SIZE = 1024.0f;
	static inline constexpr float GRID_MIN_ALPHA = 0.1f;
	static inline constexpr float GRID_LIGHTNESS = 0.5f;
	static inline constexpr float COLOR_FACTOR = 255.0f;
	static inline constexpr float INTENSITY_FACTOR = 100.0f;
	static inline constexpr float SHADOW_LIGHTNESS_FACTOR = 100.0f;
	static inline constexpr float FOG_THICKNESS_FACTOR = 100.0f;
	static inline constexpr float LENS_FLARE_INTENSITY_FACTOR = 100.0f;
	static inline constexpr float LENS_FLARE_SENSITIVITY_FACTOR = 100.0f;
	static inline constexpr float SKY_EXPOSURE_INTENSITY_FACTOR = 100.0f;
	static inline constexpr float SKY_EXPOSURE_SPEED_FACTOR = 10000.0f;
	static inline constexpr float BLOOM_INTENSITY_FACTOR = 100.0f;
	static inline constexpr float CAMERA_POSITION_SPEED_DIVIDER = 100.0f;

	static inline constexpr int GRID_REPEAT = 205;

	vector<pair<string, string>> _loadedModelIds = {};
	vector<pair<string, string>> _loadedQuad3dIds = {};
	vector<pair<string, string>> _loadedText3dIds = {};
	vector<pair<string, string>> _loadedAabbIds = {};
	vector<pair<string, string>> _loadedPointlightIds = {};
	vector<pair<string, string>> _loadedSpotlightIds = {};
	vector<pair<string, string>> _loadedSound3dIds = {};
	vector<string> _loadedCaptorIds = {};

	shared_ptr<SkyEditor> _skyEditor = nullptr;
	shared_ptr<TerrainEditor> _terrainEditor = nullptr;
	shared_ptr<WaterEditor> _waterEditor = nullptr;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
	shared_ptr<Quad3dEditor> _quad3dEditor = nullptr;
	shared_ptr<Text3dEditor> _text3dEditor = nullptr;
	shared_ptr<AabbEditor> _aabbEditor = nullptr;
	shared_ptr<PointlightEditor> _pointlightEditor = nullptr;
	shared_ptr<SpotlightEditor> _spotlightEditor = nullptr;
	shared_ptr<Animation3dEditor> _animation3dEditor = nullptr;
	shared_ptr<Animation2dEditor> _animation2dEditor = nullptr;
	shared_ptr<Sound3dEditor> _sound3dEditor = nullptr;
	shared_ptr<Duplicator> _duplicator = nullptr;

	string _loadedWorldId = "";
	string _currentWorldId = "";
	string _currentTemplateModelId = "";
	string _currentTemplateQuad3dId = "";
	string _currentTemplateText3dId = "";
	string _currentTemplateAabbId = "";
	string _currentTemplatePointlightId = "";
	string _currentTemplateSpotlightId = "";
	string _currentTemplateSound3dId = "";
	string _selectedModelId = "";
	string _selectedQuad3dId = "";
	string _selectedText3dId = "";
	string _selectedAabbId = "";
	string _selectedPointlightId = "";
	string _selectedSpotlightId = "";
	string _selectedSound3dId = "";
	string _selectedCaptorId = "";
	string _activeModelId = "";
	string _activeQuad3dId = "";
	string _activeText3dId = "";
	string _activeAabbId = "";
	string _activePointlightId = "";
	string _activeSpotlightId = "";
	string _activeSound3dId = "";
	string _activeCaptorId = "";

	float _editorSpeed = 1.0f;

	int _idCounter = 0;

	bool _dontResetSelectedModel = false;
	bool _dontResetSelectedQuad3d = false;
	bool _dontResetSelectedText3d = false;
	bool _dontResetSelectedAabb = false;
	bool _dontResetSelectedPointlight = false;
	bool _dontResetSelectedSpotlight = false;
	bool _dontResetSelectedSound3d = false;
	bool _dontResetSelectedCaptor = false;
	bool _isPlacingCaptor = false;
	bool _isGridModeEnabled = true;
	bool _isWireframeModeEnabled = false;
	bool _isAabbModeEnabled = false;
};