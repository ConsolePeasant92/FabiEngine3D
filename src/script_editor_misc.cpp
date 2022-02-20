#include "script_editor.hpp"

#include <sstream>

using std::istringstream;

void ScriptEditor::_reloadScriptTextDisplay(bool reloadAabbs)
{
	for(const auto& id : _fe3d->quad3d_getIds())
	{
		_fe3d->quad3d_delete(id);
	}
	for(const auto& id : _fe3d->text3d_getIds())
	{
		_fe3d->text3d_delete(id);
	}
	for(const auto& id : _fe3d->aabb_getIds())
	{
		_fe3d->aabb_delete(id);
	}

	const auto lineCount = static_cast<float>(_script->getScriptFile(_currentScriptFileId)->getLineCount());
	const auto separatorSize = fvec2((TEXT_CHARACTER_SIZE.x / 4.0f), (lineCount * VERTICAL_LINE_OFFSET));
	const auto separatorPosition = SCRIPT_TEXT_STARTING_POSITION + fvec3(HORIZONTAL_LINE_OFFSET * 0.5f, -(((lineCount - 1) * 0.5f) * VERTICAL_LINE_OFFSET), 0.0f);
	_fe3d->quad3d_create("separator", false);
	_fe3d->quad3d_setPosition("separator", (separatorPosition - fvec3(0.0f, separatorSize.y * 0.5f, 0.0f)));
	_fe3d->quad3d_setSize("separator", separatorSize);
	_fe3d->quad3d_setColor("separator", SEPARATOR_COLOR);
	_fe3d->quad3d_setBright("separator", true);

	for(unsigned int lineIndex = 0; lineIndex < lineCount; lineIndex++)
	{
		const auto lineNumberId = to_string(lineIndex);
		const auto lineTextId = "text_" + lineNumberId;
		const auto lineNumberString = to_string(lineIndex + 1);
		const auto lineTextString = _script->getScriptFile(_currentScriptFileId)->getLineText(lineIndex);
		const auto lineNumberSize = fvec2(lineNumberString.size() * TEXT_CHARACTER_SIZE.x, TEXT_CHARACTER_SIZE.y);
		const auto lineTextSize = fvec2(lineTextString.size() * TEXT_CHARACTER_SIZE.x, TEXT_CHARACTER_SIZE.y);
		const auto lineNumberPosition = SCRIPT_TEXT_STARTING_POSITION -
			fvec3((lineNumberString.size() - 1) * (TEXT_CHARACTER_SIZE.x * 0.5f), VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex), 0.0f);
		const auto lineTextPosition = SCRIPT_TEXT_STARTING_POSITION +
			fvec3((lineTextString.size() - 1) * (TEXT_CHARACTER_SIZE.x * 0.5f), -VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex), 0.0f) +
			fvec3(HORIZONTAL_LINE_OFFSET, 0.0f, 0.0f);

		_fe3d->text3d_create(lineNumberId, FONT_MAP_PATH, false);
		_fe3d->text3d_setMinTextureAlpha(lineNumberId, 0.05f);
		_fe3d->text3d_setContent(lineNumberId, lineNumberString);
		_fe3d->text3d_setPosition(lineNumberId, (lineNumberPosition - fvec3(0.0f, (lineNumberSize.y * 0.5f), 0.0f)));
		_fe3d->text3d_setSize(lineNumberId, lineNumberSize);
		_fe3d->text3d_setColor(lineNumberId, LINE_NUMBER_COLOR);
		_fe3d->text3d_setBright(lineNumberId, true);

		const auto lineAabbPosition = (lineNumberPosition - fvec3(0.0f, TEXT_CHARACTER_SIZE.y * 0.5f, AABB_DEPTH));
		const auto lineAabbSize = fvec3(TEXT_CHARACTER_SIZE.x * static_cast<float>(MAX_CHARACTERS_PER_LINE * 2) * 1.1f, TEXT_CHARACTER_SIZE.y, AABB_DEPTH);
		_fe3d->aabb_create(lineNumberId, false);
		_fe3d->aabb_setBasePosition(lineNumberId, lineAabbPosition);
		_fe3d->aabb_setBaseSize(lineNumberId, lineAabbSize);

		istringstream iss(lineTextString);
		string noWhiteSpace;
		iss >> noWhiteSpace;
		const auto isComment = (noWhiteSpace.substr(0, 3) == "///");
		_fe3d->text3d_create(lineTextId, FONT_MAP_PATH, false);
		_fe3d->text3d_setMinTextureAlpha(lineTextId, 0.05f);
		_fe3d->text3d_setContent(lineTextId, lineTextString);
		_fe3d->text3d_setPosition(lineTextId, (lineTextPosition - fvec3(0.0f, (lineTextSize.y * 0.5f), 0.0f)));
		_fe3d->text3d_setSize(lineTextId, lineTextSize);
		_fe3d->text3d_setColor(lineTextId, (isComment ? COMMENT_TEXT_COLOR : DEFAULT_TEXT_COLOR));
		_fe3d->text3d_setBright(lineTextId, true);

		for(unsigned int charIndex = 0; charIndex < lineTextString.size(); charIndex++)
		{
			const auto characterId = (lineNumberId + "_" + to_string(charIndex));
			const auto characterX = (HORIZONTAL_LINE_OFFSET + (HORIZONTAL_CHARACTER_OFFSET * static_cast<float>(charIndex)));
			const auto characterPosition = (SCRIPT_TEXT_STARTING_POSITION + fvec3(characterX, -VERTICAL_LINE_OFFSET * static_cast<float>(lineIndex), 0.0f));
			_fe3d->text3d_create(characterId, FONT_MAP_PATH, false);
			_fe3d->text3d_setPosition(characterId, (characterPosition - fvec3(0.0f, (TEXT_CHARACTER_SIZE.y * 0.5f), 0.0f)));
			_fe3d->text3d_setSize(characterId, TEXT_CHARACTER_SIZE);
			_fe3d->text3d_setVisible(characterId, false);

			if(reloadAabbs)
			{
				const auto characterAabbPosition = (characterPosition - fvec3(0.0f, TEXT_CHARACTER_SIZE.y * 0.5f, 0.0f));
				const auto characterAabbSize = fvec3(TEXT_CHARACTER_SIZE.x, TEXT_CHARACTER_SIZE.y, AABB_DEPTH);
				_fe3d->aabb_create(characterId, false);
				_fe3d->aabb_setBasePosition(characterId, characterAabbPosition);
				_fe3d->aabb_setBaseSize(characterId, characterAabbSize);
			}
		}
	}
}

void ScriptEditor::_copySelectedText()
{
	if(_firstSelectedLineIndex != -1)
	{
		_copyClipboard.clear();

		if(_lastSelectedLineIndex == -1)
		{
			_copyClipboard.push_back(_script->getScriptFile(_currentScriptFileId)->getLineText(_firstSelectedLineIndex));
		}
		else
		{
			for(int i = ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _lastSelectedLineIndex : _firstSelectedLineIndex);
				i <= ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _firstSelectedLineIndex : _lastSelectedLineIndex); i++)
			{
				_copyClipboard.push_back(_script->getScriptFile(_currentScriptFileId)->getLineText(i));
			}
		}
	}
}

void ScriptEditor::inject(shared_ptr<Script> script)
{
	_script = script;
}

const bool ScriptEditor::isWritingScript() const
{
	return !_currentScriptFileId.empty();
}