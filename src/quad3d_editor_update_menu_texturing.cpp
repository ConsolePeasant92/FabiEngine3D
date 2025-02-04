#include "quad3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad3dEditor::_updateTexturingMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuTexturing")
	{
		const auto textureRepeat = _fe3d->quad3d_getTextureRepeat(_currentQuad3dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\quad3d\\diffuse_map\\");

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

			_fe3d->quad3d_setDiffuseMap(_currentQuad3dId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("emissionMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\quad3d\\emission_map\\");

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

			_fe3d->quad3d_setEmissionMap(_currentQuad3dId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("clearDiffuseMap")->isHovered())
		{
			_fe3d->quad3d_setDiffuseMap(_currentQuad3dId, "");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("clearEmissionMap")->isHovered())
		{
			_fe3d->quad3d_setEmissionMap(_currentQuad3dId, "");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("textureRepeat")->isHovered())
		{
			_gui->getOverlay()->openValueForm("textureRepeat", "Texture Repeat", textureRepeat, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}

		if((_gui->getOverlay()->getValueFormId() == "textureRepeat") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? Tools::parseInteger(content) : 0);

			_fe3d->quad3d_setTextureRepeat(_currentQuad3dId, value);
		}
	}
}