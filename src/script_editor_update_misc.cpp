#include "script_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <algorithm>

using std::clamp;

void ScriptEditor::_updateMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "scriptEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("search")->isHovered())
		{
			_gui->getOverlay()->openValueForm("searchScripts", "Search Scripts", "", VALUE_FORM_POSITION, SEARCH_VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("replace")->isHovered())
		{
			_gui->getOverlay()->openValueForm("replaceScripts", "Replace Scripts", "", VALUE_FORM_POSITION, REPLACE_VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createScript", "Create Script", "", VALUE_FORM_POSITION, CREATE_VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_gui->getOverlay()->openChoiceForm("editScript", "Edit Script", CENTER_CHOICE_FORM_POSITION, _script->getScriptFileIds());
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rename")->isHovered())
		{
			_gui->getOverlay()->openValueForm("renameScript", "Rename Script", _currentScriptFileId, VALUE_FORM_POSITION, RENAME_VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_gui->getOverlay()->openAnswerForm("deleteScript", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
		}

		if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_CONTROL))
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F) && !_gui->getOverlay()->isFocused())
			{
				_gui->getOverlay()->openValueForm("searchScripts", "Search Scripts", "", VALUE_FORM_POSITION, SEARCH_VALUE_FORM_SIZE, true, true, true);
			}

			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_H) && !_gui->getOverlay()->isFocused())
			{
				_gui->getOverlay()->openValueForm("replaceScripts", "Replace Scripts", "", VALUE_FORM_POSITION, REPLACE_VALUE_FORM_SIZE, true, true, true);
			}
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveScriptFiles();

				unload();

				return;
			}
			else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}

		screen->getButton("replace")->setHoverable(!_searchKeyword.empty(), true);
		screen->getButton("rename")->setHoverable(!_currentScriptFileId.empty(), true);
		screen->getButton("delete")->setHoverable(!_currentScriptFileId.empty(), true);

		screen->getTextField("totalLines")->setTextContent("Total Lines: " + to_string(_script->getTotalLineCount()));
	}
}

void ScriptEditor::_updateScriptFileCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createScript") && _gui->getOverlay()->isValueFormConfirmed())
	{
		const auto scriptFileId = _gui->getOverlay()->getValueFormContent();

		if(scriptFileId.empty())
		{
			Logger::throwWarning("Script file ID cannot be empty");

			return;
		}

		if(any_of(scriptFileId.begin(), scriptFileId.end(), isspace))
		{
			Logger::throwWarning("Script file ID cannot contain any spaces");

			return;
		}

		if(any_of(scriptFileId.begin(), scriptFileId.end(), isupper))
		{
			Logger::throwWarning("Script file ID cannot contain any capitals");

			return;
		}

		if(scriptFileId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
		{
			Logger::throwWarning("Script file ID cannot contain any specials");

			return;
		}

		const auto existingScriptFileIds = _script->getScriptFileIds();

		if(find(existingScriptFileIds.begin(), existingScriptFileIds.end(), scriptFileId) != existingScriptFileIds.end())
		{
			Logger::throwWarning("Script already exists");

			return;
		}

		_script->createScriptFile(scriptFileId);
		_script->getScriptFile(scriptFileId)->createLine(0, "");

		_currentScriptFileId = scriptFileId;
		_isWritingScript = true;

		_deleteDisplayContent();
		_createDisplayContent();

		_fe3d->text3d_setVisible(CARET_ID, true);
	}
}

void ScriptEditor::_updateScriptFileChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editScript") && _gui->getOverlay()->isChoiceFormConfirmed())
	{
		_currentScriptFileId = _gui->getOverlay()->getChoiceFormOptionId();
		_isWritingScript = true;

		_deleteDisplayContent();
		_createDisplayContent();

		_fe3d->text3d_setVisible(CARET_ID, true);
		_fe3d->camera_setPosition(fvec3(0.0f, 0.0f, CAMERA_DISTANCE));
	}
}

void ScriptEditor::_updateScriptFileRenaming()
{
	if((_gui->getOverlay()->getValueFormId() == "renameScript") && _gui->getOverlay()->isValueFormConfirmed())
	{
		const auto scriptFileId = _gui->getOverlay()->getValueFormContent();

		if(scriptFileId.empty())
		{
			Logger::throwWarning("Script file ID cannot be empty");

			return;
		}

		if(any_of(scriptFileId.begin(), scriptFileId.end(), isspace))
		{
			Logger::throwWarning("Script file ID cannot contain any spaces");

			return;
		}

		if(any_of(scriptFileId.begin(), scriptFileId.end(), isupper))
		{
			Logger::throwWarning("Script file ID cannot contain any capitals");

			return;
		}

		if(scriptFileId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
		{
			Logger::throwWarning("Script file ID cannot contain any specials");

			return;
		}

		const auto existingScriptFileIds = _script->getScriptFileIds();

		if(find(existingScriptFileIds.begin(), existingScriptFileIds.end(), scriptFileId) != existingScriptFileIds.end())
		{
			Logger::throwWarning("Script already exists");
		}

		_script->renameScriptFile(_currentScriptFileId, scriptFileId);

		_currentScriptFileId = scriptFileId;
	}
}

void ScriptEditor::_updateScriptSearching()
{
	if((_gui->getOverlay()->getValueFormId() == "searchScripts") && _gui->getOverlay()->isValueFormConfirmed())
	{
		_searchKeyword = _gui->getOverlay()->getValueFormContent();

		const auto searchResult = _script->getSearchResult(_searchKeyword);

		bool isFound = false;

		for(const auto & [scriptId, lineNumbers] : searchResult)
		{
			if(!lineNumbers.empty())
			{
				isFound = true;

				break;
			}
		}

		if(isFound)
		{
			Logger::throwInfo("Search results:");

			for(const auto & [scriptId, lineNumbers] : searchResult)
			{
				for(const auto & lineNumber : lineNumbers)
				{
					Logger::throwInfo("Script \"" + scriptId + "\" @ line " + to_string(lineNumber));
				}
			}
		}
		else
		{
			Logger::throwWarning("Search result: not found in scripts");
		}
	}
}

void ScriptEditor::_updateScriptReplacing()
{
	if((_gui->getOverlay()->getValueFormId() == "replaceScripts") && _gui->getOverlay()->isValueFormConfirmed())
	{
		_script->replaceKeyword(_searchKeyword, _gui->getOverlay()->getValueFormContent());

		_hasTextChanged = true;
	}
}

void ScriptEditor::_updateDisplay()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused())
	{
		return;
	}

	if(_hasTextChanged)
	{
		_deleteDisplayContent();
		_createDisplayContent();

		_hasTextChanged = false;
	}
}

