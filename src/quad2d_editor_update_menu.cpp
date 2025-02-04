#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad2dEditor::_updateMainMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad2dEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->openAnswerForm("save", "Save Changes?", "Yes", "No", ANSWER_FORM_POSITION);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->openValueForm("createQuad2d", "Create Quad2D", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto quad2dIds = _loadedQuad2dIds;

			for(auto & quad2dId : quad2dIds)
			{
				quad2dId = quad2dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("editQuad2d", "Edit Quad2D", LEFT_CHOICE_FORM_POSITION, quad2dIds);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto quad2dIds = _loadedQuad2dIds;

			for(auto & quad2dId : quad2dIds)
			{
				quad2dId = quad2dId.substr(1);
			}

			_gui->getOverlay()->openChoiceForm("deleteQuad2d", "Delete Quad2D", LEFT_CHOICE_FORM_POSITION, quad2dIds);
		}

		if((_gui->getOverlay()->getAnswerFormId() == "save") && _gui->getOverlay()->isAnswerFormConfirmed())
		{
			if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
			{
				saveQuad2dsToFile();

				unload();

				return;
			}
			else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
			{
				unload();

				return;
			}
		}
	}
}

void Quad2dEditor::_updateChoiceMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad2dEditorMenuChoice")
	{
		const auto color = _fe3d->quad2d_getColor(_currentQuad2dId);
		const auto opacity = _fe3d->quad2d_getOpacity(_currentQuad2dId);
		const auto lightness = _fe3d->quad2d_getLightness(_currentQuad2dId);
		const auto textureRepeat = _fe3d->quad2d_getTextureRepeat(_currentQuad2dId);
		const auto isHorizontallyFlipped = _fe3d->quad2d_isHorizontallyFlipped(_currentQuad2dId);
		const auto isVerticallyFlipped = _fe3d->quad2d_isVerticallyFlipped(_currentQuad2dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->quad2d_setVisible(_currentQuad2dId, false);

			_gui->getOverlay()->getTextField(QUAD2D_TITLE_ID)->setVisible(false);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuMain");

			_currentQuad2dId = "";

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\quad2d\\diffuse_map\\");

			if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
			{
				Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");

				return;
			}

			const auto filePath = Tools::chooseWindowsExplorerFile((rootPath + targetDirectoryPath), "TGA");

			if(filePath.empty())
			{
				return;
			}

			if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
			{
				Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");

				return;
			}

			const auto finalFilePath = filePath.substr(rootPath.size());

			_fe3d->misc_clearImageCache(finalFilePath);

			_fe3d->quad2d_setDiffuseMap(_currentQuad2dId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * LIGHTNESS_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("opacity", "Opacity", (opacity * OPACITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("textureRepeat", "Texture Repeat", textureRepeat, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isHorizontallyFlipped")->isHovered())
		{
			_fe3d->quad2d_setHorizontallyFlipped(_currentQuad2dId, !isHorizontallyFlipped);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isVerticallyFlipped")->isHovered())
		{
			_fe3d->quad2d_setVerticallyFlipped(_currentQuad2dId, !isVerticallyFlipped);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad2d_setColor(_currentQuad2dId, fvec3((value / COLOR_FACTOR), color.g, color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad2d_setColor(_currentQuad2dId, fvec3(color.r, (value / COLOR_FACTOR), color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad2d_setColor(_currentQuad2dId, fvec3(color.r, color.g, (value / COLOR_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "opacity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad2d_setOpacity(_currentQuad2dId, (value / OPACITY_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad2d_setLightness(_currentQuad2dId, (value / LIGHTNESS_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "textureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->quad2d_setTextureRepeat(_currentQuad2dId, value);
		}

		screen->getButton("isHorizontallyFlipped")->setTextContent(isHorizontallyFlipped ? "Flipped X: ON" : "Flipped X: OFF");
		screen->getButton("isVerticallyFlipped")->setTextContent(isVerticallyFlipped ? "Flipped Y: ON" : "Flipped Y: OFF");
	}
}