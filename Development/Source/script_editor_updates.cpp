#include "script_editor.hpp"

#include <algorithm>

void ScriptEditor::update()
{
	_updateGUI();
	_updateTextWriter();
	_updateMiscellaneous();
}

void ScriptEditor::_updateGUI()
{
	if (_isLoaded)
	{
		// Main screen
		auto leftWindow = _gui->getViewport("left")->getWindow("main");
		auto mainScreen = leftWindow->getScreen("scriptEditorMenuMain");
		
		// Buttons hoverability
		mainScreen->getButton("deleteScript")->setHoverable(_currentScriptFileID != "");

		// Check if LMB is pressed
		if (!_gui->getGlobalScreen()->isFocused())
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (mainScreen->getButton("createScript")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("newScriptName", "New script name", "", vec2(0.0f), vec2(0.5f, 0.1f));
				}
				else if (mainScreen->getButton("editScript")->isHovered())
				{
					_gui->getGlobalScreen()->addChoiceForm("scriptFileList", "Choose script", vec2(0.0f), _script.getAllScriptFileIDs());
				}
				else if (mainScreen->getButton("deleteScript")->isHovered())
				{
					_fe3d.billboardEntity_deleteAll();
					_script.removeScriptFile(_currentScriptFileID);
					_isWritingScript = false;
					_currentScriptFileID = "";
				}
				else if (mainScreen->getButton("globals")->isHovered())
				{

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
			leftWindow->setActiveScreen("main");
		}
		else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitScriptEditor"))
		{
			unload();
			leftWindow->setActiveScreen("main");
		}
	}
}

void ScriptEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		if (_isWritingScript)
		{
			unsigned int cursorLineIndex = _script.getScriptFile(_currentScriptFileID)->getCursorLineIndex();

			if (!_gui->getGlobalScreen()->isFocused() && _fe3d.misc_isMouseInsideViewport())
			{
				// Camera movement input
				if (_fe3d.input_getMouseWheelY() == -1 && cursorLineIndex > 12)
				{
					_scrollingAcceleration -= _scrollingSpeed;
				}
				else if (_fe3d.input_getMouseWheelY() == 1)
				{
					_scrollingAcceleration += _scrollingSpeed;
				}
			}

			// Smooth camera movement
			_scrollingAcceleration = std::clamp(_scrollingAcceleration, -_maxScrollingAcceleration, _maxScrollingAcceleration);
			_scrollingAcceleration *= 0.95f;

			// Camera must not go out of screen
			if (_fe3d.camera_getPosition().y > _cameraStartingPosition.y)
			{
				_scrollingAcceleration = 0.0f;
				_fe3d.camera_setPosition(_cameraStartingPosition);
			}
			else if (_fe3d.camera_getPosition().y == _cameraStartingPosition.y && _scrollingAcceleration > 0.0f) // Trying to scroll up
			{
				_scrollingAcceleration = 0.0f;
			}
			else if (_fe3d.billboardEntity_isExisting(to_string(cursorLineIndex)) && cursorLineIndex > 12) // Trying to scroll down
			{
				float limitY = _fe3d.billboardEntity_getPosition(to_string(cursorLineIndex)).y + 6.5f;

				// Check if camera is not seeing the space under the last line of the script
				if (_fe3d.camera_getPosition().y < limitY)
				{
					_scrollingAcceleration = 0.0f;
					float newY = limitY;
					_fe3d.camera_setPosition(vec3(_cameraStartingPosition.x, newY, _cameraStartingPosition.z));
				}
				else if (_fe3d.camera_getPosition().y == limitY && _scrollingAcceleration < 0.0f) // Forbid scrolling down
				{
					_scrollingAcceleration = 0.0f;
				}
			}

			// Fixed camera position if lines are not out of screen
			if (cursorLineIndex < 12)
			{
				_fe3d.camera_setPosition(_cameraStartingPosition);
			}
		}

		// Move camera
		_fe3d.camera_translate(vec3(0.0f, _scrollingAcceleration, 0.0f));

		// Check if user filled in a new script name
		string newName;
		if (_gui->getGlobalScreen()->checkValueForm("newScriptName", newName))
		{
			auto existingNames = _script.getAllScriptFileIDs();
			if (find(existingNames.begin(), existingNames.end(), newName) == existingNames.end())
			{
				_isWritingScript = true;
				_currentScriptFileID = newName;
				_script.addScriptFile(_currentScriptFileID);
				_script.getScriptFile(_currentScriptFileID)->insertNewLine(0, "");
				_reloadScriptTextDisplay();
			}
			else
			{
				_fe3d.logger_throwWarning("Script name already exists!");
			}
		}

		// Check if existing script file chosen for viewing
		string selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("scriptFileList");
		if (selectedButtonID != "")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_gui->getGlobalScreen()->removeChoiceForm("scriptFileList");
				_currentScriptFileID = selectedButtonID;
				_isWritingScript = true;
				_reloadScriptTextDisplay();
			}
		}
		else if (_gui->getGlobalScreen()->isChoiceFormCancelled("scriptFileList"))
		{
			_gui->getGlobalScreen()->removeChoiceForm("scriptFileList");
		}
	}
}