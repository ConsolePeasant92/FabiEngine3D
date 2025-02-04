#include "world_editor.hpp"

void WorldEditor::_updateWaterMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuWater")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuWaterPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->water_delete(_fe3d->water_getSelectedId());
		}
		else if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_LEFT) && screen->getButton("up")->isHovered())
		{
			_fe3d->water_setHeight(_fe3d->water_getSelectedId(), (_fe3d->water_getHeight(_fe3d->water_getSelectedId()) + (_editorSpeed / WATER_HEIGHT_SPEED_DIVIDER)));
		}
		else if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_LEFT) && screen->getButton("down")->isHovered())
		{
			_fe3d->water_setHeight(_fe3d->water_getSelectedId(), (_fe3d->water_getHeight(_fe3d->water_getSelectedId()) - (_editorSpeed / WATER_HEIGHT_SPEED_DIVIDER)));
		}

		screen->getButton("place")->setHoverable(_fe3d->water_getSelectedId().empty(), true);
		screen->getButton("up")->setHoverable(!_fe3d->water_getSelectedId().empty(), true);
		screen->getButton("down")->setHoverable(!_fe3d->water_getSelectedId().empty(), true);
		screen->getButton("delete")->setHoverable(!_fe3d->water_getSelectedId().empty(), true);
	}
}

void WorldEditor::_updateWaterPlacingMenu()
{
	auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuWaterPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuWater");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("editorWaters")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_duplicator->copyEditorWater(hoveredOptionId.substr(1), hoveredOptionId);

				_fe3d->water_select(hoveredOptionId.substr(1));

				_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuWater");

				return;
			}
		}
	}
}