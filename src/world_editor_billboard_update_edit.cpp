#include "world_editor.hpp"

void WorldEditor::_updateBillboardEditing()
{
	// Temporary values
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	// Reset selected billboard from last frame
	if(!_dontResetSelectedBillboard)
	{
		_selectedBillboardID = "";
	}
	else
	{
		_dontResetSelectedBillboard = false;
	}

	// User must not be placing anything
	if(_currentPreviewModelID.empty() && _currentPreviewBillboardID.empty() && _currentPreviewSoundID.empty() && !_isPlacingPointlight && !_isPlacingReflection)
	{
		// Check if user selected a billboard
		for(const auto& ID : _fe3d.billboard_getIDs())
		{
			// Must not be preview entity
			if(ID[0] != '@')
			{
				// Check which entity is selected
				auto hoveredAabbID = _fe3d.raycast_checkCursorInAny().first;
				bool hovered = (hoveredAabbID.size() >= ID.size()) && (hoveredAabbID.substr(0, ID.size()) == ID);

				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if(hovered && _fe3d.misc_isCursorInsideViewport() &&
				   !_gui.getGlobalScreen()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Select hovered billboard
					_selectBillboard(ID);

					// Check if user clicked billboard
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same billboard is not clicked again
						if(_selectedBillboardID != _activeBillboardID)
						{
							_activateBillboard(_selectedBillboardID);
						}
					}
				}
				else
				{
					// Unselect if necessary
					if((ID != _selectedBillboardID) && (ID != _activeBillboardID))
					{
						_unselectBillboard(ID);
					}
				}
			}
		}

		// Check if RMB not down
		if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check if allowed by GUI
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getGlobalScreen()->isFocused())
			{
				// Check if billboard is active
				if(!_activeBillboardID.empty())
				{
					// Check if active billboard cancelled
					if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedBillboardID.empty()) || _fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeBillboardID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		// Update billboard highlighting
		if(_selectedBillboardID != _activeBillboardID)
		{
			_updateBillboardHighlighting(_selectedBillboardID, _selectedBillboardHighlightDirection);
		}
		_updateBillboardHighlighting(_activeBillboardID, _activeBillboardHighlightDirection);

		// Update properties screen
		if(!_activeBillboardID.empty())
		{
			// Temporary values
			auto screen = rightWindow->getScreen("billboardPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("billboardPropertiesMenu");

			// Button management
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(false);
					screen->getButton("rotation")->setHoverable(true);
					screen->getButton("size")->setHoverable(true);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(false);
					screen->getButton("size")->setHoverable(true);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
				{
					// Update buttons hoverability
					screen->getButton("position")->setHoverable(true);
					screen->getButton("rotation")->setHoverable(true);
					screen->getButton("size")->setHoverable(false);
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("freeze")->isHovered())
				{
					_fe3d.billboard_setFrozen(_activeBillboardID, !_fe3d.billboard_isFrozen(_activeBillboardID));
				}
				else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d.billboard_delete(_activeBillboardID);
					rightWindow->setActiveScreen("main");
					_activeBillboardID = "";
					return;
				}
			}

			// Alternative way of deleting
			if(_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.billboard_delete(_activeBillboardID);
				rightWindow->setActiveScreen("main");
				_activeBillboardID = "";
				return;
			}

			// Get current values
			auto position = _fe3d.billboard_getPosition(_activeBillboardID);
			auto rotation = _fe3d.billboard_getRotation(_activeBillboardID);
			auto size = _fe3d.billboard_getSize(_activeBillboardID);

			// Enabling all axes by default
			screen->getButton("xMinus")->setHoverable(true);
			screen->getButton("xPlus")->setHoverable(true);
			screen->getWriteField("x")->setHoverable(true);
			screen->getButton("yMinus")->setHoverable(true);
			screen->getButton("yPlus")->setHoverable(true);
			screen->getWriteField("y")->setHoverable(true);
			screen->getButton("zMinus")->setHoverable(true);
			screen->getButton("zPlus")->setHoverable(true);
			screen->getWriteField("z")->setHoverable(true);

			// Disabling Z axis for scaling operations on a billboard
			if(!screen->getButton("size")->isHoverable())
			{
				screen->getButton("zMinus")->setHoverable(false);
				screen->getButton("zPlus")->setHoverable(false);
				screen->getWriteField("z")->setHoverable(false);
			}

			// Handle position, rotation, size
			if(!screen->getButton("position")->isHoverable())
			{
				_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
				_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
				_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
				_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
				_handleValueChanging("billboardPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
				_handleValueChanging("billboardPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));
				_fe3d.billboard_setPosition(_activeBillboardID, position);
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", rotation.x, (_editorSpeed / 25.0f));
				_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", rotation.x, -(_editorSpeed / 25.0f));
				_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", rotation.y, (_editorSpeed / 25.0f));
				_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", rotation.y, -(_editorSpeed / 25.0f));
				_handleValueChanging("billboardPropertiesMenu", "zPlus", "z", rotation.z, (_editorSpeed / 25.0f));
				_handleValueChanging("billboardPropertiesMenu", "zMinus", "z", rotation.z, -(_editorSpeed / 25.0f));
				_fe3d.billboard_setRotation(_activeBillboardID, rotation);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleValueChanging("billboardPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("billboardPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / 100.0f), BILLBOARD_SIZE_MULTIPLIER, 0.0f);
				_fe3d.billboard_setSize(_activeBillboardID, size);
			}

			// Update button text contents
			screen->getButton("freeze")->changeTextContent(_fe3d.billboard_isFrozen(_activeBillboardID) ? "Unfreeze" : "Freeze");
		}

		// Check if billboard is still selected or active
		if(_selectedBillboardID.empty() && _activeBillboardID.empty())
		{
			_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("billboardID")->getEntityID(), false);
		}
	}
}