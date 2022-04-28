#include "world_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

void WorldEditor::_load()
{
	_skyEditor->loadEntitiesFromFile();
	_terrainEditor->loadEntitiesFromFile();
	_waterEditor->loadEntitiesFromFile();
	_modelEditor->loadEntitiesFromFile();
	_quad3dEditor->loadEntitiesFromFile();
	_text3dEditor->loadEntitiesFromFile();
	_animation2dEditor->loadAnimationsFromFile();
	_animation3dEditor->loadAnimationsFromFile();
	_soundEditor->loadSoundsFromFile();

	_fe3d->model_create(TEMPLATE_LAMP_ID, LAMP_MODEL_PATH);
	_fe3d->model_create(TEMPLATE_TORCH_ID, TORCH_MODEL_PATH);
	_fe3d->model_create(TEMPLATE_CAMERA_ID, CAMERA_MODEL_PATH);
	_fe3d->model_create(TEMPLATE_SPEAKER_ID, SPEAKER_MODEL_PATH);
	_fe3d->model_setBaseSize(TEMPLATE_LAMP_ID, DEFAULT_LAMP_SIZE);
	_fe3d->model_setBaseSize(TEMPLATE_TORCH_ID, DEFAULT_TORCH_SIZE);
	_fe3d->model_setBaseSize(TEMPLATE_CAMERA_ID, DEFAULT_CAMERA_SIZE);
	_fe3d->model_setBaseSize(TEMPLATE_SPEAKER_ID, DEFAULT_SPEAKER_SIZE);
	_fe3d->model_setBaseRotation(TEMPLATE_TORCH_ID, DEFAULT_TORCH_ROTATION);
	_fe3d->model_setShadowed(TEMPLATE_LAMP_ID, false);
	_fe3d->model_setShadowed(TEMPLATE_TORCH_ID, false);
	_fe3d->model_setShadowed(TEMPLATE_CAMERA_ID, false);
	_fe3d->model_setShadowed(TEMPLATE_SPEAKER_ID, false);
	_fe3d->model_setReflected(TEMPLATE_LAMP_ID, false);
	_fe3d->model_setReflected(TEMPLATE_TORCH_ID, false);
	_fe3d->model_setReflected(TEMPLATE_CAMERA_ID, false);
	_fe3d->model_setReflected(TEMPLATE_SPEAKER_ID, false);
	_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
	_fe3d->model_setVisible(TEMPLATE_TORCH_ID, false);
	_fe3d->model_setVisible(TEMPLATE_CAMERA_ID, false);
	_fe3d->model_setVisible(TEMPLATE_SPEAKER_ID, false);

	_fe3d->pointlight_create(TEMPLATE_POINTLIGHT_ID);
	_fe3d->pointlight_setRadius(TEMPLATE_POINTLIGHT_ID, fvec3(DEFAULT_POINTLIGHT_RADIUS));
	_fe3d->pointlight_setIntensity(TEMPLATE_POINTLIGHT_ID, DEFAULT_POINTLIGHT_INTENSITY);
	_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, false);

	_fe3d->spotlight_create(TEMPLATE_SPOTLIGHT_ID);
	_fe3d->spotlight_setPitch(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_PITCH);
	_fe3d->spotlight_setIntensity(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_INTENSITY);
	_fe3d->spotlight_setAngle(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_ANGLE);
	_fe3d->spotlight_setDistance(TEMPLATE_SPOTLIGHT_ID, DEFAULT_SPOTLIGHT_DISTANCE);
	_fe3d->spotlight_setVisible(TEMPLATE_SPOTLIGHT_ID, false);

	_fe3d->captor_create(TEMPLATE_CAPTOR_ID);
	_fe3d->captor_setVisible(TEMPLATE_CAPTOR_ID, false);

	for(const auto & id : _soundEditor->getLoadedSoundIds())
	{
		_fe3d->sound3d_create(id, _fe3d->sound2d_getAudioPath(id));
		_fe3d->sound3d_setMaxVolume(id, DEFAULT_SOUND_MAX_VOLUME);
		_fe3d->sound3d_setMaxDistance(id, DEFAULT_SOUND_MAX_DISTANCE);
	}

	_fe3d->model_create("@@grid", "engine\\assets\\mesh\\plane.obj");
	_fe3d->model_setBasePosition("@@grid", fvec3(0.0f, -GRID_Y_OFFSET, 0.0f));
	_fe3d->model_setBaseSize("@@grid", fvec3(GRID_SIZE, 1.0f, GRID_SIZE));
	_fe3d->model_setDiffuseMap("@@grid", "", "engine\\assets\\image\\diffuse_map\\grid.tga");
	_fe3d->model_setTextureRepeat("@@grid", "", GRID_REPEAT);
	_fe3d->model_setMinTextureAlpha("@@grid", "", 0.1f);
	_fe3d->model_setShadowed("@@grid", false);

	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(16);
	_fe3d->collision_setCameraAabbResponseEnabled(true, true, true);
	_fe3d->raycast_setAabbIntersectionEnabled(true);

	for(const auto & id : _modelEditor->getLoadedEntityIds())
	{
		_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuModelPlace")->getScrollingList("modelList")->createOption(id, id.substr(1));
	}

	for(const auto & id : _quad3dEditor->getLoadedEntityIds())
	{
		_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuQuad3dPlace")->getScrollingList("quad3dList")->createOption(id, id.substr(1));
	}

	for(const auto & id : _text3dEditor->getLoadedEntityIds())
	{
		_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuText3dPlace")->getScrollingList("text3dList")->createOption(id, id.substr(1));
	}

	for(const auto & id : _soundEditor->getLoadedSoundIds())
	{
		_gui->getLeftViewport()->getWindow("main")->getScreen("worldEditorMenuSoundPlace")->getScrollingList("soundList")->createOption(id, id.substr(1));
	}

	_gui->getOverlay()->createTextField("selectedId", fvec2(0.0f, 0.0f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);
	_gui->getOverlay()->createTextField("activeId", fvec2(0.0f, 0.0f), fvec2(0.025f, 0.1f), " ", fvec3(1.0f), true);

	_gui->getRightViewport()->getWindow("main")->setActiveScreen("main");
}

