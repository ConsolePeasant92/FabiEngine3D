#include "world_editor.hpp"

void WorldEditor::_updateTerrainMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuTerrain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuTerrainPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->terrain_delete(_fe3d->terrain_getSelectedId());
		}

		screen->getButton("place")->setHoverable(_fe3d->terrain_getSelectedId().empty(), true);
		screen->getButton("delete")->setHoverable(!_fe3d->terrain_getSelectedId().empty(), true);
	}
}

void WorldEditor::_updateTerrainPlacingMenu()
{
	auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuTerrainPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuTerrain");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("editorTerrains")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_duplicator->copyEditorTerrain(hoveredOptionId.substr(1), hoveredOptionId);

				_fe3d->terrain_select(hoveredOptionId.substr(1));

				_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuTerrain");

				return;
			}
		}
	}
}