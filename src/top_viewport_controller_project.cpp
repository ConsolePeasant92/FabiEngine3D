#include "top_viewport_controller.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

using std::ofstream;

void TopViewportController::_updateProjectCreating()
{
	if(_isCreatingProject)
	{
		string newProjectID;

		if(_gui->getOverlay()->checkValueForm("newProjectID", newProjectID))
		{
			const auto rootPath = Tools::getRootDirectoryPath();
			const string projectDirectoryPath = (rootPath + "projects\\");
			const string newProjectDirectoryPath = (projectDirectoryPath + newProjectID + "\\");

			if(!Tools::isDirectoryExisting(projectDirectoryPath))
			{
				Logger::throwWarning("Directory `projects\\` is missing!");
				return;
			}

			if(newProjectID.find(' ') != string::npos)
			{
				Logger::throwWarning("New project name cannot contain any spaces!");
				return;
			}
			else if(Tools::isDirectoryExisting(newProjectDirectoryPath))
			{
				Logger::throwWarning("Project \"" + newProjectID + "\"" + " already exists!");
				return;
			}
			else if(any_of(newProjectID.begin(), newProjectID.end(), isupper))
			{
				Logger::throwWarning("New project name cannot contain any capitals!");
				return;
			}
			else
			{
				Tools::createDirectory(newProjectDirectoryPath);

				Tools::createDirectory(newProjectDirectoryPath + "assets\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\audio\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\model\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\model\\diffuse_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\model\\emission_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\model\\normal_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\model\\reflection_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\model\\specular_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\quad2d\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\quad2d\\diffuse_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\quad3d\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\quad3d\\diffuse_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\quad3d\\emission_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\sky\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\sky\\cube_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\terrain\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\terrain\\blend_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\terrain\\diffuse_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\terrain\\height_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\text2d\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\text2d\\font_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\text3d\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\text3d\\font_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\water\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\water\\displacement_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\water\\dudv_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\entity\\water\\normal_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\misc\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\image\\misc\\flare_map\\");
				Tools::createDirectory(newProjectDirectoryPath + "assets\\mesh\\");
				Tools::createDirectory(newProjectDirectoryPath + "data\\");
				Tools::createDirectory(newProjectDirectoryPath + "saves\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\custom\\");
				Tools::createDirectory(newProjectDirectoryPath + "worlds\\editor\\");
				Tools::createDirectory(newProjectDirectoryPath + "scripts\\");

				auto animation2dFile = ofstream(newProjectDirectoryPath + "data\\animation2d.fe3d");
				auto animation3dFile = ofstream(newProjectDirectoryPath + "data\\animation3d.fe3d");
				auto quad3dFile = ofstream(newProjectDirectoryPath + "data\\quad3d.fe3d");
				auto modelFile = ofstream(newProjectDirectoryPath + "data\\model.fe3d");
				auto quad2dFile = ofstream(newProjectDirectoryPath + "data\\quad2d.fe3d");
				auto settingsFile = ofstream(newProjectDirectoryPath + "data\\settings.fe3d");
				auto skyFile = ofstream(newProjectDirectoryPath + "data\\sky.fe3d");
				auto soundFile = ofstream(newProjectDirectoryPath + "data\\sound.fe3d");
				auto terrainFile = ofstream(newProjectDirectoryPath + "data\\terrain.fe3d");
				auto textFile = ofstream(newProjectDirectoryPath + "data\\text2d.fe3d");
				auto waterFile = ofstream(newProjectDirectoryPath + "data\\water.fe3d");
				animation2dFile.close();
				animation3dFile.close();
				quad3dFile.close();
				quad2dFile.close();
				modelFile.close();
				settingsFile.close();
				skyFile.close();
				soundFile.close();
				terrainFile.close();
				waterFile.close();

				_currentProjectID = newProjectID;
				_applyProjectChange();

				Logger::throwInfo("New project \"" + _currentProjectID + "\" created!");

				_isCreatingProject = false;
			}
		}
	}
}

