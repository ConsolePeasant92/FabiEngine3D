#include "gui_overlay.hpp"

GuiOverlay::GuiOverlay(shared_ptr<EngineInterface> fe3d)
	:
	_fe3d(fe3d)
{

}

void GuiOverlay::update()
{
	for(const auto & [scrollingListId, scrollingList] : _scrollingLists)
	{
		scrollingList->update(true);
	}

	for(const auto & [inputBoxId, inputBox] : _inputBoxes)
	{
		inputBox->update(true);
	}

	for(const auto & [buttonId, button] : _buttons)
	{
		button->update(true);
	}

	_updateValueFormDeleting();
}

void GuiOverlay::setFocused(bool value)
{
	_isFocused = value;
}

const bool GuiOverlay::isFocused() const
{
	return _isFocused;
}