#include "entity_placer.hpp"
#include "left_viewport_controller.hpp"

#include <fstream>
#include <sstream>

EntityPlacer::EntityPlacer(FabiEngine3D& fe3d, shared_ptr<EngineGuiManager> gui, WorldEditor& worldEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor) :
	_fe3d(fe3d),
	_gui(gui),
	_worldEditor(worldEditor),
	_modelEditor(modelEditor),
	_billboardEditor(billboardEditor)
{

}

void EntityPlacer::initializeGUI()
{
	// Private window instance of GUI windows
	_leftWindow = _gui->getViewport("left")->getWindow("main");
	_rightWindow = _gui->getViewport("right")->getWindow("main");

	// Left-viewport: mainWindow - placeMenuManagement
	_leftWindow->addScreen("placeManagement");
	_leftWindow->getScreen("placeManagement")->addButton("modelPlaceManagement", vec2(0.0f, 0.7f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Models", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("placeManagement")->addButton("billboardPlaceManagement", vec2(0.0f, 0.35f), vec2(1.7f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Billboards", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("placeManagement")->addButton("lightingManagement", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Lighting", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("placeManagement")->addButton("setSpeed", vec2(0.0f, -0.35f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Set speed", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("placeManagement")->addButton("back", vec2(0.0f, -0.7f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - modelPlaceManagement
	_leftWindow->addScreen("modelPlaceManagement");
	_leftWindow->getScreen("modelPlaceManagement")->addButton("placeModel", vec2(0.0f, 0.475f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Place model", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelPlaceManagement")->addButton("chooseModel", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Choose model", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("modelPlaceManagement")->addButton("back", vec2(0.0f, -0.475f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - placeModel
	_leftWindow->addScreen("placeModel");
	_leftWindow->getScreen("placeModel")->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8, 1.75f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("placeModel")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	
	// Left-viewport: mainWindow - chooseModel
	_leftWindow->addScreen("chooseModel");
	_leftWindow->getScreen("chooseModel")->addScrollingList("modelList", vec2(0.0f, 0.1f), vec2(1.8, 1.75f), vec3(0.3f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, LeftViewportController::textColor, LeftViewportController::textHoverColor, vec2(0.15f, 0.1f));
	_leftWindow->getScreen("chooseModel")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - billboardPlaceManagement
	_leftWindow->addScreen("billboardPlaceManagement");
	_leftWindow->getScreen("billboardPlaceManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - lightingManagement
	_leftWindow->addScreen("lightingManagement");
	_leftWindow->getScreen("lightingManagement")->addButton("ambient", vec2(0.0f, 0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Ambient", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("lightingManagement")->addButton("directional", vec2(0.0f, 0.21f), vec2(1.75f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Directional", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("lightingManagement")->addButton("point", vec2(0.0f, -0.21f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Point", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("lightingManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - ambientLightManagement
	_leftWindow->addScreen("ambientLightingManagement");
	_leftWindow->getScreen("ambientLightingManagement")->addButton("color", vec2(0.0f, 0.475f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("ambientLightingManagement")->addButton("intensity", vec2(0.0f, 0.0f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "intensity", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("ambientLightingManagement")->addButton("back", vec2(0.0f, -0.475f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - directionalLightManagement
	_leftWindow->addScreen("directionalLightingManagement");
	_leftWindow->getScreen("directionalLightingManagement")->addButton("color", vec2(0.0f, 0.63f), vec2(1.0f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Color", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("directionalLightingManagement")->addButton("position", vec2(0.0f, 0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Position", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("directionalLightingManagement")->addButton("intensity", vec2(0.0f, -0.21f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "intensity", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("directionalLightingManagement")->addButton("back", vec2(0.0f, -0.63f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Left-viewport: mainWindow - pointLightManagement
	_leftWindow->addScreen("pointLightManagement");
	_leftWindow->getScreen("pointLightManagement")->addButton("add", vec2(0.0f, 0.45f), vec2(1.5f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Add light", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_leftWindow->getScreen("pointLightManagement")->addButton("back", vec2(0.0f, -0.45f), vec2(1.25f, 0.1f), LeftViewportController::buttonColor, LeftViewportController::buttonHoverColor, "Go back", LeftViewportController::textColor, LeftViewportController::textHoverColor);

	// Right-viewport: mainWindow - modelProperties
	_rightWindow->addScreen("modelProperties");
	_rightWindow->getScreen("modelProperties")->addTextfield("transformation", vec2(0.0f, 0.95f), vec2(1.75f, 0.1f), "Transformation", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("translation", vec2(0.0f, 0.8f), vec2(0.75f, 0.2f), "translation.png", vec3(0.0f));
	_rightWindow->getScreen("modelProperties")->addButton("rotation", vec2(0.0f, 0.55f), vec2(0.75f, 0.2f), "rotation.png", vec3(0.0f));
	_rightWindow->getScreen("modelProperties")->addButton("scaling", vec2(0.0f, 0.3f), vec2(0.75f, 0.2f), "scaling.png", vec3(0.0f));
	_rightWindow->getScreen("modelProperties")->addButton("freeze", vec2(0.0f, 0.13f), vec2(1.25f, 0.075f), vec3(0.0f, 0.0f, 0.75f), vec3(0.25f, 0.25f, 1.0f), "Freeze", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_rightWindow->getScreen("modelProperties")->addButton("delete", vec2(0.0f, -0.03f), vec2(1.25f, 0.075f), vec3(0.75f, 0.0f, 0.0f), vec3(1.0f, 0.25f, 0.25f), "Delete", LeftViewportController::textColor, LeftViewportController::textHoverColor);
	_rightWindow->getScreen("modelProperties")->addTextfield("x", vec2(0.0f, -0.15f), vec2(0.25f, 0.1f), "X", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addTextfield("y", vec2(0.0f, -0.4f), vec2(0.25f, 0.1f), "Y", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addTextfield("z", vec2(0.0f, -0.65f), vec2(0.25f, 0.1f), "Z", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("xPlus", vec2(0.75f, -0.25f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("yPlus", vec2(0.75f, -0.5f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("zPlus", vec2(0.75f, -0.75f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("xMinus", vec2(-0.75f, -0.25f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("yMinus", vec2(-0.75f, -0.5f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addButton("zMinus", vec2(-0.75f, -0.75f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("modelProperties")->addWriteField("x", vec2(0.0f, -0.25f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("modelProperties")->addWriteField("y", vec2(0.0f, -0.5f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("modelProperties")->addWriteField("z", vec2(0.0f, -0.75f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);

	// Right-viewport: mainWindow - lightProperties
	_rightWindow->addScreen("lightProperties");
	_rightWindow->getScreen("lightProperties")->addTextfield("intensity", vec2(0.0f, 0.95f), vec2(1.5f, 0.1f), "Intensity", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("intensityPlus", vec2(0.75f, 0.85f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("intensityMinus", vec2(-0.75f, 0.85f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addWriteField("intensity", vec2(0.0f, 0.85f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("lightProperties")->addTextfield("distance", vec2(0.0f, 0.725f), vec2(1.5f, 0.1f), "Distance", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("distancePlus", vec2(0.75f, 0.625f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("distanceMinus", vec2(-0.75f, 0.625f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addWriteField("distance", vec2(0.0f, 0.625f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("lightProperties")->addTextfield("x", vec2(0.0f, 0.5f), vec2(0.25f, 0.1f), "X", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("xPlus", vec2(0.75f, 0.4f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("xMinus", vec2(-0.75f, 0.4f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addWriteField("x", vec2(0.0f, 0.4f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("lightProperties")->addTextfield("y", vec2(0.0f, 0.275f), vec2(0.25f, 0.1f), "Y", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("yPlus", vec2(0.75f, 0.175f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("yMinus", vec2(-0.75f, 0.175f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addWriteField("y", vec2(0.0f, 0.175f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("lightProperties")->addTextfield("z", vec2(0.0f, 0.05f), vec2(0.25f, 0.1f), "Z", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("zPlus", vec2(0.75f, -0.05f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("zMinus", vec2(-0.75f, -0.05f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addWriteField("z", vec2(0.0f, -0.05f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("lightProperties")->addTextfield("r", vec2(0.0f, -0.175f), vec2(0.25f, 0.1f), "R", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("rPlus", vec2(0.75f, -0.185f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("rMinus", vec2(-0.75f, -0.185f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addWriteField("r", vec2(0.0f, -0.185f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("lightProperties")->addTextfield("g", vec2(0.0f, -0.4f), vec2(0.25f, 0.1f), "G", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("gPlus", vec2(0.75f, -0.5f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("gMinus", vec2(-0.75f, -0.5f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addWriteField("g", vec2(0.0f, -0.5f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("lightProperties")->addTextfield("b", vec2(0.0f, -0.625f), vec2(0.25f, 0.1f), "B", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("bPlus", vec2(0.75f, -0.725f), vec2(0.5f, 0.15f), "plus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addButton("bMinus", vec2(-0.75f, -0.725f), vec2(0.5f, 0.15f), "minus.png", vec3(1.0f));
	_rightWindow->getScreen("lightProperties")->addWriteField("b", vec2(0.0f, -0.725f), vec2(1.0f, 0.1f), vec3(0.25f), vec3(0.75f), vec3(1.0f), vec3(0.0f), 0, 1, 1, 1, 1);
	_rightWindow->getScreen("lightProperties")->addButton("delete", vec2(0.0f, -0.9f), vec2(1.5f, 0.1f), vec3(0.75f, 0.0f, 0.0f), vec3(1.0f, 0.25f, 0.25f), "Delete", LeftViewportController::textColor, LeftViewportController::textHoverColor);
}

void EntityPlacer::load()
{
	// Enable graphics
	_fe3d.gfx_enableLightMapping();
	_fe3d.gfx_enablePointLighting();
	_fe3d.gfx_enableSkyReflections(0.25f);
	_fe3d.gfx_enableMSAA();
	_fe3d.gfx_enableWaterEffects();
	//_fe3d.gfx_enableShadows(vec3(50.0f, 50.0f, 0.0f), vec3(0.0f), 100.0f, 150.0);
	_fe3d.gfx_enableSpecularLighting(3.0f);

	// Disable default skybox
	_fe3d.skyEntity_select("");

	// Load world entities
	_worldEditor.loadSkyEntity();
	_worldEditor.loadTerrainEntity();
	_worldEditor.loadWaterEntity();

	// Show sky entity
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_show("@sky");
	}

	// Show terrain entity
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		_fe3d.terrainEntity_show("@terrain");
	}

	// Show water entity
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		_fe3d.waterEntity_show("@water");
	}

	// Camera properties
	float height = 0.0f;

	// Set camera height relative to water size
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		float size = _fe3d.waterEntity_getSize("@water") / 2.0f;
		height = _fe3d.waterEntity_getSurfaceHeight("@water") + (size / 10.0f);
	}

	// Terrain can overwrite camera height
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		height = _fe3d.terrainEntity_getMaxHeight("@terrain");
	}

	// Load camera
	_fe3d.camera_setPosition(vec3(0.0f, height, 0.0f));

	// Preview model loading
	_modelEditor.loadModels();
	for (auto& modelName : _modelEditor.getModelNames())
	{
		// Check if there is a game entity present
		if (_fe3d.gameEntity_isExisting(modelName))
		{
			_leftWindow->getScreen("placeModel")->getScrollingList("modelList")->addButton(modelName, modelName.substr(1, modelName.size() - 1));
		}
	}

	// Preview pointlight loading
	_fe3d.lightEntity_add(_previewPointlightID, vec3(0.0f), _defaultPointlightColor, _defaultPointlightIntensity);
	_fe3d.gameEntity_add(_previewPointlightID, "Engine\\OBJs\\lamp.obj", vec3(0.0f), vec3(0.0f), _defaultLightbulbSize);
	_fe3d.aabbEntity_add(_previewPointlightID, vec3(0.0f), _defaultLightbulbAabbSize, true);

	// Create name textfields
	_gui->getGlobalScreen()->addTextfield("selectedModelName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui->getGlobalScreen()->addTextfield("selectedBillboardName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));
	_gui->getGlobalScreen()->addTextfield("selectedPointlightName", vec2(0.0f, 0.85f), vec2(0.5f, 0.1f), "", vec3(1.0f));

	// Other
	loadWorld();
	_isLoaded = true;
}

void EntityPlacer::loadWorld()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	string modelsPath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\world.fe3d";

	// Load models file
	if (_fe3d.misc_isFileExisting(modelsPath)) // Check if models file exists
	{
		std::ifstream file(modelsPath);
		string line;

		// Read model data
		while (std::getline(file, line))
		{
			// Placeholder variables
			string entityType;

			// For item extraction
			std::istringstream iss(line);

			// Extract type from file
			iss >> entityType;

			// Load entity according to type
			if (entityType == "MODEL")
			{
				string modelID, objPath, diffuseMapPath, lightMapPath, reflectionMapPath;
				vec3 position, rotation, size, color, aabbSize;
				float uvRepeat, specularIntensity;
				bool isFaceculled, isShadowed, isTransparent, isSpecular, isFrozen;

				// Load model data
				iss >> modelID >> position.x >> position.y >> position.z >> rotation.x >> rotation.y >> rotation.z >> 
					size.x >> size.y >> size.z >> objPath >> diffuseMapPath >> lightMapPath >> reflectionMapPath >>
					isFaceculled >> isShadowed >> isTransparent >> isSpecular >> isFrozen >> specularIntensity >> 
					color.r >> color.g >> color.b >> uvRepeat >> aabbSize.x >> aabbSize.y >> aabbSize.z;

				// Run checks on string values
				objPath = (objPath == "-") ? "" : objPath;
				diffuseMapPath = (diffuseMapPath == "-") ? "" : diffuseMapPath;
				lightMapPath = (lightMapPath == "-") ? "" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "-") ? "" : reflectionMapPath;

				// Extract the model name from the model ID
				string modelName = "";
				for (auto& name : _modelEditor.getModelNames())
				{
					if (modelID.substr(0, name.size() - 1) == name.substr(1, name.size() - 1))
					{
						modelName = name;
					}
				}

				// Add the model
				_placeModel(modelID, position, rotation, size, objPath, diffuseMapPath, lightMapPath, reflectionMapPath, isFaceculled, isShadowed, isTransparent, isSpecular,
					specularIntensity, color, uvRepeat, aabbSize);
			}
			else if (entityType == "BILLBOARD")
			{

			}
			else if (entityType == "AMBIENT")
			{
				iss >> _ambientLightColor.r >> _ambientLightColor.g >> _ambientLightColor.b >> _ambientLightIntensity;
				_fe3d.gfx_enableAmbientLighting(_ambientLightColor, _ambientLightIntensity);
			}
			else if (entityType == "DIRECTIONAL")
			{
				iss >> _directionalLightPosition.x >> _directionalLightPosition.y >> _directionalLightPosition.z >>
					_directionalLightColor.r >> _directionalLightColor.g >> _directionalLightColor.b >> _directionalLightIntensity;
				_fe3d.gfx_enableDirectionalLighting(_directionalLightPosition, _directionalLightColor, _directionalLightIntensity);
			}
			else if (entityType == "POINT")
			{
				string ID;
				vec3 position, color;
				float intensity;

				// Extract line data
				iss >> ID >> position.x >> position.y >> position.z >> color.r >> color.g >> color.b >> intensity;

				// Add entities
				_fe3d.gameEntity_add("@" + ID, "Engine\\OBJs\\lamp.obj", position, vec3(0.0f), _defaultLightbulbSize);
				_fe3d.aabbEntity_bindToGameEntity("@" + ID, _defaultLightbulbAabbSize, true);
				_fe3d.lightEntity_add(ID, position, color, intensity);
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Models from project \"" + _currentProjectName + "\" loaded!");
	}
}

void EntityPlacer::save()
{
	if (_isLoaded)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite models file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\world.fe3d");

		// Write game entities data into file
		for (auto& entityID : _fe3d.gameEntity_getAllIDs())
		{
			// Check if not preview model
			if (entityID[0] != '@')
			{
				// Retrieve all values to be saved
				auto position = _fe3d.gameEntity_getPosition(entityID);
				auto rotation = _fe3d.gameEntity_getRotation(entityID);
				auto size = _fe3d.gameEntity_getSize(entityID);
				auto objPath = _fe3d.gameEntity_getObjPath(entityID);
				auto diffuseMapPath = _fe3d.gameEntity_getDiffuseMapPath(entityID);
				auto lightMapPath = _fe3d.gameEntity_getLightMapPath(entityID);
				auto reflectionMapPath = _fe3d.gameEntity_getReflectionMapPath(entityID);
				auto isFaceCulled = _fe3d.gameEntity_isFaceCulled(entityID);
				auto isShadowed = _fe3d.gameEntity_isShadowed(entityID);
				auto isTransparent = _fe3d.gameEntity_isTransparent(entityID);
				auto isSpecular = _fe3d.gameEntity_isSpecularLighted(entityID);
				auto isFrozen = _fe3d.gameEntity_isStaticToCamera(entityID);
				auto specularIntensity = _fe3d.gameEntity_getSpecularIntensity(entityID);
				auto color = _fe3d.gameEntity_getColor(entityID);
				auto uvRepeat = _fe3d.gameEntity_getUvRepeat(entityID);
				auto aabbSize = _fe3d.aabbEntity_getSize(entityID);

				// String value corrections
				diffuseMapPath = (diffuseMapPath == "") ? "-" : diffuseMapPath;
				lightMapPath = (lightMapPath == "") ? "-" : lightMapPath;
				reflectionMapPath = (reflectionMapPath == "") ? "-" : reflectionMapPath;

				// 1 model -> 1 line in file
				file << "MODEL " << entityID << " " << position.x << " " << position.y << " " << position.z << " " <<
					rotation.x << " " << rotation.y << " " << rotation.z << " " << size.x << " " << size.y << " " << size.z << " " <<
					objPath << " " << diffuseMapPath << " " << lightMapPath << " " << reflectionMapPath << " " <<
					isFaceCulled << " " << isShadowed << " " << isTransparent << " " << isSpecular << " " << isFrozen << " " << 
					specularIntensity << " " << color.r << " " << color.g << " " << color.b << " " << uvRepeat << " " <<
					aabbSize.x << " " << aabbSize.y << " " << aabbSize.z << "\n";
			}
		}

		// Ambient light
		file << "AMBIENT " << _ambientLightColor.r << " " << _ambientLightColor.g << " " <<
			_ambientLightColor.b << " " << _ambientLightIntensity << "\n";

		// Directional light
		file << "DIRECTIONAL " << _directionalLightPosition.x << " " << _directionalLightPosition.y << " " <<
			_directionalLightPosition.z << " " << _directionalLightColor.r << " " << _directionalLightColor.g << " " <<
			_directionalLightColor.b << " " << _directionalLightIntensity << "\n";

		// Point lights
		for (auto& entityID : _fe3d.lightEntity_getAllIDs())
		{
			// Check if not preview model
			if (entityID[0] != '@')
			{
				auto position = _fe3d.lightEntity_getPosition(entityID);
				auto color = _fe3d.lightEntity_getColor(entityID);
				auto intensity = _fe3d.lightEntity_getIntensity(entityID);

				// Write line to file
				file << "POINT " << entityID << " " << position.x << " " << position.y << " " << position.z << " " <<
					color.r << " " << color.g << " " << color.b << " " << intensity << "\n";
			}
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Entity placer data from project \"" + _currentProjectName + "\" saved!");
	}
}

void EntityPlacer::unload()
{
	// Disable graphics
	_fe3d.gfx_disableAmbientLighting();
	_fe3d.gfx_disableDirectionalLighting();
	_fe3d.gfx_disableLightMapping();
	_fe3d.gfx_disableSkyReflections();
	_fe3d.gfx_disableMSAA();
	_fe3d.gfx_disableWaterEffects();
	_fe3d.gfx_disableShadows();
	_fe3d.gfx_disableSpecularLighting();
	_fe3d.gfx_disablePointLighting();

	// Delete world entities
	if (_fe3d.skyEntity_isExisting("@sky"))
	{
		_fe3d.skyEntity_delete("@sky");
	}

	// Show terrain entity
	if (_fe3d.terrainEntity_isExisting("@terrain"))
	{
		_fe3d.terrainEntity_delete("@terrain");
	}

	// Show water entity
	if (_fe3d.waterEntity_isExisting("@water"))
	{
		_fe3d.waterEntity_delete("@water");
	}

	// Delete placed entities
	_fe3d.gameEntity_deleteAll();
	_fe3d.billboardEntity_deleteAll();
	_fe3d.lightEntity_deleteAll();

	// Reset variables
	_currentPreviewModelName = "";
	_customCameraSpeed = 10.0f;
	_currentPreviewModelName = "";
	_currentBillboardName = "";
	_ambientLightColor = vec3(1.0f);
	_ambientLightIntensity = 1.0f;
	_directionalLightColor = vec3(1.0f);
	_directionalLightPosition = vec3(0.0f);
	_directionalLightIntensity = 0.0f;
	_isPlacingPointlight = false;
	_isLoaded = false;
	_transformation = Transformation::TRANSLATION;
	_customCameraSpeed = 25.0f;

	// Delete name textfields
	_gui->getGlobalScreen()->deleteTextfield("selectedModelName");
	_gui->getGlobalScreen()->deleteTextfield("selectedBillboardName");
	_gui->getGlobalScreen()->deleteTextfield("selectedPointlightName");

	// Enable default skybox
	_fe3d.skyEntity_select("@defaultSky");

	// Camera
	_fe3d.camera_setPosition(vec3(0.0f));
	_fe3d.camera_setYaw(0.0f);
	_fe3d.camera_setPitch(0.0f);
	_fe3d.camera_disableFirstPersonView();

	// Other
	_leftWindow->getScreen("placeModel")->getScrollingList("modelList")->deleteButtons();
	_fe3d.collision_disableFrameRendering();
	_isLoaded = false;
}