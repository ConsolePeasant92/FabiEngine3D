#include "animation2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Animation2dEditor::_updateMainMenu()
{
	auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation2dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("back", "Save Changes?", "Yes", "No", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createAnimation2d", "Create Animation2D", "", fvec2(0.0f, 0.1f), 10, true, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto animation2dIds = _loadedAnimation2dIds;

			for(auto & animation2dId : animation2dIds)
			{
				animation2dId = animation2dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editAnimation2d", "Edit Animation2D", fvec2(0.0f, 0.1f), animation2dIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto animation2dIds = _loadedAnimation2dIds;

			for(auto & animation2dId : animation2dIds)
			{
				animation2dId = animation2dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteAnimation2d", "Delete Animation2D", fvec2(0.0f, 0.1f), animation2dIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "back") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveAnimation2dsToFile();
				unload();

				return;
			}
			if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void Animation2dEditor::_updateChoiceMenu()
{
	auto screen = _gui->getRightViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "animation2dEditorMenuChoice")
	{
		const auto rowCount = _fe3d->animation2d_getRowCount(_currentAnimation2dId);
		const auto columnCount = _fe3d->animation2d_getColumnCount(_currentAnimation2dId);
		const auto interval = _fe3d->animation2d_getInterval(_currentAnimation2dId);
		const auto isStarted = _fe3d->quad3d_isAnimationStarted(PREVIEW_QUAD2D_ID, _currentAnimation2dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			if(_fe3d->quad3d_isAnimationStarted(PREVIEW_QUAD2D_ID, _currentAnimation2dId))
			{
				_fe3d->quad3d_stopAnimation(PREVIEW_QUAD2D_ID, _currentAnimation2dId);
			}

			_fe3d->quad3d_setDiffuseMap(PREVIEW_QUAD2D_ID, "");
			_fe3d->quad3d_setVisible(PREVIEW_QUAD2D_ID, false);

			_currentAnimation2dId = "";
			_isPreviewTextureChosen = false;
			_gui->getOverlay()->getTextField("animation2dId")->setVisible(false);
			_gui->getRightViewport()->getWindow("main")->setActiveScreen("animation2dEditorMenuMain");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("preview")->isHovered())
		{
			_gui->getOverlay()->openAnswerForm("preview", "Quad Type?", "Quad3D", "Quad2D", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rowCount")->isHovered())
		{
			_gui->getOverlay()->openValueForm("rowCount", "Row Count", to_string(rowCount), fvec2(0.0f, 0.1f), 2, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("columnCount")->isHovered())
		{
			_gui->getOverlay()->openValueForm("columnCount", "Column Count", to_string(columnCount), fvec2(0.0f, 0.1f), 2, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("interval")->isHovered())
		{
			_gui->getOverlay()->openValueForm("interval", "Interval", to_string(interval), fvec2(0.0f, 0.1f), 3, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("start")->isHovered())
		{
			_fe3d->quad3d_startAnimation(PREVIEW_QUAD2D_ID, _currentAnimation2dId, 1);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			_fe3d->quad3d_stopAnimation(PREVIEW_QUAD2D_ID, _currentAnimation2dId);
		}

		if((_gui->getOverlay()->getValueFormId() == "rowCount") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = max(0, Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation2d_setRowCount(_currentAnimation2dId, content);
		}
		if((_gui->getOverlay()->getValueFormId() == "columnCount") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = max(0, Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation2d_setColumnCount(_currentAnimation2dId, content);
		}
		if((_gui->getOverlay()->getValueFormId() == "interval") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = max(0, Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

			_fe3d->animation2d_setInterval(_currentAnimation2dId, content);
		}

		screen->getButton("preview")->setHoverable(!isStarted);
		screen->getButton("rowCount")->setHoverable(_isPreviewTextureChosen && !isStarted);
		screen->getButton("columnCount")->setHoverable(_isPreviewTextureChosen && !isStarted);
		screen->getButton("interval")->setHoverable(_isPreviewTextureChosen && !isStarted);
		screen->getButton("start")->setHoverable(_isPreviewTextureChosen && !isStarted);
		screen->getButton("stop")->setHoverable(_isPreviewTextureChosen && isStarted);
	}
}