#include "top_viewport_controller.hpp"
#include "configuration.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>

using TVPC = TopViewportController;

TopViewportController::TopViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui, SkyEditor& skyEditor, TerrainEditor& terrainEditor, WaterEditor& waterEditor, ModelEditor& modelEditor, AnimationEditor& animationEditor, BillboardEditor& billboardEditor, AudioEditor& audioEditor, SceneEditor& sceneEditor, ScriptEditor& scriptEditor, SettingsEditor& settingsEditor)
	:
	BaseViewportController(fe3d, gui),
	_skyEditor(skyEditor),
	_terrainEditor(terrainEditor),
	_waterEditor(waterEditor),
	_modelEditor(modelEditor),
	_animationEditor(animationEditor),
	_billboardEditor(billboardEditor),
	_audioEditor(audioEditor),
	_sceneEditor(sceneEditor),
	_scriptEditor(scriptEditor),
	_settingsEditor(settingsEditor)
{

}

void TopViewportController::initialize()
{
	// Top-viewport windows
	_gui.getViewport("top")->createWindow("projectWindow", Vec2(-0.25f, 0.0f), Vec2(0.9875f, 1.5f), TVPC::FRAME_COLOR);
	_gui.getViewport("top")->createWindow("runWindow", Vec2(0.125f, 0.0f), Vec2(0.4875f, 1.5f), TVPC::FRAME_COLOR);
	_gui.getViewport("top")->createWindow("miscWindow", Vec2(0.375f, 0.0f), Vec2(0.4875f, 1.5f), TVPC::FRAME_COLOR);
	_projectWindow = _gui.getViewport("top")->getWindow("projectWindow");
	_gameWindow = _gui.getViewport("top")->getWindow("runWindow");
	_miscWindow = _gui.getViewport("top")->getWindow("miscWindow");

	// Top-viewport: projectWindow
	_projectWindow->createScreen("main");
	_projectWindow->setActiveScreen("main");
	auto screen = _projectWindow->getScreen("main");
	screen->createButton("newProject", Vec2(-0.767f, 0.0f), Vec2(0.15f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "NEW", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	screen->createButton("loadProject", Vec2(-0.384f, 0.0f), Vec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "LOAD", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	screen->createButton("saveProject", Vec2(0.0f, 0.0f), Vec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "SAVE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	screen->createButton("deleteProject", Vec2(0.384f, 0.0f), Vec2(0.3f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "DELETE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	screen->createButton("quitEngine", Vec2(0.767f, 0.0f), Vec2(0.2f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "QUIT", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);

	// Top-viewport: gameWindow
	_gameWindow->createScreen("main");
	_gameWindow->setActiveScreen("main");
	screen = _gameWindow->getScreen("main");
	screen->createButton("play", Vec2(-0.73f, 0.0f), Vec2(0.2f, 1.75f), "play.png", Vec3(2.0f), true, true, true);
	screen->createButton("pause", Vec2(-0.36f, 0.0f), Vec2(0.2f, 1.75f), "pause.png", Vec3(2.0f), true, true, true);
	screen->createButton("restart", Vec2(0.0f, 0.0f), Vec2(0.2f, 1.75f), "restart.png", Vec3(2.0f), true, true, true);
	screen->createButton("stop", Vec2(0.36f, 0.0f), Vec2(0.2f, 1.75f), "stop.png", Vec3(2.0f), true, true, true);
	screen->createButton("debug", Vec2(0.73f, 0.0f), Vec2(0.2f, 1.75f), "debug.png", Vec3(2.0f), true, true, true);

	// Top-viewport: miscWindow
	_miscWindow->createScreen("main");
	_miscWindow->setActiveScreen("main");
	screen = _miscWindow->getScreen("main");
	screen->createButton("uncache", Vec2(-0.5875f, 0.0f), Vec2(0.55f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "UNCACHE", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	screen->createButton("export", Vec2(0.075f, 0.0f), Vec2(0.5f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "EXPORT", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
	screen->createButton("docs", Vec2(0.6625f, 0.0f), Vec2(0.4f, 1.25f), TVPC::BUTTON_COLOR, TVPC::BUTTON_HOVER_COLOR, "DOCS", TVPC::TEXT_COLOR, TVPC::TEXT_HOVER_COLOR, true, true, true);
}

void TopViewportController::update()
{
	_updateProjectScreenManagement();
	_updateGameScreenManagement();
	_updateMiscScreenManagement();
	_updateMiscellaneous();
}

void TopViewportController::_updateProjectScreenManagement()
{
	// Temporary values
	auto topScreen = _projectWindow->getActiveScreen();
	auto leftScreen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(topScreen->getID() == "main")
	{
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if(topScreen->getButton("newProject")->isHovered())
			{
				_gui.getGlobalScreen()->createValueForm("newProjectID", "Create Project", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
				_isCreatingProject = true;
			}
			else if(topScreen->getButton("loadProject")->isHovered())
			{
				if(_prepareProjectChoosing("Load Project"))
				{
					_isLoadingProject = true;
				}
			}
			else if(topScreen->getButton("saveProject")->isHovered())
			{
				_saveCurrentProject();
			}
			else if(topScreen->getButton("deleteProject")->isHovered())
			{
				if(_prepareProjectChoosing("Delete Project"))
				{
					_isDeletingProject = true;
				}
			}
			else if(topScreen->getButton("quitEngine")->isHovered())
			{
				// Check if currently in an editor (except for scene editor)
				if(_currentProjectID != "" && leftScreen->getID() != "main" && leftScreen->getID() != "sceneEditorMenuMain")
				{
					_gui.getGlobalScreen()->createAnswerForm("quit", "Save Changes?", Vec2(0.0f, 0.25f));
				}
				else // Otherwise, just stop the engine
				{
					_fe3d.application_stop();
				}
			}
		}

		// Update specific processes
		_updateProjectCreating();
		_updateProjectLoading();
		_updateProjectDeleting();

		// Quitting with ESCAPE
		if(_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && (leftScreen->getID() == "main") && !_gui.getGlobalScreen()->isFocused())
		{
			// Check if script execution not started
			if(!_scriptEditor.getScriptExecutor().isStarted())
			{
				_fe3d.application_stop();
			}
		}

		// Update answer forms
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("quit"))
		{
			_saveCurrentProject();
			_fe3d.application_stop();
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("quit"))
		{
			_fe3d.application_stop();
		}

		// Update buttons hoverability
		topScreen->getButton("saveProject")->setHoverable(_currentProjectID != "");
	}
}

void TopViewportController::_updateGameScreenManagement()
{
	// Temporary values
	auto projectScreen = _projectWindow->getActiveScreen();
	auto gameScreen = _gameWindow->getScreen("main");
	auto miscScreen = _miscWindow->getScreen("main");

	// Check if currently a project is loaded
	if(_currentProjectID.empty())
	{
		gameScreen->getButton("play")->setHoverable(false);
		gameScreen->getButton("pause")->setHoverable(false);
		gameScreen->getButton("restart")->setHoverable(false);
		gameScreen->getButton("stop")->setHoverable(false);
		gameScreen->getButton("debug")->setHoverable(false);
	}
	else
	{
		// Check if LMB pressed
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if(gameScreen->getButton("play")->isHovered())
			{
				// Resume game or load game
				if(_scriptEditor.getScriptExecutor().isStarted())
				{
					_scriptEditor.getScriptExecutor().resume();
				}
				else
				{
					_scriptEditor.loadScriptFiles(true);
					_scriptEditor.getScriptExecutor().load();
				}
			}
			else if(gameScreen->getButton("pause")->isHovered())
			{
				_scriptEditor.getScriptExecutor().pause();
			}
			else if(gameScreen->getButton("restart")->isHovered())
			{
				_scriptEditor.getScriptExecutor().unload();
				_scriptEditor.loadScriptFiles(true);
				_scriptEditor.getScriptExecutor().load();
			}
			else if(gameScreen->getButton("stop")->isHovered())
			{
				_scriptEditor.getScriptExecutor().unload();
			}
			else if(gameScreen->getButton("debug")->isHovered())
			{
				_scriptEditor.getScriptExecutor().resume();
				_scriptEditor.getScriptExecutor().update(true);
				_scriptEditor.getScriptExecutor().pause();
			}
		}

		// Update buttons hoverability
		static bool wasInMainMenu = false;
		bool isInMainMenu = (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "main");
		gameScreen->getButton("play")->setHoverable(isInMainMenu && !_scriptEditor.getScriptExecutor().isScriptEmpty() && !isScriptRunning());
		gameScreen->getButton("pause")->setHoverable(isInMainMenu && isScriptRunning() && !_fe3d.networkServer_isRunning());
		gameScreen->getButton("restart")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());
		gameScreen->getButton("stop")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());
		gameScreen->getButton("debug")->setHoverable(isInMainMenu && _scriptEditor.getScriptExecutor().isStarted());
		projectScreen->getButton("newProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
		projectScreen->getButton("loadProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
		projectScreen->getButton("saveProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
		projectScreen->getButton("deleteProject")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());
		miscScreen->getButton("uncache")->setHoverable(!_scriptEditor.getScriptExecutor().isStarted());

		// Reload script files every second or if user came into menu
		bool cameIntoMenu = (!wasInMainMenu && isInMainMenu);
		if(cameIntoMenu || (isInMainMenu && !isScriptStarted() && _fe3d.misc_checkInterval(Config::UPDATES_PER_SECOND)))
		{
			_scriptEditor.loadScriptFiles(false);
		}
		wasInMainMenu = isInMainMenu;

		// Check if user wants to pause the running game
		if(_scriptEditor.getScriptExecutor().isRunning())
		{
			// Check if ESCAPE pressed
			if(_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if(_fe3d.networkServer_isRunning()) // Server application cannot be paused, only on or off
				{
					_scriptEditor.getScriptExecutor().unload();
				}
				else // Non-server application can be paused
				{
					_scriptEditor.getScriptExecutor().pause();
				}
			}
		}

		// Executing game script (if possible)
		_scriptEditor.getScriptExecutor().update(false);
	}
}

void TopViewportController::_updateMiscScreenManagement()
{
	// Temporary values
	auto screen = _miscWindow->getScreen("main");

	// Button management
	if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("uncache")->isHovered())
	{
		// Get the chosen file name
		const auto rootDirectoryPath = Tools::getRootDirectoryPath();
		const string targetDirectoryPath = string("game_assets\\");

		// Validate target directory
		if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
		{
			Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
			return;
		}

		// Validate chosen file
		const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "");
		if(filePath.empty())
		{
			return;
		}

		// Validate directory of file
		if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
		   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
		{
			Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
			return;
		}

		// Clear the cache of selected file
		const string newFilePath = filePath.substr(rootDirectoryPath.size());
		_fe3d.misc_clearMeshCache(newFilePath);
		_fe3d.misc_clearFontCache(newFilePath);
		_fe3d.misc_clearTextureCache2D(newFilePath);
		_fe3d.misc_clearBitmapCache(newFilePath);
		_fe3d.misc_clearAudioCache(newFilePath);
	}
	else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("export")->isHovered())
	{
		// Validate chosen directory
		const string chosenDirectoryPath = Tools::chooseExplorerDirectory("");
		if(chosenDirectoryPath.empty())
		{
			return;
		}

		// Compose important paths
		const string rootDirectoryPath = Tools::getRootDirectoryPath();
		const string exportDirectoryPath = string(chosenDirectoryPath + "\\" + _currentProjectID + "\\");

		// Create application directory
		Tools::createDirectory(exportDirectoryPath);

		// Copy main directories
		Tools::copyDirectory(string(rootDirectoryPath + "binaries"), string(exportDirectoryPath + "binaries"));
		Tools::copyDirectory(string(rootDirectoryPath + "engine_assets"), string(exportDirectoryPath + "engine_assets"));
		Tools::copyDirectory(string(rootDirectoryPath + "game_assets"), string(exportDirectoryPath + "game_assets"));
		Tools::copyDirectory(string(rootDirectoryPath + "shaders"), string(exportDirectoryPath + "shaders"));

		// Copy project directories
		Tools::copyDirectory(string(rootDirectoryPath + "projects\\" + _currentProjectID + "\\data"), string(exportDirectoryPath + "data"));
		Tools::copyDirectory(string(rootDirectoryPath + "projects\\" + _currentProjectID + "\\saves"), string(exportDirectoryPath + "saves"));
		Tools::copyDirectory(string(rootDirectoryPath + "projects\\" + _currentProjectID + "\\scenes"), string(exportDirectoryPath + "scenes"));
		Tools::copyDirectory(string(rootDirectoryPath + "projects\\" + _currentProjectID + "\\scripts"), string(exportDirectoryPath + "scripts"));

		// Copy project files
		Tools::copyFile(string(rootDirectoryPath + "projects\\" + _currentProjectID + "\\config.fe3d"), string(exportDirectoryPath + "config.fe3d"));
	}
	else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("docs")->isHovered())
	{
		ShellExecute(0, 0, "https://github.com/ConsolePeasant92/FabiEngine3D/blob/master/README.md", 0, 0, SW_SHOW);
	}

	// Update buttons hoverability
	screen->getButton("export")->setHoverable(!_currentProjectID.empty());
}

void TopViewportController::_saveCurrentProject()
{
	// Error checking
	if(_currentProjectID.empty())
	{
		Logger::throwError("TopViewportController::_saveCurrentProject");
	}

	// Save everything
	_skyEditor.saveSkyEntitiesToFile();
	_terrainEditor.saveTerrainEntitiesToFile();
	_waterEditor.saveWaterEntitiesToFile();
	_modelEditor.saveModelEntitiesToFile();
	_animationEditor.saveAnimationsToFile();
	_billboardEditor.saveBillboardEntitiesToFile();
	_audioEditor.saveAudioEntitiesToFile();
	_sceneEditor.saveEditorSceneToFile();
	_scriptEditor.saveScriptFiles();
	_settingsEditor.saveSettingsToFile();

	// Logging
	Logger::throwInfo("Project \"" + _currentProjectID + "\" saved!");
}