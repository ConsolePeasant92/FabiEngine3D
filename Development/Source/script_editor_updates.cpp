#include "script_editor.hpp"

#include <algorithm>

void ScriptEditor::update()
{
	_updateGUI();
	_updateChoiceLists();
	_updateNavigation();
	_updateScriptLineAdding();
	_updateScriptVariableAdding();
	_updateMiscellaneous();
}

void ScriptEditor::_updateGUI()
{
	if (_isLoaded)
	{
		// Main screen
		auto mainScreen = _leftWindow->getScreen("scriptEditorMenuMain");
		
		// Check if LMB is pressed
		if (!_gui->getGlobalScreen()->isFocused())
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (mainScreen->getButton("variables")->isHovered())
				{
					_clearChoiceLists();
					_allowedToAddScriptLine = false;
					_isCreatingScriptLine = false;
					_isUpdatingScriptLine = false;
					_isAddingScriptLine = false;
					_leftWindow->setActiveScreen("scriptEditorMenuVariables");
				}
				else if (mainScreen->getButton("addLine")->isHovered())
				{
					_isAddingScriptLine = true;
				}
				else if (mainScreen->getButton("updateLine")->isHovered())
				{
					_isUpdatingScriptLine = true;
				}
				else if (mainScreen->getButton("deleteLine")->isHovered())
				{
					// Remove line from script
					_clearChoiceLists();
					_script->removeLine(_currentScriptLineID);
					_calibrateScriptLines();
					_currentScriptLineID = "";
				}
				else if (mainScreen->getButton("createLine")->isHovered())
				{
					// Add default choicelist
					_clearChoiceLists();
					_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_TYPE);
					_isCreatingScriptLine = true;
					_allowedToAddScriptLine = false;
					_currentScriptLineID = "";
				}
				else if (mainScreen->getButton("viewLine")->isHovered())
				{
					_gui->getGlobalScreen()->addChoiceForm("scriptLinesList", "View script", vec2(0.0f, 0.0f), _script->getAllScriptLineIDs());
				}
				else if (mainScreen->getButton("back")->isHovered())
				{
					_gui->getGlobalScreen()->addAnswerForm("exitScriptEditor", "Save changes?", vec2(0.0f, 0.25f));
				}
			}
		}

		// Check if user wants to save changes
		if (_gui->getGlobalScreen()->isAnswerFormConfirmed("exitScriptEditor"))
		{
			save();
			unload();
			_leftWindow->setActiveScreen("main");
		}
		else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitScriptEditor"))
		{
			unload();
			_leftWindow->setActiveScreen("main");
		}

		// Variables screen
		auto variableScreen = _leftWindow->getScreen("scriptEditorMenuVariables");

		// Check if LMB is pressed
		if (!_gui->getGlobalScreen()->isFocused())
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (variableScreen->getButton("addVariable")->isHovered())
				{
					_isAddingScriptVariable = true;
				}
				else if (variableScreen->getButton("updateVariable")->isHovered())
				{
					_isUpdatingScriptVariable = true;
				}
				else if (variableScreen->getButton("deleteVariable")->isHovered())
				{
					// Remove variable from script
					_clearChoiceLists();
					_script->removeVariable(_currentScriptVariableID);
					_currentScriptVariableID = "";
				}
				else if (variableScreen->getButton("createVariable")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("variableName", "New variable name", "", vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (variableScreen->getButton("viewVariable")->isHovered())
				{
					_gui->getGlobalScreen()->addChoiceForm("scriptVariablesList", "View variable", vec2(0.0f, 0.0f), _script->getAllScriptVariableIDs());
				}
				else if (variableScreen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("scriptEditorMenuMain");
				}
			}
		}
	}
}

