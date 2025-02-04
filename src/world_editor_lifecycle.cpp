#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_load()
{
	_skyEditor->loadSkiesFromFile();
	_terrainEditor->loadTerrainsFromFile();
	_waterEditor->loadWatersFromFile();
	_modelEditor->loadModelsFromFile();
	_quad3dEditor->loadQuad3dsFromFile();
	_text3dEditor->loadText3dsFromFile();
	_animation3dEditor->loadAnimation3dsFromFile();
	_animation2dEditor->loadAnimation2dsFromFile();
	_aabbEditor->loadAabbsFromFile();
	_pointlightEditor->loadPointlightsFromFile();
	_spotlightEditor->loadSpotlightsFromFile();
	_captorEditor->loadCaptorsFromFile();
	_sound3dEditor->loadSound3dsFromFile();

	_fe3d->model_create(GRID_ID, GRID_MESH_PATH);
	_fe3d->model_setBaseSize(GRID_ID, fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap(GRID_ID, "", GRID_TEXTURE_PATH);
	_fe3d->model_setTextureRepeat(GRID_ID, "", GRID_REPEAT);
	_fe3d->model_setMinAlpha(GRID_ID, "", GRID_MIN_ALPHA);
	_fe3d->model_setLightness(GRID_ID, "", GRID_LIGHTNESS);
	_fe3d->model_setShadowed(GRID_ID, false);
	_fe3d->model_create(LAMP_ID, LAMP_MESH_PATH);
	_fe3d->model_setBaseSize(LAMP_ID, LAMP_SIZE);
	_fe3d->model_setShadowed(LAMP_ID, false);
	_fe3d->model_setReflected(LAMP_ID, false);
	_fe3d->model_setRefracted(LAMP_ID, false);
	_fe3d->model_setVisible(LAMP_ID, false);
	_fe3d->model_setBright(LAMP_ID, "", true);
	_fe3d->model_create(TORCH_ID, TORCH_MESH_PATH);
	_fe3d->model_setBaseSize(TORCH_ID, TORCH_SIZE);
	_fe3d->model_setBaseRotation(TORCH_ID, TORCH_ROTATION);
	_fe3d->model_setShadowed(TORCH_ID, false);
	_fe3d->model_setReflected(TORCH_ID, false);
	_fe3d->model_setRefracted(TORCH_ID, false);
	_fe3d->model_setVisible(TORCH_ID, false);
	_fe3d->model_setBright(TORCH_ID, "", true);
	_fe3d->model_create(LENS_ID, LENS_MESH_PATH);
	_fe3d->model_setBaseSize(LENS_ID, LENS_SIZE);
	_fe3d->model_setShadowed(LENS_ID, false);
	_fe3d->model_setReflected(LENS_ID, false);
	_fe3d->model_setRefracted(LENS_ID, false);
	_fe3d->model_setVisible(LENS_ID, false);
	_fe3d->model_setBright(LENS_ID, "", true);
	_fe3d->model_create(SPEAKER_ID, SPEAKER_MESH_PATH);
	_fe3d->model_setBaseSize(SPEAKER_ID, SPEAKER_SIZE);
	_fe3d->model_setShadowed(SPEAKER_ID, false);
	_fe3d->model_setReflected(SPEAKER_ID, false);
	_fe3d->model_setRefracted(SPEAKER_ID, false);
	_fe3d->model_setVisible(SPEAKER_ID, false);
	_fe3d->model_setBright(SPEAKER_ID, "", true);
	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(16);
	_fe3d->collision_setCameraBox(0.0f, 0.0f, CAMERA_BOX_HEIGHT, 0.0f, 0.0f, 0.0f);

	for(const auto & skyId : _skyEditor->getLoadedSkyIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuSkyPlace")->getScrollingList("editorSkies")->createOption(skyId, skyId.substr(1));
	}

	for(const auto & terrainId : _terrainEditor->getLoadedTerrainIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuTerrainPlace")->getScrollingList("editorTerrains")->createOption(terrainId, terrainId.substr(1));
	}

	for(const auto & waterId : _waterEditor->getLoadedWaterIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuWaterPlace")->getScrollingList("editorWaters")->createOption(waterId, waterId.substr(1));
	}

	for(const auto & modelId : _modelEditor->getLoadedModelIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuModelPlace")->getScrollingList("editorModels")->createOption(modelId, modelId.substr(1));
	}

	for(const auto & quad3dId : _quad3dEditor->getLoadedQuad3dIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dPlace")->getScrollingList("editorQuad3ds")->createOption(quad3dId, quad3dId.substr(1));
	}

	for(const auto & text3dId : _text3dEditor->getLoadedText3dIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuText3dPlace")->getScrollingList("editorText3ds")->createOption(text3dId, text3dId.substr(1));
	}

	for(const auto & aabbId : _aabbEditor->getLoadedAabbIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuAabbPlace")->getScrollingList("editorAabbs")->createOption(aabbId, aabbId.substr(1));
	}

	for(const auto & pointlightId : _pointlightEditor->getLoadedPointlightIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuPointlightPlace")->getScrollingList("editorPointlights")->createOption(pointlightId, pointlightId.substr(1));
	}

	for(const auto & spotlightId : _spotlightEditor->getLoadedSpotlightIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuSpotlightPlace")->getScrollingList("editorSpotlights")->createOption(spotlightId, spotlightId.substr(1));
	}

	for(const auto & captorId : _captorEditor->getLoadedCaptorIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuCaptorPlace")->getScrollingList("editorCaptors")->createOption(captorId, captorId.substr(1));
	}

	for(const auto & sound3dId : _sound3dEditor->getLoadedSound3dIds())
	{
		_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuSound3dPlace")->getScrollingList("editorSound3ds")->createOption(sound3dId, sound3dId.substr(1));
	}

	_gui->getOverlay()->createTextField(SELECTED_TITLE_ID, fvec2(0.0f, 0.0f), fvec2(0.025f, 0.1f), "", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField(ACTIVE_TITLE_ID, fvec2(0.0f, 0.0f), fvec2(0.025f, 0.1f), "", fvec3(1.0f), true);
}

void WorldEditor::_unload()
{
	_skyEditor->deleteLoadedSkies();
	_terrainEditor->deleteLoadedTerrains();
	_waterEditor->deleteLoadedWaters();
	_modelEditor->deleteLoadedModels();
	_quad3dEditor->deleteLoadedQuad3ds();
	_text3dEditor->deleteLoadedText3ds();
	_animation3dEditor->deleteLoadedAnimation3ds();
	_animation2dEditor->deleteLoadedAnimation2ds();
	_aabbEditor->deleteLoadedAabbs();
	_pointlightEditor->deleteLoadedPointlights();
	_spotlightEditor->deleteLoadedSpotlights();
	_captorEditor->deleteLoadedCaptors();
	_sound3dEditor->deleteLoadedSound3ds();

	_fe3d->model_delete(GRID_ID);
	_fe3d->model_delete(LAMP_ID);
	_fe3d->model_delete(TORCH_ID);
	_fe3d->model_delete(LENS_ID);
	_fe3d->model_delete(SPEAKER_ID);
	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->collision_setCameraBox(0.0f, 0.0f, 0.0, 0.0f, 0.0f, 0.0f);

	_gui->getOverlay()->deleteTextField(SELECTED_TITLE_ID);
	_gui->getOverlay()->deleteTextField(ACTIVE_TITLE_ID);
}

void WorldEditor::_update()
{
	if(isLoaded())
	{
		_updateMainMenu();
	}

	if(isLoaded())
	{
		_updateWorldCreating();
	}

	if(isLoaded())
	{
		_updateWorldChoosing();
	}

	if(isLoaded())
	{
		_updateWorldDeleting();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateChoiceMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateModelPlacing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateQuad3dPlacing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateText3dPlacing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateAabbPlacing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePointlightPlacing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSpotlightPlacing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateCaptorPlacing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSound3dPlacing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSkyMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateTerrainMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateWaterMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateModelMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateQuad3dMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateText3dMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateAabbMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePointlightMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSpotlightMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateCaptorMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSound3dMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSkyPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateTerrainPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateWaterPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateModelPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateQuad3dPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateText3dPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateAabbPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePointlightPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSpotlightPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateCaptorPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSound3dPlacingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateModelChoosingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateQuad3dChoosingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateText3dChoosingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateAabbChoosingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePointlightChoosingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSpotlightChoosingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateCaptorChoosingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSound3dChoosingMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateModelEditing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateQuad3dEditing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateText3dEditing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateAabbEditing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePointlightEditing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSpotlightEditing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateCaptorEditing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSound3dEditing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSettingsMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateAmbientLightingSettingsMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateDirectionalLightingSettingsMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateShadowsSettingsMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePlanarReflectionsSettingsMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updatePlanarRefractionsSettingsMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateBloomSettingsMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateDofSettingsMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateLensFlareSettingsMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateFogSettingsMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSkyExposureSettingsMenu();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateExceptionChoosing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateAnimation3dChoosing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateAnimation2dChoosing();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateCamera();
	}

	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateMiscellaneous();
	}
}