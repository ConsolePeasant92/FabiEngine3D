#include "environment_editor.hpp"
#include "left_viewport_controller.hpp"

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

EnvironmentEditor::EnvironmentEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void EnvironmentEditor::_loadGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - environmentEditorMenu
	leftWindow->addScreen("environmentEditorMenu");
	leftWindow->getScreen("environmentEditorMenu")->addButton("sky", Vec2(0.0f, 0.63f), Vec2(CW("Sky"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenu")->addButton("terrain", Vec2(0.0f, 0.21f), Vec2(CW("Terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenu")->addButton("water", Vec2(0.0f, -0.21f), Vec2(CW("Water"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("environmentEditorMenu")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: mainWindow - skyEditorMenuMain
	leftWindow->addScreen("skyEditorMenuMain");
	leftWindow->getScreen("skyEditorMenuMain")->addButton("create", Vec2(0.0f, 0.63f), Vec2(CW("Create sky"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMain")->addButton("edit", Vec2(0.0f, 0.21f), Vec2(CW("Edit sky"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMain")->addButton("delete", Vec2(0.0f, -0.21f), Vec2(CW("Remove sky"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Remove sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - skyEditorMenuChoice
	leftWindow->addScreen("skyEditorMenuChoice");
	leftWindow->getScreen("skyEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.475f), Vec2(CW("3D mesh"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuChoice")->addButton("options", Vec2(0.0f, 0.0f), Vec2(CW("Options"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Options", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.475f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - skyEditorMenuMesh
	leftWindow->addScreen("skyEditorMenuMesh");
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("leftTexture", Vec2(0.0f, 0.7875f), Vec2(CW("Left texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Left texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("rightTexture", Vec2(0.0f, 0.525f), Vec2(CW("Right texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Right texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("frontTexture", Vec2(0.0f, 0.2625f), Vec2(CW("Front texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Front texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("backTexture", Vec2(0.0f, 0.0f), Vec2(CW("Back texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Back texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("topTexture", Vec2(0.0f, -0.2625f), Vec2(CW("Top texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Top texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("bottomTexture", Vec2(0.0f, -0.525f), Vec2(CW("Bottom texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Bottom texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - skyEditorMenuOptions
	leftWindow->addScreen("skyEditorMenuOptions");
	leftWindow->getScreen("skyEditorMenuOptions")->addButton("rotationSpeed", Vec2(0.0f, 0.63f), Vec2(CW("Rotation speed"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rotation speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuOptions")->addButton("lightness", Vec2(0.0f, 0.21f), Vec2(CW("Lightness"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuOptions")->addButton("color", Vec2(0.0f, -0.21f), Vec2(CW("Color"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("skyEditorMenuOptions")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - terrainEditorMenuMain
	leftWindow->addScreen("terrainEditorMenuMain");
	leftWindow->getScreen("terrainEditorMenuMain")->addButton("create", Vec2(0.0f, 0.63f), Vec2(CW("Create terain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create terain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMain")->addButton("edit", Vec2(0.0f, 0.21f), Vec2(CW("Edit terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMain")->addButton("delete", Vec2(0.0f, -0.21f), Vec2(CW("Remove terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Remove terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - terrainEditorMenuChoice
	leftWindow->addScreen("terrainEditorMenuChoice");
	leftWindow->getScreen("terrainEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.63f), Vec2(CW("3D mesh"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuChoice")->addButton("blendMap", Vec2(0.0f, 0.21f), Vec2(CW("BlendMap"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "BlendMap", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuChoice")->addButton("lighting", Vec2(0.0f, -0.21f), Vec2(CW("Lighting"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lighting", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - terrainEditorMenuMesh
	leftWindow->addScreen("terrainEditorMenuMesh");
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("heightMap", Vec2(0.0f, 0.7f), Vec2(CW("Height map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Height map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("diffuseMap", Vec2(0.0f, 0.35f), Vec2(CW("Diffuse map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Diffuse map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("maxHeight", Vec2(0.0f, 0.0f), Vec2(CW("Max height"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Max height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("uvRepeat", Vec2(0.0f, -0.35f), Vec2(CW("UV repeat"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "UV repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - terrainEditorMenuBlendMap
	leftWindow->addScreen("terrainEditorMenuBlendMap");
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blendMap", Vec2(0.0f, 0.83f), Vec2(CW("Blend map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blend map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("red", Vec2(0.0f, 0.59f), Vec2(CW("Red texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("green", Vec2(0.0f, 0.36f), Vec2(CW("Green texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blue", Vec2(0.0f, 0.13f), Vec2(CW("Blue texture"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue texture", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("redRepeat", Vec2(0.0f, -0.1f), Vec2(CW("Red UV"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("greenRepeat", Vec2(0.0f, -0.33f), Vec2(CW("Green UV"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("blueRepeat", Vec2(0.0f, -0.56f), Vec2(CW("Blue UV"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue UV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuBlendMap")->addButton("back", Vec2(0.0f, -0.79f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	
	// Left-viewport: mainWindow - terrainEditorMenuLighting
	leftWindow->addScreen("terrainEditorMenuLighting");
	leftWindow->getScreen("terrainEditorMenuLighting")->addButton("normalMap", Vec2(0.0f, 0.8f), Vec2(CW("Normal map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->addButton("normalMapR", Vec2(0.0f, 0.6f), Vec2(CW("Red normal map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Red normal map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->addButton("normalMapG", Vec2(0.0f, 0.4f), Vec2(CW("Green normal map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Green normal map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->addButton("normalMapB", Vec2(0.0f, 0.2f), Vec2(CW("Blue normal map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Blue normal map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->addButton("isSpecular", Vec2(0.0f, 0.0f), Vec2(CW("Specular: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->addButton("specularFactor", Vec2(0.0f, -0.2f), Vec2(CW("Spec factor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->addButton("specularIntensity", Vec2(0.0f, -0.4f), Vec2(CW("Spec intensity"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Spec intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->addButton("lightness", Vec2(0.0f, -0.6f), Vec2(CW("Lightness"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Lightness", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("terrainEditorMenuLighting")->addButton("back", Vec2(0.0f, -0.8f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - waterEditorMenuMain
	leftWindow->addScreen("waterEditorMenuMain");
	leftWindow->getScreen("waterEditorMenuMain")->addButton("create", Vec2(0.0f, 0.63f), Vec2(CW("Create water"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Create water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMain")->addButton("edit", Vec2(0.0f, 0.21f), Vec2(CW("Edit water"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMain")->addButton("delete", Vec2(0.0f, -0.21f), Vec2(CW("Remove water"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Remove water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - waterEditorMenuChoice
	leftWindow->addScreen("waterEditorMenuChoice");
	leftWindow->getScreen("waterEditorMenuChoice")->addButton("terrain", Vec2(0.0f, 0.7f), Vec2(CW("Terrain"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->addButton("mesh", Vec2(0.0f, 0.35f), Vec2(CW("3D mesh"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "3D mesh", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->addButton("effects", Vec2(0.0f, 0.0f), Vec2(CW("Effects"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Effects", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->addButton("options", Vec2(0.0f, -0.35f), Vec2(CW("Options"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Options", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - waterEditorMenuMesh
	leftWindow->addScreen("waterEditorMenuMesh");
	leftWindow->getScreen("waterEditorMenuMesh")->addButton("position", Vec2(0.0f, 0.7f), Vec2(CW("Position"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Position", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMesh")->addButton("size", Vec2(0.0f, 0.35f), Vec2(CW("Size"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Size", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMesh")->addButton("up", Vec2(0.0f, 0.0f), Vec2(CW("Move up"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move up", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMesh")->addButton("down", Vec2(0.0f, -0.35f), Vec2(CW("Move down"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Move down", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuMesh")->addButton("back", Vec2(0.0f, -0.7f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - waterEditorMenuEffects
	leftWindow->addScreen("waterEditorMenuEffects");
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("uvRepeat", Vec2(0.0f, 0.859f), Vec2(CW("UV repeat"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "UV repeat", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("dudvMap", Vec2(0.0f, 0.668f), Vec2(CW("Dudv map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Dudv map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("normalMap", Vec2(0.0f, 0.477f), Vec2(CW("Normal map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Normal map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("displaceMap", Vec2(0.0f, 0.286f), Vec2(CW("Displace map"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Displace map", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("isReflective", Vec2(0.0f, 0.095f), Vec2(CW("Reflective: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflective: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("isRefractive", Vec2(0.0f, -0.096f), Vec2(CW("Refractive: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Refractive: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("isWaving", Vec2(0.0f, -0.287f), Vec2(CW("Waving: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Waving: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("isRippling", Vec2(0.0f, -0.478f), Vec2(CW("Rippling: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Rippling: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("isSpecular", Vec2(0.0f, -0.669f), Vec2(CW("Specular: OFF"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular: OFF", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuEffects")->addButton("back", Vec2(0.0f, -0.86f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - waterEditorMenuOptions
	leftWindow->addScreen("waterEditorMenuOptions");
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("speed", Vec2(0.0f, 0.7875f), Vec2(CW("Water speed"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water speed", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("transparency", Vec2(0.0f, 0.525f), Vec2(CW("Transparency"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Transparency", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("color", Vec2(0.0f, 0.2625f), Vec2(CW("Color"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Color", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("specularFactor", Vec2(0.0f, 0.0f), Vec2(CW("Spec factor"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular factor", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("specularIntensity", Vec2(0.0f, -0.2625f), Vec2(CW("Spec intensity"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Specular intensity", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("waveHeight", Vec2(0.0f, -0.525f), Vec2(CW("Wave height"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Wave height", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("waterEditorMenuOptions")->addButton("back", Vec2(0.0f, -0.7875f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void EnvironmentEditor::_unloadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	leftWindow->deleteScreen("environmentEditorMenu");
	leftWindow->deleteScreen("skyEditorMenuMain");
	leftWindow->deleteScreen("skyEditorMenuChoice");
	leftWindow->deleteScreen("skyEditorMenuMesh");
	leftWindow->deleteScreen("skyEditorMenuOptions");
	leftWindow->deleteScreen("terrainEditorMenuMain");
	leftWindow->deleteScreen("terrainEditorMenuChoice");
	leftWindow->deleteScreen("terrainEditorMenuMesh");
	leftWindow->deleteScreen("terrainEditorMenuBlendMap");
	leftWindow->deleteScreen("terrainEditorMenuLighting");
	leftWindow->deleteScreen("waterEditorMenuMain");
	leftWindow->deleteScreen("waterEditorMenuChoice");
	leftWindow->deleteScreen("waterEditorMenuMesh");
	leftWindow->deleteScreen("waterEditorMenuEffects");
	leftWindow->deleteScreen("waterEditorMenuOptions");
}

void EnvironmentEditor::load()
{
	// GUI
	_loadGUI();

	// Default camera
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f), 0.0f, 0.0f);
	
	// Enable default graphics
	_fe3d.gfx_enableAmbientLighting(Vec3(1.0f), 0.75f);
	_fe3d.gfx_enableDirectionalLighting(Vec3(1000.0f), Vec3(1.0f), 0.75f);
	_fe3d.gfx_enableSpecularLighting();
	_fe3d.gfx_enableNormalMapping();
	_fe3d.gfx_enableWaterEffects();

	// Core
	loadSkyEntitiesFromFile();
	loadTerrainEntitiesFromFile();
	loadWaterEntitiesFromFile();

	// Miscellaneous
	_gui.getGlobalScreen()->addTextfield("selectedSkyName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedTerrainName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getGlobalScreen()->addTextfield("selectedWaterName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("environmentEditorControls");
	_isEditorLoaded = true;
}

void EnvironmentEditor::save()
{
	saveSkyEntitiesToFile();
	saveTerrainEntitiesToFile();
	saveWaterEntitiesToFile();
}

void EnvironmentEditor::unload()
{
	// GUI
	_unloadGUI();

	// Disable default graphics
	_fe3d.gfx_disableAmbientLighting(true);
	_fe3d.gfx_disableDirectionalLighting(true);
	_fe3d.gfx_disableSpecularLighting(true);
	_fe3d.gfx_disableWaterEffects(true);

	// Delete entities
	unloadSkyEntities();
	unloadTerrainEntities();
	unloadWaterEntities();

	// Reset editor properties
	_loadedSkyIDs.clear();
	_loadedTerrainIDs.clear();
	_loadedWaterIDs.clear();
	_currentEnvironmentType = EnvironmentType::NONE;
	_cameraAcceleration = 0.0f;
	_totalCameraRotation = 0.0f;
	_currentSkyID = "";
	_hoveredSkyID = "";
	_currentTerrainID = "";
	_hoveredTerrainID = "";
	_currentWaterID = "";
	_hoveredWaterID = "";
	_isSkyCreationEnabled = false;
	_isSkyChoosingEnabled = false;
	_isSkyEditingEnabled = false;
	_isSkyRemovalEnabled = false;
	_isTerrainCreationEnabled = false;
	_isTerrainChoosingEnabled = false;
	_isTerrainEditingEnabled = false;
	_isTerrainRemovalEnabled = false;
	_isWaterCreationEnabled = false;
	_isWaterChoosingEnabled = false;
	_isWaterEditingEnabled = false;
	_isWaterRemovalEnabled = false;

	// Miscellaneous
	_gui.getGlobalScreen()->deleteTextfield("selectedSkyName");
	_gui.getGlobalScreen()->deleteTextfield("selectedTerrainName");
	_gui.getGlobalScreen()->deleteTextfield("selectedWaterName");
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");
	if (_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_fe3d.input_setKeyTogglingLocked(false);
	_isEditorLoaded = false;
}