void ScriptEditor::_updateCamera()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused() || !Tools::isCursorInsideDisplay())
	{
		return;
	}

	const auto isControlDown = _fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_CONTROL);
	const auto scrollSpeed = (_fe3d->input_isMouseScrolled(MouseWheelType::WHEEL_UP) ? VERTICAL_LINE_OFFSET : _fe3d->input_isMouseScrolled(MouseWheelType::WHEEL_DOWN) ? -VERTICAL_LINE_OFFSET : 0.0f);
	const auto lineCount = _script->getScriptFile(_currentScriptFileId)->getLineCount();
	const auto lastLineHeight = _fe3d->text3d_getPosition("number_" + to_string(lineCount - 1)).y;
	const auto minCameraOffset = fvec2(0.0f, min(0.0f, (lastLineHeight + ROOT_TEXT_POSITION.y)));
	const auto maxCameraOffset = fvec2(FLT_MAX, 0.0f);

	auto cameraPosition = _fe3d->camera_getPosition();

	if(isControlDown)
	{
		cameraPosition.x += scrollSpeed;
	}
	else
	{
		cameraPosition.y += scrollSpeed;
	}

	cameraPosition.x = clamp(cameraPosition.x, minCameraOffset.x, maxCameraOffset.x);
	cameraPosition.y = clamp(cameraPosition.y, minCameraOffset.y, maxCameraOffset.y);

	_fe3d->camera_setPosition(cameraPosition);

	for(int lineIndex = 0; lineIndex < lineCount; lineIndex++)
	{
		const auto lineTextId = ("text_" + to_string(lineIndex));
		const auto lineTextString = _script->getScriptFile(_currentScriptFileId)->getLine(lineIndex);
		const auto lineTextPosition = _fe3d->text3d_getPosition(lineTextId);
		const auto isVisible = ((lineTextPosition.y <= (cameraPosition.y + ROOT_TEXT_POSITION.y + VERTICAL_LINE_OFFSET)) &&
								(lineTextPosition.y >= (cameraPosition.y - ROOT_TEXT_POSITION.y - VERTICAL_LINE_OFFSET)));

		_fe3d->text3d_setVisible(lineTextId, isVisible);
		_fe3d->aabb_setRaycastResponsive(to_string(lineIndex), isVisible);

		for(int charIndex = 0; charIndex < static_cast<int>(lineTextString.size()); charIndex++)
		{
			_fe3d->aabb_setRaycastResponsive((to_string(lineIndex) + "_" + to_string(charIndex)), isVisible);
		}
	}
}

void ScriptEditor::_updateCursor()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused())
	{
		_fe3d->text3d_setVisible(CARET_ID, false);

		return;
	}

	if(Tools::isCursorInsideDisplay())
	{
		_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), CURSOR_TEXTURE_PATH);
	}

	if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / CARET_UPDATE_DIVIDER)) == 0)
	{
		if(_fe3d->text3d_getContent(CARET_ID) == "|")
		{
			_fe3d->text3d_setContent(CARET_ID, " ");
		}
		else
		{
			_fe3d->text3d_setContent(CARET_ID, "|");
		}
	}

	const auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
	const auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();

	if(cursorCharacterIndex == 0)
	{
		const auto linePosition = _fe3d->aabb_getBasePosition(to_string(_script->getScriptFile(_currentScriptFileId)->getCursorLineIndex()));
		const auto cursorPosition = fvec3((ROOT_TEXT_POSITION.x + HORIZONTAL_LINE_OFFSET - (CHAR_SIZE.x * 0.5f)), linePosition.y, linePosition.z);

		_fe3d->text3d_setPosition(CARET_ID, cursorPosition);
	}
	else
	{
		const auto characterPosition = _fe3d->aabb_getBasePosition(to_string(cursorLineIndex) + "_" + to_string(cursorCharacterIndex - 1));
		const auto cursorPosition = fvec3((characterPosition.x + (CHAR_SIZE.x * 0.5f)), characterPosition.y, characterPosition.z);

		_fe3d->text3d_setPosition(CARET_ID, cursorPosition);
	}
}

void ScriptEditor::_updateScriptDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteScript") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_script->deleteScriptFile(_currentScriptFileId);

			_clearDisplay();
		}
	}
}