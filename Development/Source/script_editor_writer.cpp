#include "script_editor.hpp"

void ScriptEditor::_updateTextWriter()
{
	static bool wasGuiFocused = false;
	
	// User must be editing script file & no active GUI overlays
	if (_isLoaded && _isWritingScript && !_gui->getGlobalScreen()->isFocused() && !wasGuiFocused)
	{
		// Handy values
		bool textHasChanged = false;
		unsigned int cursorLineIndex = _script.getScriptFile(_currentScriptFileID)->getCursorLineIndex();
		unsigned int cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getCursorCharIndex();

		// Timing functionality for continuous actions
		const vector<Input> actionKeys = 
		{ Input::KEY_ENTER, Input::KEY_BACKSPACE, Input::KEY_DELETE, Input::KEY_LEFT, Input::KEY_RIGHT, Input::KEY_UP, Input::KEY_DOWN };
		static Input activeActionKey = Input::NONE;
		static unsigned int passedFrames = 0;
		static bool singleActionAllowed = true;
		static bool continuousActionAllowed = false;

		// Timer for continuous actions
		if (activeActionKey == Input::NONE)
		{
			for (Input actionKey : actionKeys) // Check all possible action keys
			{
				if (_fe3d.input_getKeyDown(actionKey)) // Check if action key is down
				{
					// Remember currently pressed action key
					activeActionKey = actionKey;
					break;
				}
			}
		}
		else
		{
			// Check if waited long enough for continuous action
			if (passedFrames == _continuousTextActionFrameMinimum)
			{
				continuousActionAllowed = true;
				passedFrames = 0;
			}
			else // Keep waiting
			{
				passedFrames++;
			}
		}

		// Reset timing state if action key released
		if (!_fe3d.input_getKeyDown(activeActionKey))
		{
			activeActionKey = Input::NONE;
			passedFrames = 0;
			singleActionAllowed = true;
			continuousActionAllowed = false;
		}

		// Determine text action type
		if (_fe3d.input_getKeyDown(Input::KEY_ENTER)) // Add new line
		{
			// Check if single or fast new line action
			if (singleActionAllowed || continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
				{
					singleActionAllowed = false;

					// Extract remaining text in current line from cursor position
					string currentLineText = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex);
					string textToExtract = currentLineText;
					textToExtract = textToExtract.substr(cursorCharIndex, textToExtract.size() - cursorCharIndex);
					
					// Remove extracted text from current line
					_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText.substr(0, cursorCharIndex));

					// Set cursor to beginning of new line
					cursorCharIndex = 0;
					cursorLineIndex++;

					// Add text on new line
					_script.getScriptFile(_currentScriptFileID)->insertNewLine(cursorLineIndex, textToExtract);
					textHasChanged = true;
				}
			}
		}
		else if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
		{

		}
		else if (activeActionKey == Input::KEY_LEFT) // Left arrow key
		{
			// Check if single or fast cursor move
			if (singleActionAllowed || continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
				{
					singleActionAllowed = false;

					if (cursorCharIndex > 0) // If cursor somewhere on the line
					{
						cursorCharIndex--;
					}
					else // If cursor is at the beginning of the line
					{
						if (cursorLineIndex > 0) // Check if trying to move cursor out of screen
						{
							cursorLineIndex--;
							cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size();
						}
					}
				}
			}
		}
		else if (_fe3d.input_getKeyDown(Input::KEY_RIGHT)) // Right arrow key
		{
			// Check if single or fast cursor move
			if (singleActionAllowed || continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
				{
					singleActionAllowed = false;

					if (cursorCharIndex < _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size()) // If cursor somewhere on the line
					{
						cursorCharIndex++;
					}
					else // If cursor is at the end of the line
					{
						// Check if trying to move cursor out of screen
						if (cursorLineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1)
						{
							cursorLineIndex++;
							cursorCharIndex = 0;
						}
					}
				}
			}
		}
		else if (_fe3d.input_getKeyDown(Input::KEY_UP)) // Up arrow key
		{
			// Check if single or fast cursor move
			if (singleActionAllowed || continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
				{
					singleActionAllowed = false;

					if (cursorLineIndex > 0) // Check if trying to move cursor out of screen
					{
						cursorLineIndex--;

						// Change character index accordingly
						if (cursorCharIndex > _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size())
						{
							cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size();
						}
					}
				}
			}
		}
		else if (_fe3d.input_getKeyDown(Input::KEY_DOWN)) // Down arrow key
		{
			// Check if single or fast cursor move
			if (singleActionAllowed || continuousActionAllowed)
			{
				if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
				{
					singleActionAllowed = false;

					// Check if trying to move cursor out of screen
					if (cursorLineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1)
					{
						cursorLineIndex++;

						// Change character index accordingly
						if (cursorCharIndex > _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size())
						{
							cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size();
						}
					}
				}
			}
		}
		else // Other keypresses
		{
			// All characters of current line
			string currentLineText = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex);
			string newCharacters = "";

			// Letter characters
			for (auto& c : letterCharacters)
			{
				// Check if character is pressed on keyboard
				if (_fe3d.input_getKeyPressed(Input(c)))
				{
					// Spacebar
					if (c == ' ')
					{
						newCharacters += c;
					}
					else // Non-spacebar
					{
						if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT) || _fe3d.input_getKeyDown(Input::KEY_RSHIFT)) // Uppercase or special character
						{
							newCharacters += (c - 32);
						}
						else if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) // CAPSLOCK
						{
							newCharacters += (c - 32);
						}
						else // Lowercase character
						{
							newCharacters += c;
						}
					}
				}
			}

			// Number characters
			for (auto& element : numberCharacterMap)
			{
				// Check if character is pressed on keyboard
				if (_fe3d.input_getKeyPressed(Input(element.first)))
				{
					// Check if shift was pressed
					if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT) || _fe3d.input_getKeyDown(Input::KEY_RSHIFT))
					{
						newCharacters = element.second;
					}
					else
					{
						newCharacters = element.first;
					}
				}
			}

			// Special characters
			for (auto& element : specialCharacterMap)
			{
				// Check if character is pressed on keyboard
				if (_fe3d.input_getKeyPressed(Input(element.first)))
				{
					// Check if shift was pressed
					if (_fe3d.input_getKeyDown(Input::KEY_LSHIFT) || _fe3d.input_getKeyDown(Input::KEY_RSHIFT))
					{
						newCharacters += element.second;
					}
					else
					{
						newCharacters += element.first;
					}
				}
			}

			// Remove characters from line
			if (activeActionKey == Input::KEY_BACKSPACE || activeActionKey == Input::KEY_DELETE)
			{
				// Check if single or fast remove
				if (singleActionAllowed || continuousActionAllowed)
				{
					if (_fe3d.misc_checkInterval("textAction", _continuousTextActionInterval) || singleActionAllowed)
					{
						singleActionAllowed = false;

						// Jump to line above if cursor at beginning of line
						if (cursorCharIndex == 0 && _fe3d.input_getKeyDown(Input::KEY_BACKSPACE))
						{
							// Check if not trying to remove default line
							if (cursorLineIndex > 0)
							{
								// Remove line
								string textToMerge = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex);
								_script.getScriptFile(_currentScriptFileID)->removeLine(cursorLineIndex);
								cursorLineIndex--;

								// Set cursor to last character of line above & merge text from current line
								cursorCharIndex = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex).size();
								_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, 
									_script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex) + textToMerge);
								textHasChanged = true;
							}
						}
						else if (cursorCharIndex == currentLineText.size() && _fe3d.input_getKeyDown(Input::KEY_DELETE))
						{
							// Check if not trying to remove default line
							if (cursorLineIndex < _script.getScriptFile(_currentScriptFileID)->getLineCount() - 1)
							{
								// Remove line
								string textToMerge = _script.getScriptFile(_currentScriptFileID)->getLineText(cursorLineIndex + 1);
								_script.getScriptFile(_currentScriptFileID)->removeLine(cursorLineIndex + 1);

								// Merge text on current line & save merged line
								currentLineText += textToMerge;
								_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText);
								textHasChanged = true;
							}
						}
						else if (cursorCharIndex > 0 && _fe3d.input_getKeyDown(Input::KEY_BACKSPACE)) // Remove previous character from current line
						{
							cursorCharIndex--;
							currentLineText.erase(currentLineText.begin() + cursorCharIndex);
							textHasChanged = true;
							_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText); // Save new line text
						}
						else if (_fe3d.input_getKeyDown(Input::KEY_DELETE)) // Remove next character from current line
						{
							currentLineText.erase(currentLineText.begin() + cursorCharIndex);
							textHasChanged = true;
							_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText); // Save new line text
						}
					}
				}
			}
			
			// Add new typed character to line
			if (newCharacters != "")
			{
				if (currentLineText == "" || cursorCharIndex == currentLineText.size()) // First or last character in line
				{
					for (auto& character : newCharacters)
					{
						currentLineText += character;
						cursorCharIndex++;
					}
				}
				else // Inbetween character in line
				{
					for (auto& character : newCharacters)
					{
						currentLineText.insert(currentLineText.begin() + cursorCharIndex, character);
						cursorCharIndex++;
					}
				}

				textHasChanged = true;

				// Save new line
				_script.getScriptFile(_currentScriptFileID)->setLineText(cursorLineIndex, currentLineText);
			}
		}

		// Reload text display when altered
		if (textHasChanged)
		{
			_reloadScriptTextDisplay();
		}

		// Update blinking cursor
		static unsigned int passedBarFrames = _maxPassedBarFrames;
		static bool barEnabled = true;
		if (passedBarFrames >= _maxPassedBarFrames)
		{
			passedBarFrames = 0;

			// Toggle bar animation
			barEnabled = !barEnabled;
		}
		else
		{
			passedBarFrames++;
		}

		// If cursor billboard not existing, create new one
		if (!_fe3d.billboardEntity_isExisting("cursor"))
		{
			_fe3d.billBoardEntity_add("cursor", "", _fontPath, vec3(1.0f), vec3(0.0f), vec3(0.0f), _textCharacterSize, 0, 0);
		}

		// Update cursor billboard text & position
		vec3 position;
		if (cursorCharIndex == 0) // Default line position
		{
			position = _fe3d.billboardEntity_getPosition(to_string(cursorLineIndex)) + vec3(_horizontalLineOffset / 2.0f, 0.0f, 0.0f);
		}
		else // Mid-text position
		{
			position = _fe3d.billboardEntity_getPosition(to_string(cursorLineIndex) + "_" + to_string(cursorCharIndex - 1));
		}
		position += vec3(_textCharacterSize.x / 2.0f, 0.0f, 0.0f);
		_fe3d.billboardEntity_setPosition("cursor", position);
		_fe3d.billBoardEntity_setTextContent("cursor", (barEnabled ? "|" : " "));

		// Set new cursor indices
		_script.getScriptFile(_currentScriptFileID)->setCursorLineIndex(cursorLineIndex);
		_script.getScriptFile(_currentScriptFileID)->setCursorCharIndex(cursorCharIndex);
	}

	wasGuiFocused = _gui->getGlobalScreen()->isFocused();
}