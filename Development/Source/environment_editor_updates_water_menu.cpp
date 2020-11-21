#include "environment_editor.hpp"

#include <algorithm>

void EnvironmentEditor::_updateWaterMenuMain()
{
	if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "waterEditorMenuMain")
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("waterEditorMenuMain");

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("create")->isHovered())
			{
				_waterCreationEnabled = true;
				_gui.getGlobalScreen()->addValueForm("newWaterName", "New water name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_waterChoosingEnabled = true;
				_waterEditingEnabled = true;
				for (auto& name : _waterNames) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("waterList", "Select water", Vec2(-0.4f, 0.1f), _waterNames);
				for (auto& name : _waterNames) { name = "@" + name; }
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_waterChoosingEnabled = true;
				_waterRemovalEnabled = true;
				for (auto& name : _waterNames) { name = name.substr(1); }
				_gui.getGlobalScreen()->addChoiceForm("waterList", "Select water", Vec2(-0.4f, 0.1f), _waterNames);
				for (auto& name : _waterNames) { name = "@" + name; }
			}
			else if (screen->getButton("back")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("environmentEditorMenu");
				_currentEnvironmentType = EnvironmentType::NONE;
			}
		}
	}
}

void EnvironmentEditor::_updateWaterMenuChoice()
{
	if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "waterEditorMenuChoice")
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("waterEditorMenuChoice");

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("mesh")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMesh");
			}
			else if (screen->getButton("effects")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuEffects");
			}
			else if (screen->getButton("options")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuOptions");
			}
			else if (screen->getButton("back")->isHovered())
			{
				_fe3d.camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f));
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuMain");
				_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedWaterName")->getEntityID());
				_fe3d.waterEntity_select("");
				_currentWaterID = "";
				_waterEditingEnabled = false;
			}
		}

		// Screen hoverabilities
		screen->getButton("effects")->setHoverable(_fe3d.waterEntity_isExisting(_currentWaterID));
		screen->getButton("options")->setHoverable(_fe3d.waterEntity_isExisting(_currentWaterID));
	}
}