void TopViewportController::_updateProjectLoading()
{
	if(_isLoadingProject)
	{
		const auto rootPath = Tools::getRootDirectoryPath();
		const string clickedButtonID = _gui->getOverlay()->checkChoiceForm("projectList");
		const string projectDirectoryPath = string(rootPath + "projects\\" + clickedButtonID + "\\");

		if(!clickedButtonID.empty() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if(isProjectCorrupted(projectDirectoryPath))
			{
				Logger::throwWarning("Cannot load project: missing files/directories!");
				return;
			}

			_currentProjectID = clickedButtonID;
			_applyProjectChange();

			auto skyImagePaths = _skyEditor->getImagePathsFromFile();
			auto terrainImagePaths = _terrainEditor->getImagePathsFromFile();
			auto waterImagePaths = _waterEditor->getImagePathsFromFile();
			auto modelMeshPaths = _modelEditor->getMeshPathsFromFile();
			auto modelImagePaths = _modelEditor->getImagePathsFromFile();
			auto quad3dImagePaths = _quad3dEditor->getImagePathsFromFile();
			auto quad2dImagePaths = _quad2dEditor->getImagePathsFromFile();
			auto textImagePaths = _text2dEditor->getImagePathsFromFile();
			auto audioPaths = _soundEditor->getAudioPathsFromFile();

			_fe3d->misc_cacheMeshes(modelMeshPaths);

			_fe3d->misc_cacheImages(terrainImagePaths);

			vector<string> imagePaths;
			imagePaths.insert(imagePaths.end(), skyImagePaths.begin(), skyImagePaths.end());
			imagePaths.insert(imagePaths.end(), terrainImagePaths.begin(), terrainImagePaths.end());
			imagePaths.insert(imagePaths.end(), waterImagePaths.begin(), waterImagePaths.end());
			imagePaths.insert(imagePaths.end(), modelImagePaths.begin(), modelImagePaths.end());
			imagePaths.insert(imagePaths.end(), quad3dImagePaths.begin(), quad3dImagePaths.end());
			imagePaths.insert(imagePaths.end(), quad2dImagePaths.begin(), quad2dImagePaths.end());
			_fe3d->misc_cacheImages(imagePaths);

			_fe3d->misc_cacheAudios(audioPaths);

			Logger::throwInfo("Existing project \"" + _currentProjectID + "\" loaded!");

			_gui->getOverlay()->deleteChoiceForm("projectList");
			_isLoadingProject = false;
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("projectList"))
		{
			_gui->getOverlay()->deleteChoiceForm("projectList");
			_isLoadingProject = false;
		}
	}
}

void TopViewportController::_updateProjectDeleting()
{
	if(_isDeletingProject)
	{
		static string chosenButtonID = "";
		string clickedButtonID = _gui->getOverlay()->checkChoiceForm("projectList");

		if(!clickedButtonID.empty() && _fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
			chosenButtonID = clickedButtonID;
			_gui->getOverlay()->deleteChoiceForm("projectList");
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("projectList"))
		{
			_gui->getOverlay()->deleteChoiceForm("projectList");
			_isDeletingProject = false;
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			if(chosenButtonID == _currentProjectID)
			{
				_currentProjectID = "";
				_applyProjectChange();
			}

			const auto rootPath = Tools::getRootDirectoryPath();
			const auto directoryPath = (rootPath + "projects\\" + chosenButtonID);
			if(!Tools::isDirectoryExisting(directoryPath))
			{
				Logger::throwWarning("Cannot delete project: missing directory!");
				return;
			}

			Tools::deleteDirectory(directoryPath);

			Logger::throwInfo("Existing project \"" + chosenButtonID + "\" deleted!");

			_isDeletingProject = false;
			chosenButtonID = "";
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_isDeletingProject = false;
			chosenButtonID = "";
		}
	}
}