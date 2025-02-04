#include "terrain_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void TerrainEditor::_updateDiffuseTexturingMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "terrainEditorMenuDiffuseTexturing")
	{
		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("terrainEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("diffuseMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\terrain\\diffuse_map\\");

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

			_fe3d->terrain_setDiffuseMap(_currentTerrainId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("redDiffuseMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\terrain\\diffuse_map\\");

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

			_fe3d->terrain_setRedDiffuseMap(_currentTerrainId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("greenDiffuseMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\terrain\\diffuse_map\\");

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

			_fe3d->terrain_setGreenDiffuseMap(_currentTerrainId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("blueDiffuseMap")->isHovered())
		{
			if(getCurrentProjectId().empty())
			{
				abort();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\image\\terrain\\diffuse_map\\");

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

			_fe3d->terrain_setBlueDiffuseMap(_currentTerrainId, finalFilePath);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("clearDiffuseMap")->isHovered())
		{
			_fe3d->terrain_setDiffuseMap(_currentTerrainId, "");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("clearRedDiffuseMap")->isHovered())
		{
			_fe3d->terrain_setRedDiffuseMap(_currentTerrainId, "");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("clearGreenDiffuseMap")->isHovered())
		{
			_fe3d->terrain_setGreenDiffuseMap(_currentTerrainId, "");
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("clearBlueDiffuseMap")->isHovered())
		{
			_fe3d->terrain_setBlueDiffuseMap(_currentTerrainId, "");
		}
	}
}