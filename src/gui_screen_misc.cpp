#include "gui_screen.hpp"
#include "logger.hpp"

GuiScreen::GuiScreen(shared_ptr<EngineInterface> fe3d, const string& parentId, const string& id, const fvec2& position, const fvec2& size)
	:
	_fe3d(fe3d),
	_id(id),
	_parentId(parentId),
	_parentPosition(position),
	_parentSize(size)
{

}

void GuiScreen::update(bool isHoverable)
{
	for(const auto& scrollingList : _scrollingLists)
	{
		scrollingList->update(isHoverable);
		scrollingList->setVisible(_isActive);
	}

	for(const auto& inputField : _inputFields)
	{
		inputField->update(isHoverable);
		inputField->setVisible(_isActive);
	}

	for(const auto& button : _buttons)
	{
		button->update(isHoverable);
		button->setVisible(_isActive);
	}

	for(const auto& rectangle : _rectangles)
	{
		rectangle->setVisible(_isActive);
	}

	for(const auto& textField : _textFields)
	{
		textField->setVisible(_isActive);
	}
}

void GuiScreen::show()
{
	_isActive = true;
}

void GuiScreen::hide()
{
	_isActive = false;
}

const string& GuiScreen::getId() const
{
	return _id;
}

const string& GuiScreen::getParentId() const
{
	return _parentId;
}

const fvec2 GuiScreen::convertPosition(const fvec2& position) const
{
	fvec2 screenPosition = _parentPosition;
	fvec2 screenSize = _parentSize;
	fvec2 buttonPosition = (screenPosition + (position * (screenSize * 0.5f)));

	return buttonPosition;
}

const fvec2 GuiScreen::convertSize(const fvec2& size) const
{
	fvec2 screenPosition = _parentPosition;
	fvec2 screenSize = _parentSize;
	fvec2 buttonSize = (size * 0.5f) * screenSize;

	return buttonSize;
}

const fvec4 GuiScreen::_convertDimensions(const fvec2& position, const fvec2& size) const
{
	fvec2 screenPosition = _parentPosition;
	fvec2 screenSize = _parentSize;
	fvec2 buttonPosition = (screenPosition + (position * (screenSize * 0.5f)));
	fvec2 buttonSize = (size * 0.5f) * screenSize;

	return fvec4(buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y);
}