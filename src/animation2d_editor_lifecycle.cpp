#define TEXT_SIZE(text) fvec2((static_cast<float>(string(text).size()) * CW), CH)
#define POSITIONS(count) Mathematics::calculateDistributedPositions(count, CH, false)

#include "animation2d_editor.hpp"
#include "tools.hpp"

void Animation2dEditor::_load()
{
	_fe3d->quad3d_create(PREVIEW_QUAD3D_ID, true);
	_fe3d->quad3d_setPosition(PREVIEW_QUAD3D_ID, PREVIEW_QUAD3D_POSITION);
	_fe3d->quad3d_setVisible(PREVIEW_QUAD3D_ID, false);
	_fe3d->graphics_setAntiAliasingEnabled(true);
	_fe3d->camera_setYaw(CAMERA_YAW);

	_gui->getOverlay()->createTextField(ANIMATION2D_TITLE_ID, ANIMATION2D_TITLE_POSITION, ANIMATION2D_TITLE_SIZE, "", fvec3(1.0f), true);
}

void Animation2dEditor::_unload()
{
	for(const auto & aabb2dId : _loadedAnimation2dIds)
	{
		_fe3d->animation2d_delete(aabb2dId);
	}

	_fe3d->quad3d_delete(PREVIEW_QUAD3D_ID);
	_fe3d->graphics_setAntiAliasingEnabled(false);
	_fe3d->camera_reset();

	_gui->getOverlay()->deleteTextField(ANIMATION2D_TITLE_ID);

	_loadedAnimation2dIds.clear();
}

void Animation2dEditor::_loadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->createScreen("animation2dEditorMenuMain");
	rightWindow->getScreen("animation2dEditorMenuMain")->createButton("create", fvec2(0.0f, POSITIONS(4)[0]), TEXT_SIZE("Create Animation2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Create Animation2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation2dEditorMenuMain")->createButton("edit", fvec2(0.0f, POSITIONS(4)[1]), TEXT_SIZE("Edit Animation2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Edit Animation2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation2dEditorMenuMain")->createButton("delete", fvec2(0.0f, POSITIONS(4)[2]), TEXT_SIZE("Delete Animation2D"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Delete Animation2D", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation2dEditorMenuMain")->createButton("back", fvec2(0.0f, POSITIONS(4)[3]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	rightWindow->createScreen("animation2dEditorMenuChoice");
	rightWindow->getScreen("animation2dEditorMenuChoice")->createButton("preview", fvec2(0.0f, POSITIONS(6)[0]), TEXT_SIZE("Preview Texture"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Preview Texture", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation2dEditorMenuChoice")->createButton("rowCount", fvec2(0.0f, POSITIONS(6)[1]), TEXT_SIZE("Rows"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Rows", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation2dEditorMenuChoice")->createButton("columnCount", fvec2(0.0f, POSITIONS(6)[2]), TEXT_SIZE("Columns"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Columns", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation2dEditorMenuChoice")->createButton("interval", fvec2(0.0f, POSITIONS(6)[3]), TEXT_SIZE("Interval"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Interval", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation2dEditorMenuChoice")->createButton("start", fvec2(-0.5f, POSITIONS(6)[4]), TEXT_SIZE("Start"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Start", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation2dEditorMenuChoice")->createButton("stop", fvec2(0.5f, POSITIONS(6)[4]), TEXT_SIZE("Stop"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Stop", TEXT_COLOR, TEXT_HOVER_COLOR, true);
	rightWindow->getScreen("animation2dEditorMenuChoice")->createButton("back", fvec2(0.0f, POSITIONS(6)[5]), TEXT_SIZE("Go Back"), "", BUTTON_COLOR, BUTTON_HOVER_COLOR, "Go Back", TEXT_COLOR, TEXT_HOVER_COLOR, true);

	leftWindow->setActiveScreen("empty");

	rightWindow->setActiveScreen("animation2dEditorMenuMain");
}

void Animation2dEditor::_unloadGUI()
{
	const auto leftWindow = _gui->getLeftViewport()->getWindow("main");
	const auto rightWindow = _gui->getRightViewport()->getWindow("main");

	rightWindow->deleteScreen("animation2dEditorMenuMain");
	rightWindow->deleteScreen("animation2dEditorMenuChoice");

	leftWindow->setActiveScreen("main");

	rightWindow->setActiveScreen("main");
}

void Animation2dEditor::_update()
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
		_updateAnimation2dCreating();
	}

	if(isLoaded())
	{
		_updateAnimation2dChoosing();
	}

	if(isLoaded())
	{
		_updateAnimation2dDeleting();
	}

	if(isLoaded())
	{
		_updateImageChoosing();
	}

	if(isLoaded())
	{
		_updateMiscellaneous();
	}
}