void ScriptEditor::_updateChoiceLists()
{
	if (((_isCreatingScriptLine && !_allowedToAddScriptLine) || (_isCreatingScriptVariable && !_isAllowedToAddScriptVariable))
		&& !_gui->getGlobalScreen()->isFocused() && _isLoaded)
	{
		// Update hoverability & color & scrolling
		for (auto& list : _choiceListStack)
		{
			// General values
			int listIndex = static_cast<int>(list.type);
			bool isResponsive = (listIndex == static_cast<int>(_choiceListStack.back().type));
			int scrollingSpeed = _fe3d.input_getMouseWheelY();

			// Option scrolling
			if (isResponsive)
			{
				// Scrolling values
				string baseID = to_string(listIndex) + "_option_";
				vec3 firstPosition = _fe3d.billboardEntity_getPosition(baseID + "0"); // Position of top option
				vec3 lastPosition = _fe3d.billboardEntity_getPosition(baseID + to_string(list.total - 1)); // Position of bottom option

				// Calculate distance between 2 options
				float optionOffsetY;
				if (_fe3d.billboardEntity_isExisting(baseID + "1"))
				{
					optionOffsetY = _fe3d.billboardEntity_getPosition(baseID + "0").y - _fe3d.billboardEntity_getPosition(baseID + "1").y;
				}
				else
				{
					optionOffsetY = 0.0f;
				}

				// Calculate scrolling list bounds
				float maxY = _fe3d.gameEntity_getPosition(to_string(listIndex) + "_header").y - optionOffsetY;
				float minY = _fe3d.gameEntity_getPosition("background").y - (_fe3d.gameEntity_getSize("background").y / 15.0f);
				float halfHeight = (_optionBillboardHeight / 2.0f);
				static bool hasCollided = false;

				// Check if list is long enough to be scrollable
				if ((firstPosition.y - lastPosition.y) > (maxY - minY))
				{
					// Update scrolling movement
					_scrollingAcceleration += -(static_cast<float>(scrollingSpeed) * 0.05f);
					if (hasCollided)
					{
						_scrollingAcceleration = 0.0f;
						hasCollided = false;
					}

					// Movement constraints
					if ((firstPosition.y + halfHeight) < maxY) // Top movement constraint
					{
						_scrollingAcceleration = maxY - (firstPosition.y + halfHeight);
						hasCollided = true;
					}
					else if ((lastPosition.y - halfHeight) > minY) // Bottom movement constraint
					{
						_scrollingAcceleration = -((lastPosition.y - halfHeight) - minY);
						hasCollided = true;
					}

					// Limit acceleration
					_scrollingAcceleration = std::clamp(_scrollingAcceleration, -_maxScrollingAcceleration, _maxScrollingAcceleration);
				}
			}

			// Update every AABB
			for (int i = 0; i < list.total; i++)
			{
				// Determine entity ID
				string ID = to_string(listIndex) + "_option_" + to_string(i);

				// AABB responsiveness
				_fe3d.aabbEntity_setResponsiveness(ID, isResponsive);

				// Update current choice list
				if (isResponsive)
				{
					// Reset hover color
					_fe3d.billboardEntity_setColor(ID, vec3(1.0f));

					// Applying scrolling
					_fe3d.billboardEntity_move(ID, vec3(0.0f, _scrollingAcceleration, 0.0f));
				}
			}
		}
	}
}

