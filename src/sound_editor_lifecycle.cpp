#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)

#include "sound_editor.hpp"
#include "left_viewport_controller.hpp"
#include "configuration.hpp"
#include "tools.hpp"

void SoundEditor::_load()
{
	_fe3d->gfx_setAntiAliasingEnabled(true);
	_fe3d->gfx_setAnisotropicFilteringQuality(16);
	_fe3d->gfx_setBloomEnabled(true);
	_fe3d->gfx_setBloomType(BloomType::PARTS);
	_fe3d->gfx_setBloomIntensity(1.0f);
	_fe3d->gfx_setBloomBlurCount(5);
	_fe3d->gfx_setBloomQuality(5);

	_fe3d->camera_reset();
	_fe3d->camera_setYaw(270.0f);

	_fe3d->quad3d_create("@@icon", true);
	_fe3d->quad3d_setPosition("@@icon", ICON_QUAD_POSITION);
	_fe3d->quad3d_setDiffuseMap("@@icon", "engine\\assets\\image\\diffuse_map\\stop.tga");
	_fe3d->quad3d_setBright("@@icon", true);

	_gui->getOverlay()->createTextField("soundId", fvec2(0.0f, 0.85f), fvec2(0.5f, 0.1f), "", fvec3(1.0f), true);
}

void SoundEditor::_unload()
{
	for(const auto& id : _loadedSoundIds)
	{
		_fe3d->sound2d_delete(id);
	}

	_fe3d->gfx_setAntiAliasingEnabled(false);
	_fe3d->gfx_setAnisotropicFilteringQuality(0);
	_fe3d->gfx_setBloomEnabled(false);
	_fe3d->gfx_setBloomType(BloomType::EVERYTHING);
	_fe3d->gfx_setBloomIntensity(0.0f);
	_fe3d->gfx_setBloomBlurCount(0);
	_fe3d->gfx_setBloomQuality(0);

	_fe3d->quad3d_delete("@@icon");

	_gui->getOverlay()->deleteTextField("soundId");

	_loadedSoundIds.clear();
	_currentSoundId = "";
	_hoveredSoundId = "";
	_isCreatingSound = false;
	_isChoosingSound = false;
	_isDeletingSound = false;
}

void SoundEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");

	auto positions = Math::calculateDistributedPositions(4, CH);
	leftWindow->createScreen("soundEditorMenuMain");
	leftWindow->getScreen("soundEditorMenuMain")->createButton("create", fvec2(0.0f, positions[0]), TEXT_SIZE("Create Sound"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Sound", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("edit", fvec2(0.0f, positions[1]), TEXT_SIZE("Edit Sound"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Sound", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("delete", fvec2(0.0f, positions[2]), TEXT_SIZE("Delete Sound"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Sound", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuMain")->createButton("back", fvec2(0.0f, positions[3]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	positions = Math::calculateDistributedPositions(5, CH);
	leftWindow->createScreen("soundEditorMenuChoice");
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("play", fvec2(0.0f, positions[0]), TEXT_SIZE("Play"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Play", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("resume", fvec2(0.0f, positions[1]), TEXT_SIZE("Resume"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Resume", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("pause", fvec2(0.0f, positions[2]), TEXT_SIZE("Pause"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Pause", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("stop", fvec2(0.0f, positions[3]), TEXT_SIZE("Stop"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Stop", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	leftWindow->getScreen("soundEditorMenuChoice")->createButton("back", fvec2(0.0f, positions[4]), TEXT_SIZE("Go Back"), BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);
}

void SoundEditor::_unloadGUI()
{
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("soundEditorMenuMain");
	_gui->getLeftViewport()->getWindow("main")->deleteScreen("soundEditorMenuChoice");
}

void SoundEditor::update()
{
	if(isLoaded())
	{
		_updateMainMenu();
	}
	if(isLoaded())
	{
		_updateChoiceMenu();
	}
	if(isLoaded())
	{
		_updateSoundCreating();
	}
	if(isLoaded())
	{
		_updateSoundChoosing();
	}
	if(isLoaded())
	{
		_updateSoundDeleting();
	}
	if(isLoaded())
	{
		_updateMiscellaneous();
	}
}