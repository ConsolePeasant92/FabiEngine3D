#include "gui_text_field.hpp"

GuiTextField::GuiTextField(shared_ptr<EngineInterface> fe3d, const string& parentID, const string& ID, fvec2 position, fvec2 size, string textContent, const fvec3& color, bool isCentered)
	:
	_fe3d(fe3d),
	_ID(ID),
	_entityID("@" + parentID + "_" + ID),
	_parentID(parentID),
	_initialPosition(position),
	_initialSize(size),
	_initialColor(color)
{
	_fe3d->text2d_create(_entityID, FONT_MAP_PATH, isCentered);
	_fe3d->text2d_setPosition(_entityID, position);
	_fe3d->text2d_setSize(_entityID, size);
	_fe3d->text2d_setColor(_entityID, color);
	_fe3d->text2d_setContent(_entityID, textContent);
}

GuiTextField::~GuiTextField()
{
	_fe3d->text2d_delete(_entityID);
}

void GuiTextField::setVisible(bool isVisible)
{
	_fe3d->text2d_setVisible(_entityID, isVisible);
}

void GuiTextField::changeTextContent(const string& content)
{
	if(content != _fe3d->text2d_getContent(_entityID))
	{
		auto charWidth = (_initialSize.x / static_cast<float>(_fe3d->text2d_getContent(_entityID).size()));
		auto charHeight = _initialSize.y;
		_fe3d->text2d_setContent(_entityID, content, charWidth, charHeight);
		updateInitialSize();
	}
}

void GuiTextField::updateInitialPosition()
{
	_initialPosition = _fe3d->text2d_getPosition(_entityID);
}

void GuiTextField::updateInitialSize()
{
	_initialSize = _fe3d->text2d_getSize(_entityID);
}

void GuiTextField::updateInitialColor()
{
	_initialColor = _fe3d->text2d_getColor(_entityID);
}

const fvec2 GuiTextField::getInitialPosition() const
{
	return _initialPosition;
}

const fvec2 GuiTextField::getInitialSize() const
{
	return _initialSize;
}

const fvec3& GuiTextField::getInitialColor() const
{
	return _initialColor;
}

const string& GuiTextField::getID() const
{
	return _ID;
}

const string& GuiTextField::getEntityID() const
{
	return _entityID;
}

const string& GuiTextField::getParentID() const
{
	return _parentID;
}