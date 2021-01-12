#include "engine_gui_writefield.hpp"

#include <map>

EngineGuiWriteField::EngineGuiWriteField(
	FabiEngine3D& fe3d, const string& parentID, const string& ID, Vec2 position, Vec2 size, Vec3 color, Vec3 hoverColor,
	Vec3 textColor, Vec3 textHoverColor, bool noNumbers, bool noCaps, bool noSpecials, bool noLetters, bool minusAllowed) :
	EngineGuiButton(fe3d, parentID, ID, position, size, color, hoverColor, "|", textColor, textHoverColor, false, true),
	_noNumbers(noNumbers),
	_noCaps(noCaps),
	_noSpecials(noSpecials),
	_noLetters(noLetters),
	_minusAllowed(minusAllowed)
{

}

void EngineGuiWriteField::update(bool hoverable)
{
	_updateHovering(hoverable && !_isActive);
	_updateActivation();
	_updateTyping();
}

void EngineGuiWriteField::_updateActivation()
{
	if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
	{
		if (_isHovered)
		{
			_isActive = true;
		}
		else
		{
			if (!_mustBeActive)
			{
				_isActive = false;
			}
		}
	}
}

void EngineGuiWriteField::_updateTyping()
{
	if (_isActive)
	{
		static int passedBarFrames = _maxPassedBarFrames;
		static int passedBackspaceFrames = _maxPassedBackspaceFrames;
		static bool barEnabled = true;

		// Update bar animation time
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

		// Check if not writing out of border
		if ((float(_currentTextContent.size() + 1) * _charWidth) < _textfield->getOriginalSize().x)
		{
			// Letter characters
			string letterCharacters = " abcdefghijklmnopqrstuvwxyz";

			// Number characters
			std::map<char, char> numberCharacterMap;
			numberCharacterMap['0'] = ')';
			numberCharacterMap['1'] = '!';
			numberCharacterMap['2'] = '@';
			numberCharacterMap['3'] = '#';
			numberCharacterMap['4'] = '$';
			numberCharacterMap['5'] = '%';
			numberCharacterMap['6'] = '^';
			numberCharacterMap['7'] = '&';
			numberCharacterMap['8'] = '*';
			numberCharacterMap['9'] = '(';

			// Special characters
			std::map<char, char> specialCharacterMap;
			specialCharacterMap['.'] = '>';
			specialCharacterMap[','] = '<';
			specialCharacterMap['/'] = '?';
			specialCharacterMap[';'] = ':';
			specialCharacterMap['\''] = '\"';
			specialCharacterMap['['] = '{';
			specialCharacterMap[']'] = '}';
			specialCharacterMap['\\'] = '|';
			specialCharacterMap['-'] = '_';
			specialCharacterMap['='] = '+';

			// Letter characters
			if (!_noLetters)
			{
				for (auto& c : letterCharacters)
				{
					// Check if character is pressed on keyboard
					if (_fe3d.input_getKeyPressed(InputType(c)))
					{
						// Spacebar
						if (c == ' ')
						{
							_currentTextContent += c;
						}
						else // Non-spacebar
						{
							if (_fe3d.input_getKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_getKeyDown(InputType::KEY_RSHIFT)) // Uppercase or special character
							{
								// Convert to uppercase
								{
									_currentTextContent += (c - 32);
								}
							}
							else if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) // Uppercase character
							{
								if (!_noCaps) // A - Z
								{
									// Convert to uppercase
									_currentTextContent += (c - 32);
								}
							}
							else // Lowercase character
							{
								_currentTextContent += c;
							}
						}
					}
				}
			}

			// Number characters
			if (!_noNumbers)
			{
				for (auto& element : numberCharacterMap)
				{
					// Check if character is pressed on keyboard
					if (_fe3d.input_getKeyPressed(InputType(element.first)))
					{
						// Check if shift was pressed
						if (_fe3d.input_getKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_getKeyDown(InputType::KEY_RSHIFT))
						{
							_currentTextContent += element.second;
						}
						else
						{
							_currentTextContent += element.first;
						}
					}
				}
			}

			// Special characters
			if (!_noSpecials)
			{
				for (auto& element : specialCharacterMap)
				{
					// Check if character is pressed on keyboard
					if (_fe3d.input_getKeyPressed(InputType(element.first)))
					{
						// Check if shift was pressed
						if (_fe3d.input_getKeyDown(InputType::KEY_LSHIFT) || _fe3d.input_getKeyDown(InputType::KEY_RSHIFT))
						{
							_currentTextContent += element.second;
						}
						else
						{
							_currentTextContent += element.first;
						}
					}
				}
			}
			else if(_minusAllowed && !_noNumbers) // Minus character (for numbers)
			{
				if (_fe3d.input_getKeyPressed(InputType('-')))
				{
					if (!_fe3d.input_getKeyDown(InputType::KEY_LSHIFT) && !_fe3d.input_getKeyDown(InputType::KEY_RSHIFT))
					{
						if (_currentTextContent.empty()) // Minus can only before any number
						{
							_currentTextContent += '-';
						}
					}
				}
			}
		}

		// Remove character
		if (_fe3d.input_getKeyDown(InputType::KEY_BACKSPACE))
		{
			// Check if enough time passed
			if (passedBackspaceFrames >= _maxPassedBackspaceFrames)
			{
				passedBackspaceFrames = 0;

				if (_currentTextContent.size() == 1)
				{
					_currentTextContent = "";
				}
				else
				{
					_currentTextContent = _currentTextContent.substr(0, _currentTextContent.size() - 1); // Remove last character
				}
			}
			else
			{
				passedBackspaceFrames++;
			}
		}
		else
		{
			passedBackspaceFrames = _maxPassedBackspaceFrames;
		}

		// Update text content with or without bar
		_fe3d.textEntity_setTextContent(_textfield->getEntityID(), _currentTextContent + (barEnabled ? "|" : " "), _charWidth);

		// Input confirmation
		if (_fe3d.input_getKeyPressed(InputType::KEY_ENTER))
		{
			if (_currentTextContent != "")
			{
				_confirmedInput = true;
				_isActive = false;
			}
		}
	}
	else
	{
		// Update text content
		_fe3d.textEntity_setTextContent(_textfield->getEntityID(), _currentTextContent, _charWidth);
		_confirmedInput = false;
	}
}

void EngineGuiWriteField::setActive(bool active)
{
	_isActive = active;
}

void EngineGuiWriteField::setPermActive(bool active)
{
	_isActive = active;
	_mustBeActive = active;
}

bool EngineGuiWriteField::confirmedInput()
{
	return _confirmedInput;
}

bool EngineGuiWriteField::isActive()
{
	return _isActive;
}

bool EngineGuiWriteField::hasTextContentChanged()
{
	bool result = (_lastTextContent != _currentTextContent);
	_lastTextContent = _currentTextContent;
	return result;
}

string EngineGuiWriteField::getTextContent()
{
	// Check if user filled in a minus without a number
	if (_currentTextContent == "-" && _noSpecials && _minusAllowed)
	{
		return "";
	}
	else
	{
		return _currentTextContent;
	}
}

void EngineGuiWriteField::setTextContent(const string& content)
{
	_currentTextContent = content;
}