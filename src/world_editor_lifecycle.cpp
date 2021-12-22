#include "world_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"

WorldEditor::WorldEditor(FabiEngine3D& fe3d,
						 GuiManager& gui,
						 SkyEditor& skyEditor,
						 TerrainEditor& terrainEditor,
						 WaterEditor& waterEditor,
						 ModelEditor& modelEditor,
						 BillboardEditor& billboardEditor,
						 Animation2dEditor& animation2dEditor,
						 Animation3dEditor& animation3dEditor,
						 SoundEditor& soundEditor)
	:
	_fe3d(fe3d),
	_gui(gui),
	_skyEditor(skyEditor),
	_terrainEditor(terrainEditor),
	_waterEditor(waterEditor),
	_modelEditor(modelEditor),
	_billboardEditor(billboardEditor),
	_animation2dEditor(animation2dEditor),
	_animation3dEditor(animation3dEditor),
	_soundEditor(soundEditor)
{

}

void WorldEditor::load()
{
	// GUI
	_loadGUI();

	// Camera
	_fe3d.camera_reset();

	// Default graphics
	_fe3d.gfx_enableAntiAliasing();
	_fe3d.gfx_setAnisotropicFilteringQuality(Config::MAX_ANISOTROPIC_FILTERING_QUALITY);

	// Load template skies
	_skyEditor.loadFromFile();

	// Load template terrains
	_terrainEditor.loadFromFile();

	// Load template waters
	_waterEditor.loadFromFile();

	// Load template models
	_modelEditor.loadFromFile();
	for(const auto& modelID : _modelEditor.getLoadedIDs())
	{
		// Check if there is a model entity present
		if(_fe3d.model_isExisting(modelID))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuModelPlace")->getScrollingList("modelList")->
				createButton(modelID, modelID.substr(1));
		}
	}

	// Load template billboards
	_billboardEditor.loadFromFile();
	for(const auto& billboardID : _billboardEditor.getLoadedIDs())
	{
		// Check if there is a billboard entity present
		if(_fe3d.billboard_isExisting(billboardID))
		{
			_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuBillboardPlace")->getScrollingList("billboardList")->
				createButton(billboardID, billboardID.substr(1));
		}
	}

	// Load template animations
	_animation2dEditor.loadFromFile(false);
	_animation3dEditor.loadFromFile(false);

	// Load template sounds
	_soundEditor.loadFromFile();
	_fe3d.model_create(TEMPLATE_SPEAKER_ID, SPEAKER_MODEL_PATH);
	_fe3d.model_setBaseSize(TEMPLATE_SPEAKER_ID, DEFAULT_SPEAKER_SIZE);
	_fe3d.model_setShadowed(TEMPLATE_SPEAKER_ID, false);
	_fe3d.model_setReflected(TEMPLATE_SPEAKER_ID, false);
	_fe3d.model_setBright(TEMPLATE_SPEAKER_ID, true);
	_fe3d.model_setVisible(TEMPLATE_SPEAKER_ID, false);
	for(const auto& soundID : _soundEditor.getLoadedIDs())
	{
		_fe3d.sound3d_setMaxVolume(soundID, DEFAULT_SOUND_MAX_VOLUME);
		_fe3d.sound3d_setMaxDistance(soundID, DEFAULT_SOUND_MAX_DISTANCE);
		_gui.getViewport("left")->getWindow("main")->getScreen("worldEditorMenuSoundPlace")->getScrollingList("sounds")->
			createButton(soundID, soundID.substr(1));
	}

	// Load template pointlight
	_fe3d.model_create(TEMPLATE_LAMP_ID, LAMP_MODEL_PATH);
	_fe3d.model_setBaseSize(TEMPLATE_LAMP_ID, DEFAULT_LAMP_SIZE);
	_fe3d.model_setShadowed(TEMPLATE_LAMP_ID, false);
	_fe3d.model_setReflected(TEMPLATE_LAMP_ID, false);
	_fe3d.model_setBright(TEMPLATE_LAMP_ID, true);
	_fe3d.model_setVisible(TEMPLATE_LAMP_ID, false);
	_fe3d.pointlight_create(TEMPLATE_LAMP_ID);
	_fe3d.pointlight_setRadius(TEMPLATE_LAMP_ID, fvec3(DEFAULT_POINTLIGHT_RADIUS));
	_fe3d.pointlight_setIntensity(TEMPLATE_LAMP_ID, DEFAULT_POINTLIGHT_INTENSITY);
	_fe3d.pointlight_setVisible(TEMPLATE_LAMP_ID, false);

	// Load template spotlight
	_fe3d.model_create(TEMPLATE_TORCH_ID, TORCH_MODEL_PATH);
	_fe3d.model_setBaseSize(TEMPLATE_TORCH_ID, DEFAULT_TORCH_SIZE);
	_fe3d.model_setShadowed(TEMPLATE_TORCH_ID, false);
	_fe3d.model_setReflected(TEMPLATE_TORCH_ID, false);
	_fe3d.model_setBright(TEMPLATE_TORCH_ID, true);
	_fe3d.model_setVisible(TEMPLATE_TORCH_ID, false);
	_fe3d.spotlight_create(TEMPLATE_TORCH_ID);
	_fe3d.spotlight_setPitch(TEMPLATE_TORCH_ID, DEFAULT_SPOTLIGHT_PITCH);
	_fe3d.spotlight_setIntensity(TEMPLATE_TORCH_ID, DEFAULT_SPOTLIGHT_INTENSITY);
	_fe3d.spotlight_setAngle(TEMPLATE_TORCH_ID, DEFAULT_SPOTLIGHT_ANGLE);
	_fe3d.spotlight_setDistance(TEMPLATE_TORCH_ID, DEFAULT_SPOTLIGHT_DISTANCE);
	_fe3d.spotlight_setVisible(TEMPLATE_TORCH_ID, false);

	// Load template reflection
	_fe3d.model_create(TEMPLATE_CAMERA_ID, CAMERA_MODEL_PATH);
	_fe3d.model_setBaseSize(TEMPLATE_CAMERA_ID, DEFAULT_CAMERA_SIZE);
	_fe3d.model_setShadowed(TEMPLATE_CAMERA_ID, false);
	_fe3d.model_setReflected(TEMPLATE_CAMERA_ID, false);
	_fe3d.model_setBright(TEMPLATE_CAMERA_ID, true);
	_fe3d.model_setVisible(TEMPLATE_CAMERA_ID, false);
	_fe3d.reflection_create(TEMPLATE_CAMERA_ID);
	_fe3d.reflection_setVisible(TEMPLATE_CAMERA_ID, false);

	// Create ID text fields
	_gui.getOverlay()->createTextField("modelID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);
	_gui.getOverlay()->createTextField("billboardID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);
	_gui.getOverlay()->createTextField("soundID", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true, false);

	// Miscellaneous
	_fe3d.collision_enableCameraResponse(true, true, true);
	_fe3d.collision_setCameraBox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("main");
	_isEditorLoaded = true;
}

void WorldEditor::unload()
{
	// GUI
	_unloadGUI();

	// Default graphics
	_fe3d.gfx_disableAntiAliasing(true);
	_fe3d.gfx_setAnisotropicFilteringQuality(Config::MIN_ANISOTROPIC_FILTERING_QUALITY);
	_fe3d.gfx_setPlanarReflectionHeight(0.0f);

	// Clear world
	clearCurrentWorld();

	// Delete all sky entities except the background
	for(const auto& ID : _fe3d.sky_getIDs())
	{
		if(ID != "@@background")
		{
			_fe3d.sky_delete(ID);
		}
	}

	// Delete template entities
	_fe3d.terrain_deleteAll();
	_fe3d.water_deleteAll();
	_fe3d.model_deleteAll();
	_fe3d.billboard_deleteAll();
	_fe3d.sound2d_deleteAll();
	_fe3d.sound3d_deleteAll();
	_fe3d.pointlight_deleteAll();
	_fe3d.spotlight_deleteAll();
	_fe3d.reflection_deleteAll();

	// Reset editor properties
	_loadedModelIDs.clear();
	_outsideLoadedModelIDs.clear();
	_loadedBillboardIDs.clear();
	_outsideLoadedBillboardIDs.clear();
	_loadedSoundIDs.clear();
	_outsideLoadedSoundIDs.clear();
	_initialModelPosition.clear();
	_initialModelRotation.clear();
	_initialModelSize.clear();
	_customWorldModelIDs.clear();
	_customWorldBillboardIDs.clear();
	_customWorldAabbIDs.clear();
	_customWorldSoundIDs.clear();
	_customWorldPointlightIDs.clear();
	_customWorldSpotlightIDs.clear();
	_customWorldReflectionIDs.clear();
	_loadedAabbIDs.clear();
	_loadedPointlightIDs.clear();
	_loadedSpotlightIDs.clear();
	_loadedReflectionIDs.clear();
	_customWorldID = "";
	_loadedSkyID = "";
	_loadedTerrainID = "";
	_loadedWaterID = "";
	_currentSkyID = "";
	_currentTerrainID = "";
	_currentWaterID = "";
	_currentTemplateModelID = "";
	_selectedModelID = "";
	_activeModelID = "";
	_currentTemplateBillboardID = "";
	_selectedBillboardID = "";
	_activeBillboardID = "";
	_currentTemplateSoundID = "";
	_selectedSpeakerID = "";
	_activeSpeakerID = "";
	_selectedLampID = "";
	_activeLampID = "";
	_selectedTorchID = "";
	_activeTorchID = "";
	_selectedCameraID = "";
	_activeCameraID = "";
	_loadedWorldID = "";
	_currentWorldID = "";
	_editorSpeed = 1.0f;
	_selectedModelHighlightDirection = 1;
	_activeModelHighlightDirection = 1;
	_selectedBillboardHighlightDirection = 1;
	_activeBillboardHighlightDirection = 1;
	_selectedSpeakerHighlightDirection = 1;
	_activeSpeakerHighlightDirection = 1;
	_selectedLampHighlightDirection = 1;
	_activeLampHighlightDirection = 1;
	_selectedTorchHighlightDirection = 1;
	_activeTorchHighlightDirection = 1;
	_selectedCameraHighlightDirection = 1;
	_activeCameraHighlightDirection = 1;
	_hasCustomWorldLighting = false;
	_hasCustomWorldGraphics = false;
	_hasCustomWorldSky = false;
	_hasCustomWorldTerrain = false;
	_hasCustomWorldWater = false;
	_dontResetSelectedModel = false;
	_dontResetSelectedBillboard = false;
	_dontResetSelectedSpeaker = false;
	_dontResetSelectedLamp = false;
	_dontResetSelectedTorch = false;
	_dontResetSelectedCamera = false;
	_isPlacingPointlight = false;
	_isPlacingSpotlight = false;
	_isPlacingReflection = false;
	_isEditorLoaded = false;
	_isChoosingWorld = false;
	_isDeletingWorld = false;

	// Delete ID textFields
	_gui.getOverlay()->deleteTextField("modelID");
	_gui.getOverlay()->deleteTextField("billboardID");
	_gui.getOverlay()->deleteTextField("soundID");

	// Miscellaneous
	_fe3d.collision_disableCameraResponse();
	if(_fe3d.misc_isAabbFrameRenderingEnabled())
	{
		_fe3d.misc_disableAabbFrameRendering();
	}
	if(_fe3d.misc_isWireframeRenderingEnabled())
	{
		_fe3d.misc_disableWireframeRendering();
	}
	if(_fe3d.misc_isDebugRenderingEnabled())
	{
		_fe3d.misc_disableDebugRendering();
	}
	if(_fe3d.raycast_isTerrainPointingEnabled())
	{
		_fe3d.raycast_disableTerrainPointing();
	}
}

void WorldEditor::update()
{
	if(_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSkyMenu();
	}
	if(_isEditorLoaded)
	{
		_updateTerrainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateWaterMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelPlacingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateModelPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateModelEditing();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardPlacingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateBillboardEditing();
	}
	if(_isEditorLoaded)
	{
		_updateSoundMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSoundPlacingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSoundChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSoundPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateSoundEditing();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightMenu();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightPlacing();
	}
	if(_isEditorLoaded)
	{
		_updatePointlightEditing();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateSpotlightEditing();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionMenu();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionChoosingMenu();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionPlacing();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionEditing();
	}
	if(_isEditorLoaded)
	{
		_updateSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateLightingSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateAmbientLightingSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateDirectionalLightingSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateShadowsGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateReflectionsGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateRefractionsGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateDofGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateFogGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateLensFlareGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateSkyExposureGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateBloomGraphicsSettingsMenu();
	}
	if(_isEditorLoaded)
	{
		_updateCamera();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}