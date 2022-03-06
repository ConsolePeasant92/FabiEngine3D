#include "script_editor.hpp"
#include <iostream>
#include <windows.h>

void ScriptEditor::_updateTextWriter()
{
	if(isLoaded() && _isWritingScript && !_gui->getOverlay()->isFocused() && !_wasGuiFocused)
	{
		if(_fe3d->misc_isCursorInsideDisplay())
		{
			_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_text.tga");
		}

		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _fe3d->misc_isCursorInsideDisplay())
		{
			_reloadScriptTextDisplay(true);
			_hasClickedLMB = true;
			return;
		}

		bool textHasChanged = false;
		unsigned int cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
		unsigned int cursorCharIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharIndex();
		string newCharacters = "";

		auto hoveredTextId = _fe3d->raycast_getClosestAabbId();
		int hoveredLineIndex = -1;
		int hoveredCharacterIndex = -1;
		if(!hoveredTextId.empty())
		{
			bool extractingLineNumber = true;
			string lineIndexString = "";
			string charIndexString = "";

			for(const auto& c : hoveredTextId)
			{
				if(extractingLineNumber)
				{
					lineIndexString += c;
				}
				else
				{
					charIndexString += c;
				}

				if(c == '_')
				{
					extractingLineNumber = false;
				}
			}

			hoveredLineIndex = stoi(lineIndexString);
			if(!charIndexString.empty())
			{
				hoveredCharacterIndex = stoi(charIndexString);
			}
		}

		if(_activeActionKey == InputType::NONE)
		{
			for(InputType actionKey : ACTION_KEYS)
			{
				if(_fe3d->input_isKeyPressed(actionKey))
				{
					_activeActionKey = actionKey;
					break;
				}
			}
		}
		else
		{
			if(_passedFrames == CONTINUOUS_TEXT_ACTION_FRAME_MINIMUM)
			{
				_isContinuousActionAllowed = true;
				_passedFrames = 0;
			}
			else
			{
				_passedFrames++;
			}
		}

		if(!_fe3d->input_isKeyDown(_activeActionKey))
		{
			_activeActionKey = InputType::NONE;
			_passedFrames = 0;
			_isSingleActionAllowed = true;
			_isContinuousActionAllowed = false;
		}

		if(_hasClickedLMB)
		{
			if(!hoveredTextId.empty())
			{
				cursorLineIndex = hoveredLineIndex;

				if(hoveredCharacterIndex == -1)
				{
					cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
				}
				else
				{
					cursorCharIndex = hoveredCharacterIndex;
				}
			}
		}
		else if(_activeActionKey == InputType::KEY_ENTER)
		{
			if(_firstSelectedLineIndex == -1)
			{
				if(_script->getScriptFile(_currentScriptFileId)->getLineCount() < MAX_LINE_COUNT)
				{
					if(_isSingleActionAllowed || _isContinuousActionAllowed)
					{
						if(((_fe3d->misc_getPassedUpdateCount() % CONTINUOUS_TEXT_ACTION_INTERVAL) == 0) || _isSingleActionAllowed)
						{
							_isSingleActionAllowed = false;

							string currentLineText = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex);
							string textToExtract = currentLineText;
							textToExtract = textToExtract.substr(cursorCharIndex, textToExtract.size() - cursorCharIndex);

							_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText.substr(0, cursorCharIndex));

							cursorCharIndex = 0;
							cursorLineIndex++;

							_script->getScriptFile(_currentScriptFileId)->insertNewLine(cursorLineIndex, textToExtract);
							textHasChanged = true;
						}
					}
				}
			}
		}
		else if(_activeActionKey == InputType::KEY_LEFT)
		{
			if(_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if(((_fe3d->misc_getPassedUpdateCount() % CONTINUOUS_TEXT_ACTION_INTERVAL) == 0) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					if(cursorCharIndex > 0)
					{
						cursorCharIndex--;
					}
					else
					{
						if(cursorLineIndex > 0)
						{
							cursorLineIndex--;
							cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
						}
					}
				}
			}
		}
		else if(_activeActionKey == InputType::KEY_RIGHT)
		{
			if(_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if(((_fe3d->misc_getPassedUpdateCount() % CONTINUOUS_TEXT_ACTION_INTERVAL) == 0) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					if(cursorCharIndex < _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size())
					{
						cursorCharIndex++;
					}
					else
					{
						if(cursorLineIndex < _script->getScriptFile(_currentScriptFileId)->getLineCount() - 1)
						{
							cursorLineIndex++;
							cursorCharIndex = 0;
						}
					}
				}
			}
		}
		else if(_activeActionKey == InputType::KEY_UP)
		{
			if(_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if(((_fe3d->misc_getPassedUpdateCount() % CONTINUOUS_TEXT_ACTION_INTERVAL) == 0) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					if(cursorLineIndex > 0)
					{
						cursorLineIndex--;

						if(cursorCharIndex > _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size())
						{
							cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
						}
					}
				}
			}
		}
		else if(_activeActionKey == InputType::KEY_DOWN)
		{
			if(_isSingleActionAllowed || _isContinuousActionAllowed)
			{
				if(((_fe3d->misc_getPassedUpdateCount() % CONTINUOUS_TEXT_ACTION_INTERVAL) == 0) || _isSingleActionAllowed)
				{
					_isSingleActionAllowed = false;

					if(cursorLineIndex < _script->getScriptFile(_currentScriptFileId)->getLineCount() - 1)
					{
						cursorLineIndex++;

						if(cursorCharIndex > _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size())
						{
							cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
						}
					}
				}
			}
		}
		else
		{
			string currentLineText = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex);

			if(!_fe3d->input_isKeyDown(InputType::KEY_LCTRL) && !_fe3d->input_isKeyDown(InputType::KEY_RCTRL))
			{
				for(const auto& c : ALPHABET_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(InputType(c)))
					{
						if(c == ' ')
						{
							newCharacters += c;
						}
						else
						{
							if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
							{
								newCharacters += (c - 32);
							}
							else if((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
							{
								newCharacters += (c - 32);
							}
							else
							{
								newCharacters += c;
							}
						}
					}
				}

				for(const auto& [normalCharacter, shiftCharacter] : NUMBER_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(InputType(normalCharacter)))
					{
						if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
						{
							newCharacters += shiftCharacter;
						}
						else
						{
							newCharacters += normalCharacter;
						}
					}
				}

				for(const auto& [normalCharacter, shiftCharacter] : SPECIAL_CHARACTERS)
				{
					if(_fe3d->input_isKeyPressed(InputType(normalCharacter)))
					{
						if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
						{
							newCharacters += shiftCharacter;
						}
						else
						{
							newCharacters += normalCharacter;
						}
					}
				}

				if(_fe3d->input_isKeyPressed(InputType::KEY_TAB))
				{
					newCharacters += "    ";
				}
			}

			if(_activeActionKey == InputType::KEY_BACKSPACE || _activeActionKey == InputType::KEY_DELETE)
			{
				if(_firstSelectedLineIndex == -1)
				{
					if(_isSingleActionAllowed || _isContinuousActionAllowed)
					{
						if(((_fe3d->misc_getPassedUpdateCount() % CONTINUOUS_TEXT_ACTION_INTERVAL) == 0) || _isSingleActionAllowed)
						{
							_isSingleActionAllowed = false;

							if(cursorCharIndex == 0 && _activeActionKey == InputType::KEY_BACKSPACE)
							{
								if(cursorLineIndex > 0)
								{
									string textToMerge = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex);
									_script->getScriptFile(_currentScriptFileId)->deleteLine(cursorLineIndex);
									cursorLineIndex--;

									cursorCharIndex = static_cast<unsigned int>(_script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex).size());
									_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex,
																							  _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex) + textToMerge);
									textHasChanged = true;
								}
							}
							else if(cursorCharIndex == currentLineText.size() && _activeActionKey == InputType::KEY_DELETE)
							{
								if(cursorLineIndex < _script->getScriptFile(_currentScriptFileId)->getLineCount() - 1)
								{
									string textToMerge = _script->getScriptFile(_currentScriptFileId)->getLineText(cursorLineIndex + 1);

									if((currentLineText.size() + textToMerge.size()) <= MAX_CHARACTERS_PER_LINE)
									{
										_script->getScriptFile(_currentScriptFileId)->deleteLine(cursorLineIndex + 1);

										currentLineText += textToMerge;
										_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText);
										textHasChanged = true;
									}
								}
							}
							else if(cursorCharIndex > 0 && _fe3d->input_isKeyDown(InputType::KEY_BACKSPACE))
							{
								cursorCharIndex--;
								currentLineText.erase(currentLineText.begin() + cursorCharIndex);
								textHasChanged = true;
								_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText);
							}
							else if(_fe3d->input_isKeyDown(InputType::KEY_DELETE))
							{
								currentLineText.erase(currentLineText.begin() + cursorCharIndex);
								textHasChanged = true;
								_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText);
							}
						}
					}
				}
			}

			if(static_cast<unsigned int>(currentLineText.size() + newCharacters.size()) <= MAX_CHARACTERS_PER_LINE)
			{
				if(_firstSelectedLineIndex == -1)
				{
					if(!newCharacters.empty())
					{
						if(currentLineText.empty() || cursorCharIndex == currentLineText.size())
						{
							for(const auto& character : newCharacters)
							{
								currentLineText += character;
								cursorCharIndex++;
							}
						}
						else
						{
							for(const auto& character : newCharacters)
							{
								currentLineText.insert(currentLineText.begin() + cursorCharIndex, character);
								cursorCharIndex++;
							}
						}

						textHasChanged = true;

						_script->getScriptFile(_currentScriptFileId)->setLineText(cursorLineIndex, currentLineText);
					}
				}
			}
		}

		_updateTextSelector(newCharacters, cursorLineIndex, cursorCharIndex, hoveredLineIndex, textHasChanged);

		if(textHasChanged || _hasClickedLMB)
		{
			_reloadScriptTextDisplay(false);
		}

		static unsigned int passedBarFrames = MAX_PASSED_BAR_FRAMES;
		static bool barEnabled = true;
		if(passedBarFrames >= MAX_PASSED_BAR_FRAMES)
		{
			passedBarFrames = 0;

			barEnabled = !barEnabled;
		}
		else
		{
			passedBarFrames++;
		}

		if(!_fe3d->text3d_isExisting("cursor"))
		{
			_fe3d->text3d_create("cursor", FONT_MAP_PATH, false);
			_fe3d->text3d_setSize("cursor", TEXT_CHARACTER_SIZE);
			_fe3d->text3d_setMinTextureAlpha("cursor", 0.15f);
		}

		fvec3 position;
		if(cursorCharIndex == 0)
		{
			fvec3 linePosition = _fe3d->aabb_getBasePosition(to_string(cursorLineIndex));
			position = fvec3(TEXT_STARTING_POSITION.x + HORIZONTAL_LINE_OFFSET - HORIZONTAL_CHARACTER_OFFSET, linePosition.y, linePosition.z);
		}
		else
		{
			position = _fe3d->aabb_getBasePosition(to_string(cursorLineIndex) + "_" + to_string(cursorCharIndex - 1));
		}
		position += fvec3(TEXT_CHARACTER_SIZE.x * 0.5f, 0.0f, 0.0f);
		_fe3d->text3d_setPosition("cursor", position);
		bool showBar = ((barEnabled && _firstSelectedLineIndex == -1) || _activeActionKey != InputType::NONE);
		_fe3d->text3d_setContent("cursor", (showBar ? "|" : " "));

		_script->getScriptFile(_currentScriptFileId)->setCursorLineIndex(cursorLineIndex);
		_script->getScriptFile(_currentScriptFileId)->setCursorCharIndex(cursorCharIndex);
	}

	_wasGuiFocused = _gui->getOverlay()->isFocused();
	_hasClickedLMB = false;
}