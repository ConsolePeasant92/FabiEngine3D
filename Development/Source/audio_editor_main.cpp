#include "audio_editor.hpp"
#include "left_viewport_controller.hpp"

#define CW(text) VPC::calculateTextWidth(text, 0.115f)

constexpr auto TH = 0.0875f;

AudioEditor::AudioEditor(FabiEngine3D& fe3d, EngineGuiManager& gui) :
	_fe3d(fe3d),
	_gui(gui)
{

}

void AudioEditor::_loadGUI()
{
	// Private window instance of left viewport
	auto leftWindow = _gui.getViewport("left")->getWindow("main");

	// Left-viewport: mainWindow - audioEditorMenuMain
	leftWindow->addScreen("audioEditorMenuMain");
	leftWindow->getScreen("audioEditorMenuMain")->addButton("addAudio", Vec2(0.0f, 0.63f), Vec2(CW("Add audio"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Add audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuMain")->addButton("editAudio", Vec2(0.0f, 0.21f), Vec2(CW("Edit audio"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Edit audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuMain")->addButton("deleteAudio", Vec2(0.0f, -0.21f), Vec2(CW("Delete audio"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Delete audio", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuMain")->addButton("back", Vec2(0.0f, -0.63f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);

	// Left-viewport: mainWindow - audioEditorMenuChoice
	leftWindow->addScreen("audioEditorMenuChoice");
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("load", Vec2(0.0f, 0.75f), Vec2(CW("Load WAV"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Load WAV", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("play", Vec2(0.0f, 0.45f), Vec2(CW("Play"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Play", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("resume", Vec2(0.0f, 0.15f), Vec2(CW("Resume"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Resume", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("pause", Vec2(0.0f, -0.15f), Vec2(CW("Pause"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Pause", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("stop", Vec2(0.0f, -0.45f), Vec2(CW("Stop"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Stop", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
	leftWindow->getScreen("audioEditorMenuChoice")->addButton("back", Vec2(0.0f, -0.75f), Vec2(CW("Go back"), TH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Go back", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR);
}

void AudioEditor::_unloadGUI()
{
	auto leftWindow = _gui.getViewport("left")->getWindow("main");
	leftWindow->deleteScreen("audioEditorMenuMain");
	leftWindow->deleteScreen("audioEditorMenuChoice");
}

void AudioEditor::load()
{
	// GUI
	_loadGUI();

	// Load all audio entities
	loadAudioEntitiesFromFile();

	// Miscellaneous
	_fe3d.billboardEntity_add("@@audioStatus", "engine_assets\\textures\\stop.png", Vec3(0.0f, -0.5f, -1.5f), Vec3(0.0f), Vec2(1.0f), true, false, false, true);
	_fe3d.camera_load(90.0f, 0.1f, 10000.0f, Vec3(0.0f), -90.0f, 0.0f);
	_gui.getGlobalScreen()->addTextfield("selectedAudioName", Vec2(0.0f, 0.85f), Vec2(0.5f, 0.1f), "", Vec3(1.0f));
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("audioEditorControls");
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_isEditorLoaded = true;
}

void AudioEditor::unload()
{
	// GUI
	_unloadGUI();

	// Delete everything
	_fe3d.billboardEntity_delete("@@audioStatus");
	_fe3d.soundEntity_deleteAll();
	_gui.getGlobalScreen()->deleteTextfield("selectedAudioName");
	_gui.getViewport("right")->getWindow("main")->setActiveScreen("mainMenuControls");

	// Reset editor properties
	_loadedAudioIDs.clear();
	_currentAudioID = "";
	_hoveredAudioID = "";
	_isCreatingAudio = false;
	_isChoosingAudio = false;
	_isEditingAudio = false;
	_isRemovingAudio = false;

	// Miscellaneous
	_fe3d.input_clearMouseToggles();
	_fe3d.input_clearKeyToggles();
	_isEditorLoaded = false;
}