#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateModelMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuModel")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
				return;
			}
			else if (screen->getButton("place")->isHovered()) // Place model button
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuModelPlace");
			}
			else if (screen->getButton("choice")->isHovered()) // Choose model button
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuModelChoice");

				// Clear all buttons from scrolling list
				_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->getScrollingList("modelList")->deleteButtons();

				// Add the ID of every placed model
				auto IDs = _fe3d.modelEntity_getAllIDs();
				sort(IDs.begin(), IDs.end());
				for (auto& modelID : IDs)
				{
					// Check if model is not a preview model
					if (modelID[0] != '@')
					{
						// Removing the unique number from the modelID
						reverse(modelID.begin(), modelID.end());
						string rawID = modelID.substr(modelID.find('_') + 1);
						reverse(rawID.begin(), rawID.end());
						reverse(modelID.begin(), modelID.end());

						// Add new button
						_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->
							getScrollingList("modelList")->createButton(modelID, rawID);
					}
				}
			}
		}
	}
}

void SceneEditor::_updateModelPlacingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuModelPlace")
	{
		// Check if input received
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuModel");
				return;
			}
			else
			{
				// Iterate through every created model
				for (const auto& modelID : _modelEditor.getLoadedModelIDs())
				{
					// Check if model has mesh
					if (_fe3d.modelEntity_isExisting(modelID))
					{
						// Check if button is hovered
						if (screen->getScrollingList("modelList")->getButton(modelID)->isHovered())
						{
							// Set new preview model
							_currentPreviewModelID = modelID;
							_fe3d.modelEntity_setPosition(_currentPreviewModelID, Vec3(0.0f));
							_fe3d.modelEntity_setVisible(_currentPreviewModelID, true);
							auto textEntityID = _gui.getGlobalScreen()->getTextfield("selectedModelID")->getEntityID();
							_fe3d.textEntity_setVisible(textEntityID, true);
							_fe3d.textEntity_setTextContent(textEntityID, "Model: " + _currentPreviewModelID.substr(1), 0.025f);
							_fe3d.misc_centerCursor();

							// Add position value forms for placing without terrain
							if (_fe3d.terrainEntity_getSelectedID().empty())
							{
								_gui.getGlobalScreen()->createValueForm("positionX", "X", 0.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
								_gui.getGlobalScreen()->createValueForm("positionY", "Y", 0.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
								_gui.getGlobalScreen()->createValueForm("positionZ", "Z", 0.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
							}

							// Disable model choosing
							break;
						}
					}
				}
			}
		}
	}
}

void SceneEditor::_updateModelChoosingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// GUI management
	if (screen->getID() == "sceneEditorMenuModelChoice")
	{
		// Remove deleted models from the scrollingList buttons
		for (const auto& button : _gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->getScrollingList("modelList")->getButtons())
		{
			// Check if model is still existing
			if (!_fe3d.modelEntity_isExisting(button->getID()))
			{
				// Delete button
				_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuModelChoice")->getScrollingList("modelList")->deleteButton(button->getID());
				break;
			}
		}

		// Iterate through every placed model
		for (const auto& modelID : _fe3d.modelEntity_getAllIDs())
		{
			// Check if model is not a preview model
			if (modelID[0] != '@')
			{
				// Check if button is hovered
				if (screen->getScrollingList("modelList")->getButton(modelID)->isHovered())
				{
					// Check if LMB pressed (activation)
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateModel(modelID);
					}
					else // Hovering (selection)
					{
						_dontResetSelectedModel = true;
						_selectModel(modelID);
					}

					break;
				}
			}
		}

		// Back button
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuModel");
				_currentPreviewModelID = "";
				return;
			}
		}
	}
}