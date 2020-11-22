#include "top_viewport_controller.hpp"

#include <fstream>
#include <sstream>

#define SCRIPT_EXECUTOR _scriptEditor.getScriptExecutor(false)

TopViewportController::TopViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui,
	EnvironmentEditor& environmentEditor, ModelEditor& modelEditor, BillboardEditor& billboardEditor,
	SceneEditor& sceneEditor, ScriptEditor& scriptEditor, AudioEditor& audioEditor) :
	ViewportController(fe3d, gui),
	_modelEditor(modelEditor),
	_environmentEditor(environmentEditor),
	_billboardEditor(billboardEditor),
	_sceneEditor(sceneEditor),
	_scriptEditor(scriptEditor),
	_audioEditor(audioEditor)
{

}

void TopViewportController::initialize()
{
	// Top-viewport windows
	_gui.getViewport("top")->addWindow("projectWindow", Vec2(-0.25f, 0.0f), Vec2(0.9825f, 1.5f), TVPC::frameColor);
	_gui.getViewport("top")->addWindow("gameWindow", Vec2(0.25f, 0.0f), Vec2(0.9825f, 1.5f), Vec3(0.25f));
	_projectWindow = _gui.getViewport("top")->getWindow("projectWindow");
	_gameWindow = _gui.getViewport("top")->getWindow("gameWindow");
	
	// Top-viewport: projectWindow
	_projectWindow->addScreen("main");
	_projectWindow->setActiveScreen("main");
	auto screen = _projectWindow->getScreen("main");
	screen->addButton("newProject", Vec2(-0.767f, 0.0f), Vec2(0.15f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "NEW", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("loadProject", Vec2(-0.384f, 0.0f), Vec2(0.2f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "LOAD", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("saveProject", Vec2(0.0f, 0.0f), Vec2(0.2f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "SAVE", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("deleteProject", Vec2(0.384f, 0.0f), Vec2(0.3f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "DELETE", TVPC::textColor, TVPC::textHoverColor);
	screen->addButton("quitEngine", Vec2(0.767f, 0.0f), Vec2(0.2f, 1.25f), TVPC::buttonColor, TVPC::buttonHoverColor, "QUIT", TVPC::textColor, TVPC::textHoverColor);

	// Top-viewport: gameWindow
	_gameWindow->addScreen("main");
	_gameWindow->setActiveScreen("main");
	screen = _gameWindow->getScreen("main");
	screen->addButton("play", Vec2(-0.85f, 0.0f), Vec2(0.1f, 1.75f), "play.png", Vec3(2.0f));
	screen->addButton("pause", Vec2(-0.65f, 0.0f), Vec2(0.1f, 1.75f), "pause.png", Vec3(2.0f));
	screen->addButton("restart", Vec2(-0.45f, 0.0f), Vec2(0.1f, 1.75f), "restart.png", Vec3(2.0f));
	screen->addButton("stop", Vec2(-0.25f, 0.0f), Vec2(0.1f, 1.75f), "stop.png", Vec3(2.0f));
}

void TopViewportController::update()
{
	_updateProjectManagement();
	_updateGameManagement();
	_updateMiscellaneous();
}

void TopViewportController::_updateProjectManagement()
{
	auto screen = _projectWindow->getActiveScreen();

	// GUI management
	if (screen->getID() == "main")
	{
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
		{
			if (screen->getButton("newProject")->isHovered())
			{
				_gui.getGlobalScreen()->addValueForm("newProjectName", "Enter project name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
				_creatingProject = true;
			}
			else if (screen->getButton("loadProject")->isHovered())
			{
				_prepareProjectChoosing();
				_loadingProject = true;
			}
			else if (screen->getButton("saveProject")->isHovered())
			{
				_saveCurrentProject();
			}
			else if (screen->getButton("deleteProject")->isHovered())
			{
				_prepareProjectChoosing();
				_deletingProject = true;
			}
			else if (screen->getButton("quitEngine")->isHovered())
			{
				if (_currentProjectName != "") // A project must be loaded
				{
					_gui.getGlobalScreen()->addAnswerForm("exitEngine", "Save changes?", Vec2(0.0f, 0.25f));
				}
				else // Otherwise, just exit the engine
				{
					_fe3d.engine_stop();
				}
			}
		}

		// Update specific processes
		_updateProjectCreation();
		_updateProjectLoading();
		_updateProjectDeletion();

		// Update save button hoverability
		bool scriptRunning = (_currentProjectName == "") ? false : SCRIPT_EXECUTOR.isInitialized();
		screen->getButton("newProject")->setHoverable(!scriptRunning);
		screen->getButton("loadProject")->setHoverable(!scriptRunning);
		screen->getButton("saveProject")->setHoverable(!scriptRunning && _currentProjectName != "");
		screen->getButton("deleteProject")->setHoverable(!scriptRunning);
		screen->getButton("quitEngine")->setHoverable(!scriptRunning);

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitEngine"))
		{
			_saveCurrentProject();
			_fe3d.engine_stop();
		}
		else if (_gui.getGlobalScreen()->isAnswerFormCancelled("exitEngine"))
		{
			_fe3d.engine_stop();
		}
	}

	// Exiting engine through ESCAPE
	if (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "main")
	{
		if (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())
		{
			if (_currentProjectName != "") // A project must be loaded
			{
				_gui.getGlobalScreen()->addAnswerForm("exitEngine", "Save changes?", Vec2(0.0f, 0.25f));
			}
			else // Otherwise, just exit the engine
			{
				_fe3d.engine_stop();
			}
		}
	}
}

void TopViewportController::_updateGameManagement()
{
	auto gameScreen = _gameWindow->getScreen("main");

	// Check if currently a project is loaded
	if (_currentProjectName == "")
	{
		gameScreen->getButton("play")->setHoverable(false);
		gameScreen->getButton("pause")->setHoverable(false);
		gameScreen->getButton("restart")->setHoverable(false);
		gameScreen->getButton("stop")->setHoverable(false);
	}
	else
	{
		// Check if LMB pressed
		if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			if (gameScreen->getButton("play")->isHovered())
			{
				// Unpause game or load game
				if (SCRIPT_EXECUTOR.isInitialized())
				{
					SCRIPT_EXECUTOR.unpause();
				}
				else
				{
					_scriptEditor.getScriptExecutor(true).load();
				}
			}
			else if (gameScreen->getButton("pause")->isHovered())
			{
				SCRIPT_EXECUTOR.pause();
			}
			else if (gameScreen->getButton("restart")->isHovered())
			{
				SCRIPT_EXECUTOR.unload();
				_scriptEditor.getScriptExecutor(true).load();
			}
			else if (gameScreen->getButton("stop")->isHovered())
			{
				SCRIPT_EXECUTOR.unload();
			}
		}

		// Game buttons hoverability
		bool isInMainMenu = (_gui.getViewport("left")->getWindow("main")->getActiveScreen()->getID() == "main");
		gameScreen->getButton("play")->setHoverable(isInMainMenu && !SCRIPT_EXECUTOR.isScriptEmpty() && !SCRIPT_EXECUTOR.isRunning());
		gameScreen->getButton("pause")->setHoverable(isInMainMenu && SCRIPT_EXECUTOR.isRunning());
		gameScreen->getButton("restart")->setHoverable(isInMainMenu && SCRIPT_EXECUTOR.isInitialized());
		gameScreen->getButton("stop")->setHoverable(isInMainMenu && SCRIPT_EXECUTOR.isInitialized());

		// Check if player wants to pause the running game
		if (SCRIPT_EXECUTOR.isRunning())
		{
			if (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				SCRIPT_EXECUTOR.pause();
			}
		}

		// Executing game script (if possible)
		SCRIPT_EXECUTOR.update();
	}

}

void TopViewportController::_saveCurrentProject()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to save as empty project!");
	}

	// Save everything
	_environmentEditor.save();
	_modelEditor.saveGameEntitiesToFile();
	_billboardEditor.saveBillboardEntitiesToFile();
	_sceneEditor.saveSceneToFile();
	_scriptEditor.saveScriptsToFile();
	_audioEditor.saveAudioEntitiesToFile();

	// Logging
	_fe3d.logger_throwInfo("Project \"" + _currentProjectName + "\" saved!");
}

void TopViewportController::_updateCurrentProject()
{
	// Change window title
	if (_currentProjectName == "")
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D");
	}
	else
	{
		_fe3d.misc_setWindowTitle("FabiEngine3D - " + _currentProjectName);
	}

	// Go back to main editor screen
	_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");

	// Unload environment editor
	if (_environmentEditor.isLoaded())
	{
		_environmentEditor.unload();
	}

	// Unload model editor
	if (_modelEditor.isLoaded())
	{
		_modelEditor.unload();
	}

	// Unload billboard editor
	if (_billboardEditor.isLoaded())
	{
		_billboardEditor.unload();
	}

	// Unload scene editor
	if (_sceneEditor.isLoaded())
	{
		_sceneEditor.unload();
	}

	// Unload script editor
	if (_scriptEditor.isLoaded())
	{
		_scriptEditor.unload();
	}

	// Unload audio editor
	if (_audioEditor.isLoaded())
	{
		_audioEditor.unload();
	}

	// Pass loaded project name
	_environmentEditor.setCurrentProjectName(_currentProjectName);
	_modelEditor.setCurrentProjectName(_currentProjectName);
	_billboardEditor.setCurrentProjectName(_currentProjectName);
	_sceneEditor.setCurrentProjectName(_currentProjectName);
	_scriptEditor.setCurrentProjectName(_currentProjectName);
	_audioEditor.setCurrentProjectName(_currentProjectName);
}