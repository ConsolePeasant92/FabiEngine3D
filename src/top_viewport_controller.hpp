#pragma once

#include "base_viewport_controller.hpp"
#include "sky_editor.hpp"
#include "terrain_editor.hpp"
#include "water_editor.hpp"
#include "model_editor.hpp"
#include "quad3d_editor.hpp"
#include "quad2d_editor.hpp"
#include "text3d_editor.hpp"
#include "text2d_editor.hpp"
#include "animation3d_editor.hpp"
#include "animation2d_editor.hpp"
#include "aabb_editor.hpp"
#include "pointlight_editor.hpp"
#include "spotlight_editor.hpp"
#include "captor_editor.hpp"
#include "sound3d_editor.hpp"
#include "sound2d_editor.hpp"
#include "world_editor.hpp"
#include "script_editor.hpp"
#include "script_executor.hpp"

class TopViewportController final : public BaseViewportController
{
public:
	using BaseViewportController::inject;

	void inject(shared_ptr<SkyEditor> skyEditor);
	void inject(shared_ptr<TerrainEditor> terrainEditor);
	void inject(shared_ptr<WaterEditor> waterEditor);
	void inject(shared_ptr<ModelEditor> modelEditor);
	void inject(shared_ptr<Quad3dEditor> quad3dEditor);
	void inject(shared_ptr<Quad2dEditor> quad2dEditor);
	void inject(shared_ptr<Text3dEditor> text3dEditor);
	void inject(shared_ptr<Text2dEditor> text2dEditor);
	void inject(shared_ptr<Animation3dEditor> animation3dEditor);
	void inject(shared_ptr<Animation2dEditor> animation2dEditor);
	void inject(shared_ptr<AabbEditor> aabbEditor);
	void inject(shared_ptr<PointlightEditor> pointlightEditor);
	void inject(shared_ptr<SpotlightEditor> spotlightEditor);
	void inject(shared_ptr<CaptorEditor> captorEditor);
	void inject(shared_ptr<Sound3dEditor> sound3dEditor);
	void inject(shared_ptr<Sound2dEditor> sound2dEditor);
	void inject(shared_ptr<WorldEditor> worldEditor);
	void inject(shared_ptr<ScriptEditor> scriptEditor);
	void inject(shared_ptr<CustomWorldBuilder> customWorldBuilder);
	void inject(shared_ptr<Script> script);
	void inject(shared_ptr<ScriptExecutor> scriptExecutor);
	void initialize();
	void update();

	const bool isProjectCorrupted(const string & projectDirectoryPath) const;

private:
	void _updateProjectScreenManagement();
	void _updateApplicationScreenManagement();
	void _updateExtraScreenManagement();
	void _updateMiscellaneous();
	void _updateProjectCreating();
	void _updateProjectLoading();
	void _updateProjectDeleting();
	void _updateWindowClosing();
	void _setProject(const string & projectId);

	static inline const fvec3 FRAME_COLOR = fvec3(0.5f);
	static inline const fvec3 BUTTON_COLOR = fvec3(0.0f, 0.4f, 0.0f);
	static inline const fvec3 BUTTON_HOVER_COLOR = fvec3(0.0f, 1.0f, 0.0f);
	static inline const fvec3 TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 TEXT_HOVER_COLOR = fvec3(0.0f);
	static inline const fvec3 ROUND_BUTTON_COLOR = fvec3(1.0f);
	static inline const fvec3 ROUND_BUTTON_HOVER_COLOR = fvec3(0.5f);

	static inline const fvec2 ROUND_BUTTON_SIZE = fvec2(0.2f, 1.75f);
	static inline const fvec2 CHOICE_FORM_POSITION = fvec2(0.0f, 0.1f);
	static inline const fvec2 VALUE_FORM_POSITION = fvec2(0.0f, 0.1f);
	static inline const fvec2 ANSWER_FORM_POSITION = fvec2(0.0f, 0.25f);

	static inline constexpr float LCW = 0.05f;
	static inline constexpr float LCH = 1.5f;
	static inline constexpr float RCW = 0.075f;
	static inline constexpr float RCH = 1.5f;

	static inline constexpr int VALUE_FORM_SIZE = 15;

	shared_ptr<SkyEditor> _skyEditor = nullptr;
	shared_ptr<TerrainEditor> _terrainEditor = nullptr;
	shared_ptr<WaterEditor> _waterEditor = nullptr;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
	shared_ptr<Quad3dEditor> _quad3dEditor = nullptr;
	shared_ptr<Quad2dEditor> _quad2dEditor = nullptr;
	shared_ptr<Text3dEditor> _text3dEditor = nullptr;
	shared_ptr<Text2dEditor> _text2dEditor = nullptr;
	shared_ptr<Animation3dEditor> _animation3dEditor = nullptr;
	shared_ptr<Animation2dEditor> _animation2dEditor = nullptr;
	shared_ptr<AabbEditor> _aabbEditor = nullptr;
	shared_ptr<PointlightEditor> _pointlightEditor = nullptr;
	shared_ptr<SpotlightEditor> _spotlightEditor = nullptr;
	shared_ptr<CaptorEditor> _captorEditor = nullptr;
	shared_ptr<Sound3dEditor> _sound3dEditor = nullptr;
	shared_ptr<Sound2dEditor> _sound2dEditor = nullptr;
	shared_ptr<WorldEditor> _worldEditor = nullptr;
	shared_ptr<ScriptEditor> _scriptEditor = nullptr;
	shared_ptr<CustomWorldBuilder> _customWorldBuilder = nullptr;
	shared_ptr<Script> _script = nullptr;
	shared_ptr<ScriptExecutor> _scriptExecutor = nullptr;

	string _currentProjectId = "";
};