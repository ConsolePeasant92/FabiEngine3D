#include "environment_editor.hpp"

#include <algorithm>

void EnvironmentEditor::_updateTerrainMenuBlendMap()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "terrainEditorMenuBlendMap")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			}
			else if (screen->getButton("blendMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\blend_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setBlendMap(_currentTerrainID, newFilePath);
						_fe3d.terrainEntity_setBlendMapped(_currentTerrainID, true);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("red")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setDiffuseMapR(_currentTerrainID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("green")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setDiffuseMapG(_currentTerrainID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("blue")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\diffuse_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setDiffuseMapB(_currentTerrainID, newFilePath);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("redRepeat")->isHovered())
			{
				float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(_currentTerrainID);
				_gui.getGlobalScreen()->addValueForm("redRepeat", "Red repeat", blendRepeatR, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("greenRepeat")->isHovered())
			{
				float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(_currentTerrainID);
				_gui.getGlobalScreen()->addValueForm("greenRepeat", "Green repeat", blendRepeatG, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("blueRepeat")->isHovered())
			{
				float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(_currentTerrainID);
				_gui.getGlobalScreen()->addValueForm("blueRepeat", "Blue repeat", blendRepeatB, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
		}

		// Check if redRepeat confirmed
		float blendRepeatR = _fe3d.terrainEntity_getBlendRepeatR(_currentTerrainID);
		if (_gui.getGlobalScreen()->checkValueForm("redRepeat", blendRepeatR))
		{
			blendRepeatR = std::max(0.0f, blendRepeatR);
			_fe3d.terrainEntity_setBlendRepeatR(_currentTerrainID, blendRepeatR);
		}

		// Check if greenRepeat confirmed
		float blendRepeatG = _fe3d.terrainEntity_getBlendRepeatG(_currentTerrainID);
		if (_gui.getGlobalScreen()->checkValueForm("greenRepeat", blendRepeatG))
		{
			blendRepeatG = std::max(0.0f, blendRepeatG);
			_fe3d.terrainEntity_setBlendRepeatG(_currentTerrainID, blendRepeatG);
		}

		// Check if blueRepeat confirmed
		float blendRepeatB = _fe3d.terrainEntity_getBlendRepeatB(_currentTerrainID);
		if (_gui.getGlobalScreen()->checkValueForm("blueRepeat", blendRepeatB))
		{
			blendRepeatB = std::max(0.0f, blendRepeatB);
			_fe3d.terrainEntity_setBlendRepeatB(_currentTerrainID, blendRepeatB);
		}

		// Filling statuses
		bool loadedBlendMap = _fe3d.terrainEntity_getBlendMapPath(_currentTerrainID)  != "";
		bool loadedRedTex   = _fe3d.terrainEntity_getBlendMapPathR(_currentTerrainID) != "";
		bool loadedGreenTex = _fe3d.terrainEntity_getBlendMapPathG(_currentTerrainID) != "";
		bool loadedBlueTex  = _fe3d.terrainEntity_getBlendMapPathB(_currentTerrainID) != "";

		// Button hoverability
		screen->getButton("red")->setHoverable(loadedBlendMap);
		screen->getButton("green")->setHoverable(loadedBlendMap);
		screen->getButton("blue")->setHoverable(loadedBlendMap);
		screen->getButton("redRepeat")->setHoverable(loadedBlendMap && loadedRedTex);
		screen->getButton("greenRepeat")->setHoverable(loadedBlendMap && loadedGreenTex);
		screen->getButton("blueRepeat")->setHoverable(loadedBlendMap && loadedBlueTex);
	}
}

void EnvironmentEditor::_updateTerrainMenuLighting()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "terrainEditorMenuLighting")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
			}
			else if (screen->getButton("normalMap")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\normal_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setNormalMap(_currentTerrainID, newFilePath);
						_fe3d.terrainEntity_setNormalMapped(_currentTerrainID, true);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("normalMapR")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\normal_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setNormalMapR(_currentTerrainID, newFilePath);
						_fe3d.terrainEntity_setNormalMappedR(_currentTerrainID, true);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("normalMapG")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\normal_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setNormalMapG(_currentTerrainID, newFilePath);
						_fe3d.terrainEntity_setNormalMappedG(_currentTerrainID, true);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("normalMapB")->isHovered())
			{
				// Get the chosen filename
				const string rootDirectory = _fe3d.misc_getRootDirectory();
				const string targetDirectory = string("game_assets\\textures\\normal_maps\\");
				const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "PNG");

				// Check if user chose a filename
				if (filePath != "")
				{
					// Check if user did not switch directory
					if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
						filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
					{
						const string newFilePath = filePath.substr(rootDirectory.size());
						_fe3d.misc_clearTextureCache2D(newFilePath);
						_fe3d.terrainEntity_setNormalMapB(_currentTerrainID, newFilePath);
						_fe3d.terrainEntity_setNormalMappedB(_currentTerrainID, true);
					}
					else
					{
						_fe3d.logger_throwWarning("Invalid filepath, directory switching not allowed!");
					}
				}
			}
			else if (screen->getButton("isSpecular")->isHovered())
			{
				_fe3d.terrainEntity_setSpecularLighted(_currentTerrainID, !_fe3d.terrainEntity_isSpecularLighted(_currentTerrainID));
			}
			else if (screen->getButton("specularFactor")->isHovered())
			{
				float factor = _fe3d.terrainEntity_getSpecularLightingFactor(_currentTerrainID);
				_gui.getGlobalScreen()->addValueForm("specularFactor", "Specular factor", factor, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("specularIntensity")->isHovered())
			{
				float intensity = _fe3d.terrainEntity_getSpecularLightingIntensity(_currentTerrainID);
				_gui.getGlobalScreen()->addValueForm("specularIntensity", "Specular intensity", intensity * 100.0f, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("lightness")->isHovered())
			{
				float lightness = _fe3d.terrainEntity_getLightness(_currentTerrainID);
				_gui.getGlobalScreen()->addValueForm("lightness", "Lightness", lightness * 100.0f, Vec2(0.0f), Vec2(0.15f, 0.1f));
			}
		}

		// Buttons hoverability
		bool specularLighted = _fe3d.terrainEntity_isSpecularLighted(_currentTerrainID);
		screen->getButton("specularFactor")->setHoverable(specularLighted);
		screen->getButton("specularIntensity")->setHoverable(specularLighted);

		// Update specular button content
		auto specularID = screen->getButton("isSpecular")->getTextfield()->getEntityID();
		auto isSpecular = _fe3d.terrainEntity_isSpecularLighted(_currentTerrainID);
		_fe3d.textEntity_setTextContent(specularID, isSpecular ? "Specular: ON" : "Specular: OFF");

		// Check if specular factor confirmed
		float factor = _fe3d.terrainEntity_getSpecularLightingFactor(_currentTerrainID);
		if (_gui.getGlobalScreen()->checkValueForm("specularFactor", factor))
		{
			factor = std::clamp(factor, 0.0f, 256.0f);
			_fe3d.terrainEntity_setSpecularLightingFactor(_currentTerrainID, factor);
		}

		// Check if specular intensity confirmed
		float intensity = _fe3d.terrainEntity_getSpecularLightingIntensity(_currentTerrainID);
		if (_gui.getGlobalScreen()->checkValueForm("specularIntensity", intensity))
		{
			intensity = std::max(0.0f, intensity / 100.0f);
			_fe3d.terrainEntity_setSpecularLightingIntensity(_currentTerrainID, intensity);
		}

		// Check if lightness confirmed
		float lightness = _fe3d.terrainEntity_getLightness(_currentTerrainID);
		if (_gui.getGlobalScreen()->checkValueForm("lightness", lightness))
		{
			lightness = std::max(0.0f, lightness / 100.0f);
			_fe3d.terrainEntity_setLightness(_currentTerrainID, lightness);
		}
	}
}