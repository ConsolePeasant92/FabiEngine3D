#include "world_editor.hpp"

void WorldEditor::_updateWaterMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "worldEditorMenuWater")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("choose")->isHovered())
		{
			vector<string> waterIds;
			for(const auto & id : _waterEditor->getLoadedEntityIds())
			{
				if(id[0] == '@')
				{
					waterIds.push_back(id.substr(1));
				}
			}

			_gui->getOverlay()->openChoiceForm("waterList", "Select Water", fvec2(0.0f, 0.1f), waterIds);
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_fe3d->water_delete(_fe3d->water_getSelectedId());
		}
		else if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("up")->isHovered())
		{
			_fe3d->water_setHeight(_fe3d->water_getSelectedId(), (_fe3d->water_getHeight(_fe3d->water_getSelectedId()) + (_editorSpeed / 100.0f)));
		}
		else if(_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("down")->isHovered())
		{
			_fe3d->water_setHeight(_fe3d->water_getSelectedId(), (_fe3d->water_getHeight(_fe3d->water_getSelectedId()) - (_editorSpeed / 100.0f)));
		}

		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();
			if(!selectedOptionId.empty())
			{
				_worldUtilities->copyTemplateWater(selectedOptionId, ("@" + selectedOptionId));

				_fe3d->water_select(selectedOptionId);

				_gui->getOverlay()->closeChoiceForm();
			}
			else if(_gui->getOverlay()->isChoiceFormCancelled())
			{
				_gui->getOverlay()->closeChoiceForm();
			}
		}

		screen->getButton("choose")->setHoverable(_fe3d->water_getSelectedId().empty());
		screen->getButton("up")->setHoverable(!_fe3d->water_getSelectedId().empty());
		screen->getButton("down")->setHoverable(!_fe3d->water_getSelectedId().empty());
		screen->getButton("delete")->setHoverable(!_fe3d->water_getSelectedId().empty());
	}
}