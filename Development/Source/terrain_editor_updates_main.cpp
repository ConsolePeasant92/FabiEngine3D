#include "terrain_editor.hpp"
#include "logger.hpp"

void TerrainEditor::update()
{
	if (_isEditorLoaded)
	{
		_updateMainMenu();
		_updateChoiceMenu();
		_updateMeshMenu();
		_updateBlendMapMenu();
		_updateLightingMenu();
		_updateTerrainCreating();
		_updateTerrainChoosing();
		_updateTerrainDeleting();
		_updateCamera();
		_updateMiscellaneous();
	}
}

void TerrainEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "terrainEditorMenuMain")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getGlobalScreen()->createAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
			}
			else if (screen->getButton("add")->isHovered())
			{
				_isCreatingTerrain = true;
				_gui.getGlobalScreen()->createValueForm("terrainCreate", "New Terrain Name", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				_isChoosingTerrain = true;
				_isEditingTerrain = true;
				auto IDs = getLoadedTerrainIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->createChoiceForm("terrainList", "Select Terrain", Vec2(0.0f, 0.1f), IDs);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_isChoosingTerrain = true;
				_isDeletingTerrain = true;
				auto IDs = getLoadedTerrainIDs();
				for (auto& name : IDs) { name = name.substr(1); }
				_gui.getGlobalScreen()->createChoiceForm("terrainList", "Select Terrain", Vec2(0.0f, 0.1f), IDs);
			}
		}

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
		{
			saveTerrainEntitiesToFile();
			unload();
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("exit"))
		{
			unload();
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
		}
	}
}

void TerrainEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "terrainEditorMenuChoice")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuMain");
				_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(), false);
				_fe3d.terrainEntity_setWireFramed(_currentTerrainID, false);
				_fe3d.terrainEntity_select("");
				_currentTerrainID = "";
				_isEditingTerrain = false;
				return;
			}
			else if (screen->getButton("mesh")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuMesh");
			}
			else if (screen->getButton("blendMap")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuBlendMap");
			}
			else if (screen->getButton("lighting")->isHovered())
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuLighting");
			}
		}
	}
}

void TerrainEditor::_updateTerrainCreating()
{
	if (_isCreatingTerrain)
	{
		string newTerrainID;

		// Create new terrain
		if (_gui.getGlobalScreen()->checkValueForm("terrainCreate", newTerrainID, {}))
		{
			// @ sign not allowed
			if (newTerrainID.find('@') == string::npos)
			{
				// Spaces not allowed
				if (newTerrainID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newTerrainID = "@" + newTerrainID;

					// If terrain ID not existing yet
					if (find(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end(), newTerrainID) == _loadedTerrainIDs.end())
					{
						// Get the chosen filename
						const string rootDirectory = _fe3d.misc_getRootDirectory();
						const string targetDirectory = string("game_assets\\textures\\height_maps\\");
						const string filePath = _fe3d.misc_getWinExplorerFilename(targetDirectory, "BMP");

						// Check if user chose a filename
						if (filePath.empty())
						{
							_isCreatingTerrain = false;
							return;
						}
						else
						{
							// Check if user did not switch directory
							if (filePath.size() > (rootDirectory.size() + targetDirectory.size()) &&
								filePath.substr(rootDirectory.size(), targetDirectory.size()) == targetDirectory)
							{
								const string newFilePath = filePath.substr(rootDirectory.size());
								_fe3d.misc_clearBitmapCache(newFilePath);
								_fe3d.terrainEntity_create(newTerrainID, newFilePath);
								_fe3d.terrainEntity_select(newTerrainID);
							}
							else
							{
								Logger::throwWarning("Invalid filepath, directory switching not allowed!");
								_isCreatingTerrain = false;
								return;
							}
						}

						// Miscellaneous
						_currentTerrainID = newTerrainID;
						_loadedTerrainIDs.push_back(_currentTerrainID);
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(),
							"Terrain: " + _currentTerrainID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(), true);
						_isCreatingTerrain = false;
						_isEditingTerrain = true;
					}
					else
					{
						Logger::throwWarning("Terrain name \"" + newTerrainID.substr(1) + "\" already exists!");
					}
				}
				else
				{
					Logger::throwWarning("Terrain name cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("Terrain name cannot contain '@'!");
			}
		}
	}
}

void TerrainEditor::_updateTerrainChoosing()
{
	if (_isChoosingTerrain)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("terrainList");

		// Hide last terrain
		_fe3d.terrainEntity_select("");

		// Check if a terrain name is hovered
		if (selectedButtonID != "")
		{
			// Show terrain
			_fe3d.terrainEntity_select("@" + selectedButtonID);

			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select terrain
				_currentTerrainID = "@" + selectedButtonID;

				// Check if going to editor
				if (_isEditingTerrain)
				{
					// Go to editor screen
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

					// Show terrain name
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(),
						"Terrain: " + _currentTerrainID.substr(1), 0.025f);
					_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedTerrainName")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
				_isChoosingTerrain = false;
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("terrainList")) // Cancelled choosing
		{
			_isChoosingTerrain = false;
			_isEditingTerrain = false;
			_isDeletingTerrain = false;
			_gui.getGlobalScreen()->deleteChoiceForm("terrainList");
		}
	}
}

void TerrainEditor::_updateTerrainDeleting()
{
	if (_isDeletingTerrain && _currentTerrainID != "")
	{
		// Add answer form
		if (!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", Vec2(0.0f, 0.25f));
		}

		// Check if form is answered
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Delete entity
			_fe3d.terrainEntity_delete(_currentTerrainID);

			// Delete from name record
			_loadedTerrainIDs.erase(remove(_loadedTerrainIDs.begin(), _loadedTerrainIDs.end(), _currentTerrainID), _loadedTerrainIDs.end());
			_isDeletingTerrain = false;
			_currentTerrainID = "";
		}
		else if (_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_fe3d.terrainEntity_select("");
			_isDeletingTerrain = false;
			_currentTerrainID = "";
		}
	}
}