void WorldEditor::_unload()
{
	for(const auto & id : _soundEditor->getLoadedSoundIds())
	{
		_fe3d->sound3d_delete(id);
	}

	_skyEditor->deleteLoadedEntities();
	_terrainEditor->deleteLoadedEntities();
	_waterEditor->deleteLoadedEntities();
	_modelEditor->deleteLoadedEntities();
	_quad3dEditor->deleteLoadedEntities();
	_text3dEditor->deleteLoadedEntities();
	_animation3dEditor->deleteLoadedAnimations();
	_animation2dEditor->deleteLoadedAnimations();
	_soundEditor->deleteLoadedSounds();

	_fe3d->model_delete(TEMPLATE_LAMP_ID);
	_fe3d->model_delete(TEMPLATE_TORCH_ID);
	_fe3d->model_delete(TEMPLATE_CAMERA_ID);
	_fe3d->model_delete(TEMPLATE_SPEAKER_ID);

	_fe3d->pointlight_delete(TEMPLATE_POINTLIGHT_ID);

	_fe3d->spotlight_delete(TEMPLATE_SPOTLIGHT_ID);

	_fe3d->captor_delete(TEMPLATE_CAPTOR_ID);

	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);

	_fe3d->collision_setCameraAabbResponseEnabled(false, false, false);

	_fe3d->raycast_setAabbIntersectionEnabled(false);

	_gui->getOverlay()->deleteTextField("selectedId");
	_gui->getOverlay()->deleteTextField("activeId");
}

void WorldEditor::update()
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
		_updateSoundPlacing();
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
		_updateSoundMenu();
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
		_updateSoundPlacingMenu();
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
		_updateSoundChoosingMenu();
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
		_updateSoundEditing();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateLightingSettingsMenu();
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
		_updateGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateShadowsGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateReflectionsGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateRefractionsGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateDofGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateFogGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateLensFlareGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateSkyExposureGraphicsSettingsMenu();
	}
	if(isLoaded() && !_currentWorldId.empty())
	{
		_updateBloomGraphicsSettingsMenu();
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