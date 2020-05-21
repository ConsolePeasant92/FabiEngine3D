#include "world_editor.hpp"

WorldEditor::WorldEditor(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void WorldEditor::initializeGUI()
{
	// Private window instance of left viewport
	_window = _gui->getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - worldManagement
	_window->addScreen("worldManagement");
	_window->getScreen("worldManagement")->addButton("sky", vec2(0.0f, 0.63f), vec2(0.65f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Sky", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("worldManagement")->addButton("terrain", vec2(0.0f, 0.21), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Terrain", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("worldManagement")->addButton("water", vec2(0.0f, -0.21), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Water", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("worldManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - skyManagement
	_window->addScreen("skyManagement");
	_window->getScreen("skyManagement")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "3D mesh", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyManagement")->addButton("options", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Options", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyManagement")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - skyMesh
	_window->addScreen("skyMesh");
	_window->getScreen("skyMesh")->addScrollingList("textureList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("leftTexture", "Left texture");
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("rightTexture", "Right texture");
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("frontTexture", "Front texture");
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("backTexture", "Back texture");
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("topTexture", "Top texture");
	_window->getScreen("skyMesh")->getScrollingList("textureList")->addButton("bottomTexture", "Bottom texture");
	_window->getScreen("skyMesh")->addButton("load", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Load", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("skyMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - skyOptions
	_window->addScreen("skyOptions");
	_window->getScreen("skyOptions")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - terrainManagement
	_window->addScreen("terrainManagement");
	_window->getScreen("terrainManagement")->addButton("mesh", vec2(0.0f, 0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "3D mesh", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainManagement")->addButton("blendmap", vec2(0.0f, 0.0f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Blendmap", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainManagement")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - terrainMesh
	_window->addScreen("terrainMesh");
	_window->getScreen("terrainMesh")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("heightmap", "Height map");
	_window->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("diffusemap", "Diffuse map");
	_window->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("size", "Size");
	_window->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("maxHeight", "Max height");
	_window->getScreen("terrainMesh")->getScrollingList("buttonList")->addButton("uvRepeat", "UV repeat");
	_window->getScreen("terrainMesh")->addButton("load", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Load", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - terrainBlendmap
	_window->addScreen("terrainBlendmap");
	_window->getScreen("terrainBlendmap")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("blendmap", "Blend map");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("red", "Red texture");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("green", "Green texture");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("blue", "Blue texture");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("redRepeat", "Red UV");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("greenRepeat", "Green UV");
	_window->getScreen("terrainBlendmap")->getScrollingList("buttonList")->addButton("blueRepeat", "Blue UV");
	_window->getScreen("terrainBlendmap")->addButton("load", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Load", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("terrainBlendmap")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - waterManagement
	_window->addScreen("waterManagement");
	_window->getScreen("waterManagement")->addButton("mesh", vec2(0.0f, 0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "3D mesh", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("waterManagement")->addButton("effects", vec2(0.0f, 0.21f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Effects", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("waterManagement")->addButton("options", vec2(0.0f, -0.21f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Options", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
	_window->getScreen("waterManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - waterMesh
	_window->addScreen("waterMesh");
	_window->getScreen("waterMesh")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("size", "Size");
	_window->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("height", "Height");
	_window->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("up", "Move up");
	_window->getScreen("waterMesh")->getScrollingList("buttonList")->addButton("down", "Move down");
	_window->getScreen("waterMesh")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - waterEffects
	_window->addScreen("waterEffects");
	_window->getScreen("waterEffects")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("uvRepeat", "UV repeat");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("dudvmap", "Dudv map");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("normalmap", "Normal map");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("reflective", "Reflective: OFF");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("refractive", "Refractive: OFF");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("waving", "Waving: OFF");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("rippling", "Rippling: OFF");
	_window->getScreen("waterEffects")->getScrollingList("buttonList")->addButton("specular", "Specular: OFF");
	_window->getScreen("waterEffects")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);

	// Left-viewport: mainWindow - waterOptions
	_window->addScreen("waterOptions");
	_window->getScreen("waterOptions")->addScrollingList("buttonList", vec2(0.0f, 0.2f), vec2(1.9, 1.5f), vec3(0.3f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, _gui->leftVpTextColor, _gui->leftVpTextHoverColor, vec2(0.15f, 0.1f));
	_window->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("speed", "Water speed");
	_window->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("transparency", "Transparency");
	_window->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("color", "Color");
	_window->getScreen("waterOptions")->getScrollingList("buttonList")->addButton("shininess", "Shininess");
	_window->getScreen("waterOptions")->addButton("back", vec2(0.0f, -0.9f), vec2(1.25f, 0.1f), _gui->leftVpButtonColor, _gui->leftVpButtonHoverColor, "Go back", _gui->leftVpTextColor, _gui->leftVpTextHoverColor);
}

void WorldEditor::loadProject()
{
	// Camera
	_fe3d.camera_load(90.0f, 0.1f, 1000.0f, vec3(0.0f), 0.0f, 0.0f);

	// Graphics
	_fe3d.gfx_enableAmbientLighting(0.75f);
	_fe3d.gfx_enableDirectionalLighting(vec3(1000.0f), 0.75f);
	_fe3d.gfx_enableMSAA();
	_fe3d.gfx_enableWaterEffects();

	// Other
	_skyTexturePaths = { "", "", "", "", "", "" };
	_isLoaded = true;
}

void WorldEditor::saveProject()
{

}

void WorldEditor::unloadProject()
{
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableMSAA();
	_fe3d.gfx_disableWaterEffects();

	// Delete sky
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_delete("@sky");
	}

	// Delete terrain
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		_fe3d.terrainEntity_delete("@terrain");
	}

	// Delete water
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		_fe3d.waterEntity_delete("@water");
	}

	// Clear variables
	_currentWorldPart = WorldPart::NONE;
	_currentProjectName = "";
	_terrainHeightmapPath = "";
	_terrainDiffusemapPath = "";
	_activeWritefieldID = "";
	_terrainBlendmapPath = "";
	_terrainRedPath = "";
	_terrainGreenPath = "";
	_terrainBluePath = "";
	_waterDudvmapPath = "";
	_waterNormalmapPath = "";
	_terrainSize = 0.0f;
	_maxTerrainHeight = 0.0f;
	_terrainUvRepeat = 0.0f;
	_terrainRedUvRepeat = 0.0f;
	_terrainGreenUvRepeat = 0.0f;
	_terrainBlueUvRepeat = 0.0f;
	_terrainCameraHeight = 0.0f;
	_terrainCameraDistance = 0.0f;
	_waterSize = 0.0f;
	_waterUvRepeat = 0.0f;
	_waterHeight = 0.0f;
	_waterCameraHeight = 0.0f;
	_waterCameraDistance = 0.0f;
	_cameraRotationSpeed = 0.0f;
	_totalCameraRotation = 0.0f;
	_isLoaded = false;
}

void WorldEditor::update(float delta)
{
	if (_isLoaded)
	{
		auto screen = _window->getScreen("worldManagement");
		_delta = delta;

		// GUI management
		if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("sky")->isHovered())
			{
				_window->setActiveScreen("skyManagement");
				_currentWorldPart = WorldPart::SKY;

				// Hide terrain
				if (_fe3d.terrainEntity_isExisting("@terrain"))
				{
					_fe3d.terrainEntity_hide("@terrain");
				}

				// Hide water
				if (_fe3d.waterEntity_isExisting("@water"))
				{
					_fe3d.waterEntity_hide("@water");
				}
			}
			else if (screen->getButton("terrain")->isHovered())
			{
				_window->setActiveScreen("terrainManagement");
				_currentWorldPart = WorldPart::TERRAIN;

				// Show terrain
				if (_fe3d.terrainEntity_isExisting("@terrain"))
				{
					_fe3d.terrainEntity_show("@terrain");
				}

				// Hide water
				if (_fe3d.waterEntity_isExisting("@water"))
				{
					_fe3d.waterEntity_hide("@water");
				}
			}
			else if (screen->getButton("water")->isHovered())
			{
				_window->setActiveScreen("waterManagement");
				_currentWorldPart = WorldPart::WATER;

				// Show water
				if (_fe3d.waterEntity_isExisting("@water"))
				{
					_fe3d.waterEntity_show("@water");
				}
			}
			else if (screen->getButton("back")->isHovered())
			{
				_window->setActiveScreen("main");
				unloadProject();
			}
		}

		// Update sub-menus
		_upateSkyManagement();
		_upateTerrainManagement();
		_upateWaterManagement();
	}
}