void ScriptEditor::_updateNavigation()
{
	if (_isLoaded && (_isCreatingScriptLine || _isCreatingScriptVariable) && !_gui->getGlobalScreen()->isFocused())
	{
		// Hovering over options
		string hoveredEntityID = _fe3d.collision_checkCursorInAny();
		if (hoveredEntityID != "" && !_allowedToAddScriptLine && !_isAllowedToAddScriptVariable)
		{
			_fe3d.billboardEntity_setColor(hoveredEntityID, vec3(0.0f, 1.0f, 0.0f));
			_fe3d.lightEntity_setPosition("@@selectionLight", _fe3d.billboardEntity_getPosition(hoveredEntityID) + vec3(0.0f, 0.0f, 1.0f));
			_fe3d.lightEntity_show("@@selectionLight");
		}
		else
		{
			_fe3d.lightEntity_hide("@@selectionLight");
		}

		// Clicking a hovered option
		if (!_allowedToAddScriptLine && !_isAllowedToAddScriptVariable)
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (hoveredEntityID != "")
				{
					auto listType = _choiceListStack.back().type;
					
					// Add point light
					_fe3d.lightEntity_add(to_string(++_pointLightCounter), _fe3d.billboardEntity_getPosition(hoveredEntityID) + vec3(0.0f, 0.0f, 1.0f),
						vec3(0.0f, 1.0f, 0.0f), 2.5f, 10.0f);

					// Calculate character index of underscore before option-index
					int underscoreIndex = 0;
					for (size_t i = 0; i < hoveredEntityID.size(); i++)
					{
						if (hoveredEntityID[i] == '_')
						{
							underscoreIndex = i;
						}
					}

					// Needed values
					int optionIndex = stoi(hoveredEntityID.substr(underscoreIndex + 1, hoveredEntityID.size() - (underscoreIndex + 1)));
					_choiceListStack.back().selectedOptionIndex = optionIndex;
					string optionName = _choiceListStack.back().optionNames[optionIndex];

					// Determine type of choicelist
					switch (listType)
					{
						// Event types
						case ChoiceListType::EVENT_TYPE:
						{
							// Determine event type
							if (optionName == "INIT_EVENT")
							{
								// Event chosen, go to action choosing
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_TYPE);
							}
							else if (optionName == "INPUT_EVENT")
							{
								_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_TYPE);
							}
							else if (optionName == "COLLISION_EVENT")
							{

							}
							else if (optionName == "TIME_EVENT")
							{

							}
							else if (optionName == "CONDITION_EVENT")
							{

							}
							break;
						}

						// Input event
						case ChoiceListType::EVENT_INPUT_TYPE:
						{
							// Determine input type
							if (optionName == "KEYBOARD")
							{
								// Display all keyboard keys
								_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_KEY_NAME);
							}
							else if (optionName == "MOUSE")
							{
								// Display all mouse types
								_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_MOUSE_TYPE);
							}
							break;
						}
						case ChoiceListType::EVENT_INPUT_MOUSE_TYPE:
						{
							// Determine input type
							if (optionName == "BUTTON")
							{
								_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_MOUSE_BUTTON);
							}
							else if (optionName == "SCROLL_UP" || optionName == "SCROLL_DOWN")
							{
								// Event chosen, go to action choosing
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_TYPE);
							}
							break;
						}
						case ChoiceListType::EVENT_INPUT_KEY_NAME:
						case ChoiceListType::EVENT_INPUT_MOUSE_BUTTON:
						{
							// Display input methods
							_addChoiceList(ChoiceListSort::EVENT, ChoiceListType::EVENT_INPUT_METHOD);
							break;
						}
						case ChoiceListType::EVENT_INPUT_METHOD:
						{
							// Event chosen, go to action choosing
							_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_TYPE);
							break;
						}

						// Action types
						case ChoiceListType::ACTION_TYPE:
						{
							// Determine action type
							if (optionName == "CAMERA_ACTION")
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_TYPE);
							}
							break;
						}

						// Camera action
						case ChoiceListType::ACTION_CAMERA_TYPE:
						{
							// Determine camera type
							if (optionName == "POSITION")
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_DIRECTION);
							}
							else if (optionName == "FOLLOW")
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_FOLLOW);
							}
							else if (optionName == "YAW" || optionName == "PITCH")
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_METHOD);
							}
							else if (optionName == "LOOK_AT" || optionName == "FIRST_PERSON")
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_TOGGLE);
							}
							break;
						}
						case ChoiceListType::ACTION_CAMERA_DIRECTION:
						{
							if (optionName == "XYZ")
							{
								_allowedToAddScriptLine = true;
							}
							else
							{
								_addChoiceList(ChoiceListSort::ACTION, ChoiceListType::ACTION_CAMERA_METHOD);
							}
							break;
						}
						case ChoiceListType::ACTION_CAMERA_FOLLOW:
						case ChoiceListType::ACTION_CAMERA_METHOD:
						case ChoiceListType::ACTION_CAMERA_TOGGLE:
						{
							_allowedToAddScriptLine = true;
							break;
						}

						// Variable
						case ChoiceListType::VARIABLE_CONSTANT:
						{
							_addChoiceList(ChoiceListSort::VARIABLE, ChoiceListType::VARIABLE_TYPE);
							break;
						}
						case ChoiceListType::VARIABLE_TYPE:
						{
							_isAllowedToAddScriptVariable = true;
							break;
						}
					}
				}
			}
		}

		// Remove last chosen option
		if (_isCreatingScriptLine || _isCreatingScriptVariable)
		{
			if (_fe3d.input_getKeyPressed(Input::KEY_BACKSPACE))
			{
				// Cannot remove default choice list
				if (_choiceListStack.size() > 1)
				{
					_removeChoiceList();
					_fe3d.lightEntity_delete(to_string(_pointLightCounter));
					_pointLightCounter--;

					// Script line cannot be added if last option is removed
					if (_allowedToAddScriptLine)
					{
						_allowedToAddScriptLine = false;
					}

					// Script variable cannot be added if last option is removed
					if (_isAllowedToAddScriptVariable)
					{
						_isAllowedToAddScriptVariable = false;
					}
				}
			}
		}
	}
}