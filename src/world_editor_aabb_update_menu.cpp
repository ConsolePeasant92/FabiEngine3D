#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateAabbMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuAabb")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentEditorAabbId.empty())
			{
				_fe3d->aabb_setVisible(_currentEditorAabbId, false);
				_fe3d->aabb_setRaycastResponsive(_currentEditorAabbId, false);
				_fe3d->aabb_setCollisionResponsive(_currentEditorAabbId, false);

				_currentEditorAabbId = "";
			}

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuAabbPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuAabbChoice");
			_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuAabbChoice")->getScrollingList("placedAabbs")->deleteOptions();

			for(auto & aabbId : _loadedAabbIds)
			{
				_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuAabbChoice")->getScrollingList("placedAabbs")->createOption(aabbId, aabbId);
			}
		}

		screen->getButton("choice")->setHoverable(_currentEditorAabbId.empty(), true);
	}
}

void WorldEditor::_updateAabbPlacingMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuAabbPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuAabb");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("editorAabbs")->getHoveredOptionId();

			if(!hoveredOptionId.empty())
			{
				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("empty");

				_deactivateModel();
				_deactivateQuad3d();
				_deactivateText3d();
				_deactivateAabb();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateCaptor();
				_deactivateSound3d();

				_currentEditorAabbId = hoveredOptionId;

				_fe3d->aabb_setVisible(_currentEditorAabbId, true);
				_fe3d->aabb_setRaycastResponsive(_currentEditorAabbId, true);
				_fe3d->aabb_setCollisionResponsive(_currentEditorAabbId, true);

				Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->aabb_setBasePosition(_currentEditorAabbId, fvec3(0.0f));

					_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
					_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
					_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
				}
			}
		}
	}
}

void WorldEditor::_updateAabbChoosingMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuAabbChoice")
	{
		for(const auto & optionId : screen->getScrollingList("placedAabbs")->getOptionIds())
		{
			if(!_fe3d->aabb_isExisting(optionId))
			{
				screen->getScrollingList("placedAabbs")->deleteOption(optionId);

				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("placedAabbs")->getHoveredOptionId();

		if(!hoveredOptionId.empty())
		{
			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				_deactivateModel();
				_deactivateQuad3d();
				_deactivateText3d();
				_deactivateAabb();
				_deactivatePointlight();
				_deactivateSpotlight();
				_deactivateCaptor();
				_deactivateSound3d();

				_activateAabb(hoveredOptionId);
			}
			else
			{
				_selectAabb(hoveredOptionId);

				_dontResetSelectedAabb = true;
			}
		}

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuAabb");

			return;
		}
	}
}