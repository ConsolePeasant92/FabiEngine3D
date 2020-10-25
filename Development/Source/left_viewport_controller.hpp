#pragma once

#include "viewport_controller.hpp"
#include "model_editor.hpp"
#include "world_editor.hpp"
#include "billboard_editor.hpp"
#include "scene_editor.hpp"
#include "script_editor.hpp"
#include "settings_editor.hpp"

#define LVPC LeftViewportController

class LeftViewportController final : public ViewportController
{
public:
	LeftViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui);

	void initialize() override;
	void update() override;

	ModelEditor& getModelEditor();
	WorldEditor& getWorldEditor();
	BillboardEditor& getBillboardEditor();
	SceneEditor& getSceneEditor();
	ScriptEditor& getScriptEditor();
	SettingsEditor& getSettingsEditor();

	// Static stuff for easier GUI function calls
	static inline const float calcTextWidth(const string& text, float charWidth, float maxWidth)
	{
		return std::min(static_cast<float>(text.size()) * charWidth, maxWidth);
	}
	static inline const vec3 frameColor = vec3(0.4f);
	static inline const vec3 buttonColor = vec3(0.25f, 0.25f, 1.0f);
	static inline const vec3 buttonHoverColor = vec3(0.75f, 0.75f, 1.0f);
	static inline const vec3 textColor = vec3(1.0f);
	static inline const vec3 textHoverColor = vec3(0.0f);

private:
	ModelEditor _modelEditor;
	WorldEditor _worldEditor;
	BillboardEditor _billboardEditor;
	SceneEditor _sceneEditor;
	ScriptEditor _scriptEditor;
	SettingsEditor _settingsEditor;
};