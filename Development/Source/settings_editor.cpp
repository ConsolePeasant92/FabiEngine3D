#include "settings_editor.hpp"
#include "left_viewport_controller.hpp"
#include "logger.hpp"
#include "configuration.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

SettingsEditor::SettingsEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void SettingsEditor::_loadGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	string screenID;

	// Left-viewport: mainWindow - settingsEditorMenuMain
	screenID = "settingsEditorMenuMain";
	leftWindow->addScreen(screenID);
	leftWindow->getScreen(screenID)->addButton("isFxaaEnabled", Vec2(0.0f, 0.75f), Vec2(CW("FXAA: ON"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "FXAA: ON", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("shadowQuality", Vec2(0.0f, 0.45f), Vec2(CW("Shadows"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Shadows", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("reflectionQuality", Vec2(0.0f, 0.15f), Vec2(CW("Reflections"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Reflections", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("refractionQuality", Vec2(0.0f, -0.15f), Vec2(CW("Refractions"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Refractions", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("maxAudioChannels", Vec2(0.0f, -0.45f), Vec2(CW("Audio"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen(screenID)->addButton("back", Vec2(0.0f, -0.75f), Vec2(CW("Go Back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go Back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void SettingsEditor::_unloadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	leftWindow->deleteScreen("settingsEditorMenuMain");
}

void SettingsEditor::loadSettings()
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("No current project loaded --> SettingsEditor::loadSettings()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\settings.fe3d";

	// Check if settings file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Open settings file
		std::ifstream file(filePath);
		string line;
		std::getline(file, line);
		std::istringstream iss(line);

		// Extract values from file
		unsigned int shadowQuality, reflectionQuality, refractionQuality, audioChannels;
		bool isFxaaEnabled;
		iss >> isFxaaEnabled >> shadowQuality >> reflectionQuality >> refractionQuality >> audioChannels;

		// Disable FXAA
		if (_fe3d.gfx_isFxaaEnabled())
		{
			_fe3d.gfx_disableFXAA(true);
		}

		// Set values
		isFxaaEnabled ? _fe3d.gfx_enableFXAA() : void();
		_fe3d.gfx_setShadowQuality(shadowQuality);
		_fe3d.gfx_setReflectionQuality(reflectionQuality);
		_fe3d.gfx_setRefractionQuality(refractionQuality);
		_fe3d.misc_setMaxAudioChannels(audioChannels);

		// Close file
		file.close();
	}
	else
	{
		Logger::throwError("Project \"" + _currentProjectID + "\" corrupted: \"settings.fe3d\" missing!");
	}
}

void SettingsEditor::load()
{
	// GUI
	_loadGUI();

	// Settings
	loadSettings();
	
	// Miscellaneous
	_fe3d.gfx_enableBloom(BloomType::PARTS, 1.0f, 5);
	_fe3d.billboardEntity_add("@@icon", "engine_assets\\textures\\settings.png", 
		Vec3(0.0f, -0.5f, -1.5f), Vec3(0.0f), Vec2(1.0f), true, false, false);
	_fe3d.billboardEntity_setBloomed("@@icon", true);
	_fe3d.camera_load(Config::DEFAULT_CAMERA_FOV, Config::DEFAULT_CAMERA_NEAR, Config::DEFAULT_CAMERA_FAR, Vec3(0.0f), -90.0f, 0.0f);
	_isEditorLoaded = true;
}

void SettingsEditor::unload()
{
	// GUI
	_unloadGUI();

	// Miscellaneous
	_fe3d.gfx_disableBloom();
	_fe3d.billboardEntity_delete("@@icon");
	_isEditorLoaded = false;
}

void SettingsEditor::save(bool newFile)
{
	// Error checking
	if (_currentProjectID == "")
	{
		Logger::throwError("No current project loaded --> SettingsEditor::save()");
	}

	// Compose full file path
	string filePath = _fe3d.misc_getRootDirectory() + (_fe3d.application_isExported() ? "" : ("projects\\" + _currentProjectID)) + "\\settings.fe3d";

	// Overwrite (or create) settings file
	std::ofstream file;
	file.open(filePath);

	// Get values
	auto isFxaaEnabled = _fe3d.gfx_isFxaaEnabled();
	auto shadowQuality = _fe3d.gfx_getShadowQuality();
	auto reflectionQuality = _fe3d.gfx_getReflectionQuality();
	auto refractionQuality = _fe3d.gfx_getRefractionQuality();
	auto audioChannels = _fe3d.misc_getMaxChannels();

	// Default values for new file
	if (newFile)
	{
		isFxaaEnabled = true;
		shadowQuality = 2048;
		reflectionQuality = 256;
		refractionQuality = 256;
		audioChannels = 128;
	}

	// Write to file
	file <<
		isFxaaEnabled << " " <<
		shadowQuality << " " <<
		reflectionQuality << " " <<
		refractionQuality << " " <<
		audioChannels;

	// Close file
	file.close();
}

const string& SettingsEditor::getCurrentProjectID()
{
	return _currentProjectID;
}

void SettingsEditor::update()
{
	if (_isEditorLoaded)
	{
		// Temporary values
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "settingsEditorMenuMain")
		{
			// Temporary values
			int isFxaaEnabled = _fe3d.gfx_isFxaaEnabled();
			int shadowQuality = _fe3d.gfx_getShadowQuality();
			int reflectionQuality = _fe3d.gfx_getReflectionQuality();
			int refractionQuality = _fe3d.gfx_getRefractionQuality();
			int audioChannels = _fe3d.misc_getMaxChannels();

			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					unload();
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
					return;
				}
				else if (screen->getButton("isFxaaEnabled")->isHovered())
				{
					isFxaaEnabled = !isFxaaEnabled;
					isFxaaEnabled ? _fe3d.gfx_enableFXAA() : _fe3d.gfx_disableFXAA();
					save(false);
				}
				else if (screen->getButton("shadowQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("shadowQuality", "Shadow Quality", shadowQuality, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("reflectionQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("reflectionQuality", "Reflection Quality", reflectionQuality, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("refractionQuality")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("refractionQuality", "Refraction Quality", refractionQuality, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				}
				else if (screen->getButton("maxAudioChannels")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("maxAudioChannels", "Max Audio Channels", audioChannels, Vec2(0.0f, 0.0f), Vec2(0.15f, 0.1f));
				}
			}

			// Update forms
			if (_gui.getGlobalScreen()->checkValueForm("shadowQuality", shadowQuality, {}))
			{
				_fe3d.gfx_setShadowQuality(std::clamp(shadowQuality, 512, 8192));
				save(false);
			}
			else if (_gui.getGlobalScreen()->checkValueForm("reflectionQuality", reflectionQuality, {}))
			{
				_fe3d.gfx_setReflectionQuality(std::clamp(reflectionQuality, 128, 2048));
				save(false);
			}
			else if (_gui.getGlobalScreen()->checkValueForm("refractionQuality", refractionQuality, {}))
			{
				_fe3d.gfx_setRefractionQuality(std::clamp(refractionQuality, 128, 2048));
				save(false);
			}
			else if (_gui.getGlobalScreen()->checkValueForm("maxAudioChannels", audioChannels, {}))
			{
				_fe3d.misc_setMaxAudioChannels(std::clamp(audioChannels, 32, 512));
				save(false);
			}

			// Update button contents
			screen->getButton("isFxaaEnabled")->changeTextContent(isFxaaEnabled ? "FXAA: ON" : "FXAA: OFF");

			// Miscellaneous
			_fe3d.billboardEntity_rotate("@@icon", Vec3(0.0f, 0.5f, 0.0f));
		}
	}
}

void SettingsEditor::setCurrentProjectID(const string& projectID)
{
	_currentProjectID = projectID;
}