#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "sound2d_editor.hpp"
#include "tools.hpp"

void Sound2dEditor::_load()
{
	_fe3d->quad3d_create(STATUS_ID, true);
	_fe3d->quad3d_setPosition(STATUS_ID, STATUS_QUAD3D_POSITION);
	_fe3d->quad3d_setDiffuseMap(STATUS_ID, STATUS_STOP_TEXTURE_PATH);
	_fe3d->quad3d_setBright(STATUS_ID, true);
	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->graphics_setAnisotropicFilteringQuality(ANISOTROPIC_FILTERING_QUALITY);
	_fe3d->graphics_setBloomEnabled(true);
	_fe3d->graphics_setBloomType(BLOOM_TYPE);
	_fe3d->graphics_setBloomIntensity(BLOOM_INTENSITY);
	_fe3d->graphics_setBloomBlurCount(BLOOM_BLUR_COUNT);
	_fe3d->graphics_setBloomQuality(BLOOM_QUALITY);
	_fe3d->camera_setYaw(CAMERA_YAW);

	_gui->getOverlay()->createTextField(SOUND2D_TITLE_ID, SOUND2D_TITLE_POSITION, SOUND2D_TITLE_SIZE, "", fvec3(1.0f), true);
}

void Sound2dEditor::_unload()
{
	for(const auto & sound2dId : _loadedSound2dIds)
	{
		_fe3d->sound2d_delete(sound2dId);
	}

	_fe3d->quad3d_delete(STATUS_ID);
	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->graphics_setAnisotropicFilteringQuality(0);
	_fe3d->graphics_setBloomEnabled(false);
	_fe3d->graphics_setBloomType(BloomType::EVERYTHING);
	_fe3d->graphics_setBloomIntensity(0.0f);
	_fe3d->graphics_setBloomBlurCount(0);
	_fe3d->graphics_setBloomQuality(0);
	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField(SOUND2D_TITLE_ID);

	_loadedSound2dIds.clear();
}

void Sound2dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->createScreen("sound2dEditorMenuMain");
	rightWindow->getScreen("sound2dEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Sound2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Sound2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound2dEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Sound2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Sound2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound2dEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Sound2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Sound2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound2dEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("sound2dEditorMenuChoice");
	rightWindow->getScreen("sound2dEditorMenuChoice")->createButton("play", fvec2(0.0f, POSITIONS(5)[0]), TEXT_SIZE("Play"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Play", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound2dEditorMenuChoice")->createButton("pause", fvec2(0.0f, POSITIONS(5)[1]), TEXT_SIZE("Pause"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Pause", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound2dEditorMenuChoice")->createButton("resume", fvec2(0.0f, POSITIONS(5)[2]), TEXT_SIZE("Resume"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Resume", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound2dEditorMenuChoice")->createButton("stop", fvec2(0.0f, POSITIONS(5)[3]), TEXT_SIZE("Stop"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Stop", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("sound2dEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(5)[4]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("empty");

	rightWindow->setActiveScreen("sound2dEditorMenuMain");
}

void Sound2dEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->deleteScreen("sound2dEditorMenuMain");
	rightWindow->deleteScreen("sound2dEditorMenuChoice");

	leftWindow->setActiveScreen("main");

	rightWindow->setActiveScreen("main");
}

void Sound2dEditor::_update()
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
		_updateSound2dCreating();
	}

	if(isLoaded())
	{
		_updateSound2dChoosing();
	}

	if(isLoaded())
	{
		_updateSound2dDeleting();
	}

	if(isLoaded())
	{
		_updateMiscellaneous();
	}
}