#include "model_editor.hpp"

#include <algorithm>

void ModelEditor::_updateModelEditingAabb()
{
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	if(screen->getID() == "modelEditorMenuAabb")
	{
		// Temporary values
		Vec3 currentSize = _fe3d.modelEntity_getSize(_currentModelID);

		// GUI management
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
			{
				_isMovingToggled = false;
				_isResizingToggled = false;
				_transformationDirection = Direction::X;
				_currentAabbID = "";
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
				_fe3d.misc_disableAabbFrameRendering();
				_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID());
			}
			else if (screen->getButton("add")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("newAabbName", "New AABB name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
			}
			else if (screen->getButton("edit")->isHovered())
			{
				// Retrieve all AABB names of this model
				vector<string> aabbNames = _fe3d.aabbEntity_getBoundIDs(_currentModelID, true, false);
				for (auto& name : aabbNames)
				{
					name = name.substr(string(_currentModelID + "@").size());
				}
				std::sort(aabbNames.begin(), aabbNames.end());

				// Show choicelist
				_gui.getGlobalScreen()->addChoiceForm("aabbList", "Select AABB", Vec2(-0.4f, 0.1f), aabbNames);
			}
			else if (screen->getButton("delete")->isHovered())
			{
				_isMovingToggled = false;
				_isResizingToggled = false;
				_transformationDirection = Direction::X;
				_fe3d.aabbEntity_delete(_currentModelID + "@" + _currentAabbID);
				_currentAabbID = "";
				_fe3d.textEntity_hide(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID());
			}
			else if (screen->getButton("speed")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("speed", "Transformation speed", _aabbTransformationSpeed * 100.0f, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
			}
			else if (screen->getButton("toggleMove")->isHovered())
			{
				_isMovingToggled = !_isMovingToggled;

				// Toggle box move
				string newContent = _isResizingToggled ? "Box move: ON" : "Box move: OFF";
				_fe3d.textEntity_setTextContent(screen->getButton("toggleMove")->getTextfield()->getEntityID(), newContent);
			}
			else if (screen->getButton("toggleResize")->isHovered())
			{
				_isResizingToggled = !_isResizingToggled;

				// Toggle box resize
				string newContent = _isResizingToggled ? "Box resize: ON" : "Box resize: OFF";
				_fe3d.textEntity_setTextContent(screen->getButton("toggleResize")->getTextfield()->getEntityID(), newContent);
			}
			else if (screen->getButton("direction")->isHovered())
			{
				// Change direction
				_transformationDirection = (_transformationDirection == Direction::X) ? Direction::Y :
					(_transformationDirection == Direction::Y) ? Direction::Z : Direction::X;
			}
		}
	}

	// Buttons hoverability
	bool isHoverable = (_currentAabbID != "");
	screen->getButton("delete")->setHoverable(isHoverable);
	screen->getButton("toggleMove")->setHoverable(isHoverable);
	screen->getButton("toggleResize")->setHoverable(isHoverable);
	screen->getButton("direction")->setHoverable(isHoverable);

	// Update AABB visibility
	for (const auto& entityID : _fe3d.aabbEntity_getAllIDs())
	{
		if (entityID == (_currentModelID + "@" + _currentAabbID))
		{
			_fe3d.aabbEntity_show(entityID);
		}
		else
		{
			_fe3d.aabbEntity_hide(entityID);
		}
	}

	// Update button contents
	string directions[3] = { "X", "Y", "Z" };
	string newContent = "Direction: " + directions[int(_transformationDirection)];
	_fe3d.textEntity_setTextContent(screen->getButton("direction")->getTextfield()->getEntityID(), newContent);
	_fe3d.textEntity_setTextContent(screen->getButton("toggleMove")->getTextfield()->getEntityID(), _isMovingToggled ? "Box move: ON" : "Box move: OFF");
	_fe3d.textEntity_setTextContent(screen->getButton("toggleResize")->getTextfield()->getEntityID(), _isResizingToggled ? "Box resize: ON" : "Box resize: OFF");

	// Filling transformation speed
	if (_gui.getGlobalScreen()->checkValueForm("speed", _aabbTransformationSpeed, { }))
	{
		_aabbTransformationSpeed /= 100.0f;
	}

	// Create AABB
	string newAabbName;
	if (_gui.getGlobalScreen()->checkValueForm("newAabbName", newAabbName, {}))
	{
		if (_fe3d.aabbEntity_isExisting(_currentModelID + "@" + newAabbName)) // Check if already exists
		{
			_fe3d.logger_throwWarning("AABB name \"" + newAabbName + "\" of model with ID \"" + _currentModelID.substr(1) + "\" already exists!");
		}
		else
		{
			// @ sign not allowed
			if (newAabbName.find('@') == string::npos)
			{
				// Spaces not allowed
				if (newAabbName.find(' ') == string::npos)
				{
					// Add new AABB
					_fe3d.aabbEntity_bindToModelEntity(_currentModelID, Vec3(0.0f), Vec3(1.0f), true, true, _currentModelID + "@" + newAabbName);
					_currentAabbID = newAabbName;

					// Reset editing
					_isMovingToggled = false;
					_isResizingToggled = false;
					_transformationDirection = Direction::X;

					// Show AABB title
					_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID(),
						"AABB: " + _currentAabbID, 0.025f);
					_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID());
				}
				else
				{
					_fe3d.logger_throwWarning("New AABB name cannot contain any spaces!");
				}
			}
			else
			{
				_fe3d.logger_throwWarning("New AABB name cannot contain '@'!");
			}
		}
	}

	// Choose AABB
	if (_gui.getGlobalScreen()->isChoiceFormExisting("aabbList"))
	{
		string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("aabbList");
		string hoveredAabbID = "";

		// Hide every AABB
		for (const auto& entityID : _fe3d.aabbEntity_getAllIDs())
		{
			_fe3d.aabbEntity_hide(entityID);
		}

		// Check if a AABB name is hovered
		if (selectedButtonID != "")
		{
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // Clicked
			{
				// Set current AABB
				_currentAabbID = selectedButtonID;

				// Reset editing
				_isMovingToggled = false;
				_isResizingToggled = false;
				_transformationDirection = Direction::X;

				// Show AABB title
				_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID(),
					"AABB: " + _currentAabbID, 0.025f);
				_fe3d.textEntity_show(_gui.getGlobalScreen()->getTextfield("selectedAabbName")->getEntityID());
				_gui.getGlobalScreen()->removeChoiceForm("aabbList");
			}
			else
			{
				hoveredAabbID = selectedButtonID;
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("aabbList")) // Cancelled choosing
		{
			_gui.getGlobalScreen()->removeChoiceForm("aabbList");
		}

		// Show hovered AABB
		if (hoveredAabbID != "")
		{
			_fe3d.aabbEntity_show(_currentModelID + "@" + hoveredAabbID);
		}
	}

	// Check if currently editing an AABB
	if (_currentAabbID != "" && !_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update moving through cursor
		if (_isMovingToggled)
		{
			float scrollingDirection = static_cast<float>(_fe3d.input_getMouseWheelY());
			Vec3 newPosition = _fe3d.aabbEntity_getPosition(_currentModelID + "@" + _currentAabbID);

			// Determine direction
			switch (_transformationDirection)
			{
				case Direction::X:
					newPosition.x += _aabbTransformationSpeed * scrollingDirection;
					break;

				case Direction::Y:
					newPosition.y += _aabbTransformationSpeed * scrollingDirection;
					break;

				case Direction::Z:
					newPosition.z += _aabbTransformationSpeed * scrollingDirection;
					break;
			}

			// Apply new size
			_fe3d.aabbEntity_setPosition(_currentModelID + "@" + _currentAabbID, newPosition);
		}

		// Update resizing through cursor
		if (_isResizingToggled)
		{
			float scrollingDirection = static_cast<float>(_fe3d.input_getMouseWheelY());
			Vec3 newSize = _fe3d.aabbEntity_getSize(_currentModelID + "@" + _currentAabbID);

			// Check if able to scroll
			if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
			{
				switch (_transformationDirection)
				{
					case Direction::X:
					{
						newSize.x += (_aabbTransformationSpeed * scrollingDirection);
						break;
					}

					case Direction::Y:
					{
						newSize.y += (_aabbTransformationSpeed * scrollingDirection);
						break;
					}

					case Direction::Z:
					{
						newSize.z += (_aabbTransformationSpeed * scrollingDirection);
						break;
					}
				}
			}

			// Apply new size
			_fe3d.aabbEntity_setSize(_currentModelID + "@" + _currentAabbID, newSize);
		}
	}
}