void EnvironmentEditor::_updateWaterMenuMesh()
{
	if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "waterEditorMenuMesh")
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("waterEditorMenuMesh");
		Vec3 waterPosition = _fe3d.waterEntity_getPosition(_currentWaterID);
		float waterSize = _fe3d.waterEntity_getSize(_currentWaterID);

		// Button hoverabilities
		screen->getButton("up")->setHoverable(_fe3d.waterEntity_isExisting(_currentWaterID));
		screen->getButton("down")->setHoverable(_fe3d.waterEntity_isExisting(_currentWaterID));

		// Pressed LMB
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("position")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("positionX", "X", waterPosition.x, Vec2(-0.25f, 0.0f), Vec2(0.2f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("positionY", "Y", waterPosition.y, Vec2(0.0f, 0.0f), Vec2(0.2f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("positionZ", "Z", waterPosition.z, Vec2(0.25f, 0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("size")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("size", "Size", waterSize, Vec2(0.0f), Vec2(0.3f, 0.1f));
			}			
			else if (screen->getButton("back")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			}
		}

		// Holding LMB
		if (_fe3d.input_getMouseDown(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("up")->isHovered())
			{
				_fe3d.waterEntity_setPosition(_currentWaterID, waterPosition + Vec3(0.0f, 0.1f, 0.0f));
			}
			else if (screen->getButton("down")->isHovered())
			{
				_fe3d.waterEntity_setPosition(_currentWaterID, waterPosition - Vec3(0.0f, 0.1f, 0.0f));
			}
		}

		// Update size changes
		if (_gui.getGlobalScreen()->checkValueForm("size", waterSize, { 0.0f }))
		{
			_fe3d.waterEntity_setSize(_currentWaterID, waterSize);
		}

		// Update position changes
		if 
		(
			_gui.getGlobalScreen()->checkValueForm("positionX", waterPosition.x, { }) ||
			_gui.getGlobalScreen()->checkValueForm("positionY", waterPosition.y, { }) ||
			_gui.getGlobalScreen()->checkValueForm("positionZ", waterPosition.z, { })
		)
		{
			_fe3d.waterEntity_setPosition(_currentWaterID, waterPosition);
		}
	}
}

void EnvironmentEditor::_updateWaterMenuEffects()
{
	if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "waterEditorMenuEffects")
	{
		// Variables
		auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("waterEditorMenuEffects");
		float uvRepeat = _fe3d.waterEntity_getUvRepeat(_currentWaterID);
		bool isReflective = _fe3d.waterEntity_isReflective(_currentWaterID);
		bool isRefractive = _fe3d.waterEntity_isRefractive(_currentWaterID);
		bool isWaving = _fe3d.waterEntity_isWaving(_currentWaterID);
		bool isRippling = _fe3d.waterEntity_isRippling(_currentWaterID);
		bool isSpecularLighted = _fe3d.waterEntity_isSpecularLighted(_currentWaterID);

		// Button hoverabilities
		string displacementMapPath = _fe3d.waterEntity_getDisplacementMapPath(_currentWaterID);
		string dudvMapPath = _fe3d.waterEntity_getDudvMapPath(_currentWaterID);
		string normalMapPath = _fe3d.waterEntity_getNormalMapPath(_currentWaterID);
		screen->getButton("isWaving")->setHoverable(displacementMapPath != "");
		screen->getButton("isRippling")->setHoverable(dudvMapPath != "");
		screen->getButton("isSpecular")->setHoverable(normalMapPath != "");

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("uvRepeat")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("uvRepeat", "UV repeat", uvRepeat, Vec2(0.0f), Vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("dudvMap")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\dudv_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache(newFilePath);
						_fe3d.waterEntity_setDudvMap(_currentWaterID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("normalMap")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\normal_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache(newFilePath);
						_fe3d.waterEntity_setNormalMap(_currentWaterID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("displaceMap")->isHovered())
			{
				// Get the loaded filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("user\\assets\\textures\\displacement_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache(newFilePath);
						_fe3d.waterEntity_setDisplacementMap(_currentWaterID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("isReflective")->isHovered())
			{
				isReflective = !isReflective;
				_fe3d.waterEntity_setReflective(_currentWaterID, isReflective);
			}
			else if (screen->getButton("isRefractive")->isHovered())
			{
				isRefractive = !isRefractive;
				_fe3d.waterEntity_setRefractive(_currentWaterID, isRefractive);
			}
			else if (screen->getButton("isWaving")->isHovered())
			{
				isWaving = !isWaving;
				_fe3d.waterEntity_setWaving(_currentWaterID, isWaving);
			}
			else if (screen->getButton("isRippling")->isHovered())	
			{
				isRippling = !isRippling;
				_fe3d.waterEntity_setRippling(_currentWaterID, isRippling);
			}
			else if (screen->getButton("isSpecular")->isHovered())
			{
				isSpecularLighted = !isSpecularLighted;
				_fe3d.waterEntity_setSpecularLighted(_currentWaterID, isSpecularLighted);
			}
			else if (screen->getButton("back")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			}
		}

		// Update GUI button contents
		auto reflectiveID = screen->getButton("isReflective")->getTextfield()->getEntityID();
		auto refractiveID = screen->getButton("isRefractive")->getTextfield()->getEntityID();
		auto wavingID = screen->getButton("isWaving")->getTextfield()->getEntityID();
		auto ripplingID = screen->getButton("isRippling")->getTextfield()->getEntityID();
		auto specularID = screen->getButton("isSpecular")->getTextfield()->getEntityID();
		_fe3d.textEntity_setTextContent(reflectiveID, isReflective ? "Reflective: ON" : "Reflective: OFF");
		_fe3d.textEntity_setTextContent(refractiveID, isRefractive ? "Refractive: ON" : "Refractive: OFF");
		_fe3d.textEntity_setTextContent(wavingID, isWaving ? "Waving: ON" : "Waving: OFF");
		_fe3d.textEntity_setTextContent(ripplingID, isRippling ? "Rippling: ON" : "Rippling: OFF");
		_fe3d.textEntity_setTextContent(specularID, isSpecularLighted ? "Specular: ON" : "Specular: OFF");

		// Update uvRepeat changes
		_gui.getGlobalScreen()->checkValueForm("uvRepeat", uvRepeat);
		_fe3d.waterEntity_setUvRepeat(_currentWaterID, uvRepeat);
	}
}

void EnvironmentEditor::_updateWaterMenuOptions()
{
	if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "waterEditorMenuOptions")
	{
		// Values
		auto screen = _gui.getViewport("left")->getWindow("main")->getScreen("waterEditorMenuOptions");
		Vec2 speed = _fe3d.waterEntity_getSpeed(_currentWaterID);
		float transparency = _fe3d.waterEntity_getTransparency(_currentWaterID);
		Vec3 color = _fe3d.waterEntity_getColor(_currentWaterID);
		float specularFactor = _fe3d.waterEntity_getSpecularLightingFactor(_currentWaterID);
		float specularIntensity = _fe3d.waterEntity_getSpecularLightingIntensity(_currentWaterID);
		float waveHeightFactor = _fe3d.waterEntity_getWaveHeightFactor(_currentWaterID);

		// GUI management
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (screen->getButton("speed")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("speedX", "X", speed.x * 100000.0f, Vec2(-0.15f, 0.0f), Vec2(0.2f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("speedZ", "Z", speed.y * 100000.0f, Vec2(0.15f, 0.0f), Vec2(0.2f, 0.1f));
			}
			else if (screen->getButton("transparency")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("transparency", "Transparency (0-100%)", transparency * 100.0f, Vec2(0.0f), Vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("color")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("colorR", "R(0-255)", color.r * 255.0f, Vec2(-0.25f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorG", "G(0-255)", color.g * 255.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				_gui.getGlobalScreen()->addValueForm("colorB", "B(0-255)", color.b * 255.0f, Vec2(0.25f, 0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("specularFactor")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("specularFactor", "Specular factor (0 - 256)", specularFactor, Vec2(0.0f), Vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("specularIntensity")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("specularIntensity", "Specular intensity (%)", specularIntensity * 100.0f, Vec2(0.0f), Vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("waveHeight")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("waveHeight", "Wave height factor (%)", waveHeightFactor * 100.0f, Vec2(0.0f), Vec2(0.3f, 0.1f));
			}
			else if (screen->getButton("back")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			}
		}

		// Check if speed X value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("speedX", speed.x))
		{
			speed.x /= 100000.0f;
			_fe3d.waterEntity_setSpeed(_currentWaterID, speed);
		}

		// Check if speed Z value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("speedZ", speed.y))
		{
			speed.y /= 100000.0f;
			_fe3d.waterEntity_setSpeed(_currentWaterID, speed);
		}
		
		// Check if transparency value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("transparency", transparency))
		{
			transparency = std::clamp(transparency / 100.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setTransparency(_currentWaterID, transparency);
		}

		// Check if color R value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("colorR", color.r))
		{
			color.r = std::clamp(color.r / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}

		// Check if color G value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("colorG", color.g))
		{
			color.g = std::clamp(color.g / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}

		// Check if color B value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("colorB", color.b))
		{
			color.b = std::clamp(color.b / 255.0f, 0.0f, 1.0f);
			_fe3d.waterEntity_setColor(_currentWaterID, color);
		}

		// Check if specular factor value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("specularFactor", specularFactor))
		{
			specularFactor = std::clamp(specularFactor, 0.0f, 256.0f);
			_fe3d.waterEntity_setSpecularLightingFactor(_currentWaterID, specularFactor);
		}

		// Check if specular intensity value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("specularIntensity", specularIntensity))
		{
			specularIntensity /= 100.0f;
			_fe3d.waterEntity_setSpecularLightingIntensity(_currentWaterID, specularIntensity);
		}

		// Check if wave height value confirmed
		if (_gui.getGlobalScreen()->checkValueForm("waveHeight", waveHeightFactor))
		{
			waveHeightFactor /= 100.0f;
			_fe3d.waterEntity_setWaveHeightFactor(_currentWaterID, waveHeightFactor);
		}
	}
}