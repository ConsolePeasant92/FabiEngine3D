#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateReflectionMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuReflection")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			// Reset placing
			if (_isPlacingReflection)
			{
				_fe3d.modelEntity_setVisible(PREVIEW_CAMERA_ID, false);
				_isPlacingReflection = false;
			}

			// Miscellaneous
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuChoice");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			// Deactivate everything
			_deactivateModel();
			_deactivateBillboard();
			_deactivateSound();
			_deactivatePoinlight();
			_deactivateReflection();

			// Set new preview reflection
			_isPlacingReflection = true;
			_fe3d.modelEntity_setVisible(PREVIEW_CAMERA_ID, true);
			_fe3d.reflectionEntity_setPosition(PREVIEW_CAMERA_ID, Vec3(0.0f));
			_fe3d.misc_centerCursor();

			// Add position value forms for placing without terrain
			if (_fe3d.terrainEntity_getSelectedID().empty())
			{
				_gui.getGlobalScreen()->createValueForm("positionX", "X", 0.0f, Vec2(-0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("positionY", "Y", 0.0f, Vec2(0.0f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
				_gui.getGlobalScreen()->createValueForm("positionZ", "Z", 0.0f, Vec2(0.25f, 0.1f), Vec2(0.15f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuReflectionChoice");

			// Clear all buttons from scrolling list
			_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuReflectionChoice")->getScrollingList("reflections")->deleteButtons();

			// Add the ID of every placed reflection
			auto IDs = _fe3d.reflectionEntity_getAllIDs();
			sort(IDs.begin(), IDs.end());
			for (auto& reflectionID : IDs)
			{
				// Check if reflection is not a preview
				if (reflectionID[0] != '@')
				{
					// Removing the unique number from the ID
					reverse(reflectionID.begin(), reflectionID.end());
					string rawID = reflectionID.substr(reflectionID.find('_') + 1);
					reverse(rawID.begin(), rawID.end());
					reverse(reflectionID.begin(), reflectionID.end());

					// Add new button
					_gui.getViewport("left")->getWindow("main")->getScreen("sceneEditorMenuReflectionChoice")->getScrollingList("reflections")->createButton(reflectionID, rawID);
				}
			}
		}
	}
}

void SceneEditor::_updateReflectionChoosingMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "sceneEditorMenuReflectionChoice")
	{
		// Remove deleted reflections from the scrollingList buttons
		for (const auto& button : screen->getScrollingList("reflections")->getButtons())
		{
			// Check if reflection is still existing
			if (!_fe3d.reflectionEntity_isExisting(button->getID()))
			{
				// Delete button
				screen->getScrollingList("reflections")->deleteButton(button->getID());
				break;
			}
		}

		// Iterate through every placed reflection
		for (const auto& reflectionID : _fe3d.reflectionEntity_getAllIDs())
		{
			// Check if reflection is not a preview
			if (reflectionID[0] != '@')
			{
				// Check if button is hovered
				if (screen->getScrollingList("reflections")->getButton(reflectionID)->isHovered())
				{
					// Check if LMB pressed (activation)
					if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						_activateReflection(reflectionID);
					}
					else // Hovering (selection)
					{
						_dontResetSelectedCamera = true;
						_selectReflection(reflectionID);
					}

					break;
				}
			}
		}

		// Back button
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("sceneEditorMenuReflection");
			return;
		}
	}
}