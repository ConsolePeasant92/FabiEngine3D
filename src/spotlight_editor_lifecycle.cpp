#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "spotlight_editor.hpp"
#include "tools.hpp"

void SpotlightEditor::_load()
{
	_fe3d->model_create(GRID_ID, GRID_MESH_PATH);
	_fe3d->model_setBaseSize(GRID_ID, fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap(GRID_ID, "", GRID_TEXTURE_PATH);
	_fe3d->model_setTextureRepeat(GRID_ID, "", GRID_REPEAT);
	_fe3d->model_setMinAlpha(GRID_ID, "", GRID_MIN_ALPHA);
	_fe3d->model_setLightness(GRID_ID, "", GRID_LIGHTNESS);
	_fe3d->model_setShadowed(GRID_ID, false);
	_fe3d->model_create(BOX_ID, BOX_MESH_PATH);
	_fe3d->model_setDiffuseMap(BOX_ID, "", BOX_TEXTURE_PATH);
	_fe3d->model_setLightness(BOX_ID, "", BOX_LIGHTNESS);
	_fe3d->model_setFaceCulled(BOX_ID, "", true);
	_fe3d->model_create(TORCH_ID, TORCH_MESH_PATH);
	_fe3d->model_setBasePosition(TORCH_ID, TORCH_POSITION);
	_fe3d->model_setBaseRotation(TORCH_ID, TORCH_ROTATION);
	_fe3d->model_setBaseSize(TORCH_ID, TORCH_SIZE);
	_fe3d->model_setShadowed(TORCH_ID, false);
	_fe3d->model_setBright(TORCH_ID, "", true);
	_fe3d->model_setVisible(TORCH_ID, false);
	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->graphics_setAmbientLightingEnabled(true);
	_fe3d->graphics_setAmbientLightingIntensity(AMBIENT_LIGHTING_INTENSITY);
	_fe3d->graphics_setDirectionalLightingEnabled(true);
	_fe3d->graphics_setDirectionalLightingPosition(DIRECTIONAL_LIGHTING_POSITION);
	_fe3d->graphics_setDirectionalLightingIntensity(DIRECTIONAL_LIGHTING_INTENSITY);
	_fe3d->graphics_setShadowsEnabled(true);
	_fe3d->graphics_setShadowLightness(SHADOW_LIGHTNESS);
	_fe3d->graphics_setShadowQuality(SHADOW_QUALITY);
	_fe3d->graphics_setShadowPcfCount(SHADOW_PCF_COUNT);
	_fe3d->graphics_setShadowBias(SHADOW_BIAS);
	_fe3d->graphics_setShadowPositionOffset(fvec3(GRID_SIZE * 0.5f));
	_fe3d->graphics_setShadowSize(Mathematics::calculateMagnitude(fvec3(GRID_SIZE * 0.5f)));
	_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);
	_fe3d->camera_setMinThirdPersonPitch(MIN_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonEnabled(true);
	_fe3d->camera_setThirdPersonYaw(INITIAL_CAMERA_YAW);
	_fe3d->camera_setThirdPersonPitch(INITIAL_CAMERA_PITCH);
	_fe3d->camera_setThirdPersonDistance(INITIAL_CAMERA_DISTANCE);

	_gui->getOverlay()->createTextField(SPOTLIGHT_TITLE_ID, SPOTLIGHT_TITLE_POSITION, SPOTLIGHT_TITLE_SIZE, "", fvec3(1.0f), true);
}

void SpotlightEditor::_unload()
{
	for(const auto & spotlightId : _loadedSpotlightIds)
	{
		_fe3d->spotlight_delete(spotlightId);
	}

	_fe3d->model_delete(GRID_ID);
	_fe3d->model_delete(BOX_ID);
	_fe3d->model_delete(TORCH_ID);
	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setAmbientLightingEnabled(false);
	_fe3d->graphics_setAmbientLightingIntensity(0.0f);
	_fe3d->graphics_setDirectionalLightingEnabled(false);
	_fe3d->graphics_setDirectionalLightingPosition(fvec3(0.0f));
	_fe3d->graphics_setDirectionalLightingIntensity(0.0f);
	_fe3d->graphics_setShadowsEnabled(false);
	_fe3d->graphics_setShadowLightness(0.0f);
	_fe3d->graphics_setShadowQuality(0);
	_fe3d->graphics_setShadowPositionOffset(fvec3(0.0f));
	_fe3d->graphics_setShadowSize(0.0f);
	_fe3d->graphics_setShadowPcfCount(0);
	_fe3d->graphics_setShadowBias(0.0f);
	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField(SPOTLIGHT_TITLE_ID);

	_loadedSpotlightIds.clear();
}

void SpotlightEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->createScreen("spotlightEditorMenuMain");
	rightWindow->getScreen("spotlightEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Spotlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Spotlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("spotlightEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Spotlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Spotlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("spotlightEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Spotlight"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Spotlight", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("spotlightEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("spotlightEditorMenuChoice");
	rightWindow->getScreen("spotlightEditorMenuChoice")->createButton("color", fvec2(0.0f, POSITIONS(5)[0]), TEXT_SIZE("Color"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Color", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("spotlightEditorMenuChoice")->createButton("intensity", fvec2(0.0f, POSITIONS(5)[1]), TEXT_SIZE("Intensity"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Intensity", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("spotlightEditorMenuChoice")->createButton("distance", fvec2(0.0f, POSITIONS(5)[2]), TEXT_SIZE("Distance"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Distance", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("spotlightEditorMenuChoice")->createButton("angle", fvec2(0.0f, POSITIONS(5)[3]), TEXT_SIZE("Angle"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Angle", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("spotlightEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(5)[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("empty");

	rightWindow->setActiveScreen("spotlightEditorMenuMain");
}

void SpotlightEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->deleteScreen("spotlightEditorMenuMain");
	rightWindow->deleteScreen("spotlightEditorMenuChoice");

	leftWindow->setActiveScreen("main");

	rightWindow->setActiveScreen("main");
}

void SpotlightEditor::_update()
{
	if(isLoaded())
	{
		_updateMainMenu();
	}

	if(isLoaded())
	{
		_updateChoiceMenu();
	}

	if(isLoaded())
	{
		_updateSpotlightCreating();
	}

	if(isLoaded())
	{
		_updateSpotlightChoosing();
	}

	if(isLoaded())
	{
		_updateSpotlightDeleting();
	}

	if(isLoaded())
	{
		_updateCamera();
	}

	if(isLoaded())
	{
		_updateMiscellaneous();
	}
}