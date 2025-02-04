#include "world_editor.hpp"
#include "tools.hpp"

#include <algorithm>

void WorldEditor::_updateModelMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuModel")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(!_currentEditorModelId.empty())
			{
				_fe3d->model_setVisible(_currentEditorModelId, false);

				_currentEditorModelId = "";
			}

			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("place")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModelPlace");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("choice")->isHovered())
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModelChoice");
			_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("placedModels")->deleteOptions();

			for(auto & modelId : _loadedModelIds)
			{
				_gui->getRightViewport()->getWindow("main")->getScreen("worldEditorMenuModelChoice")->getScrollingList("placedModels")->createOption(modelId, modelId);
			}
		}

		screen->getButton("choice")->setHoverable(_currentEditorModelId.empty(), true);
	}
}

void WorldEditor::_updateModelPlacingMenu()
{
	auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuModelPlace")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModel");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			const auto hoveredOptionId = screen->getScrollingList("editorModels")->getHoveredOptionId();

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

				_currentEditorModelId = hoveredOptionId;

				_fe3d->model_setVisible(_currentEditorModelId, true);

				Tools::setCursorPosition(Tools::convertFromNdc(Tools::convertPositionRelativeToDisplay(fvec2(0.0f))));

				if(_fe3d->terrain_getSelectedId().empty())
				{
					_fe3d->model_setBasePosition(_currentEditorModelId, fvec3(0.0f));

					_gui->getOverlay()->openValueForm("positionX", "X", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
					_gui->getOverlay()->openValueForm("positionY", "Y", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
					_gui->getOverlay()->openValueForm("positionZ", "Z", 0.0f, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
				}
			}
		}
	}
}

void WorldEditor::_updateModelChoosingMenu()
{
	const auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuModelChoice")
	{
		for(const auto & optionId : screen->getScrollingList("placedModels")->getOptionIds())
		{
			if(!_fe3d->model_isExisting(optionId))
			{
				screen->getScrollingList("placedModels")->deleteOption(optionId);

				break;
			}
		}

		const auto hoveredOptionId = screen->getScrollingList("placedModels")->getHoveredOptionId();

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

				_activateModel(hoveredOptionId);
			}
			else
			{
				_selectModel(hoveredOptionId);

				_dontResetSelectedModel = true;
			}
		}

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuModel");

			return;
		}
	}
}