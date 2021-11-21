#include "sky_editor.hpp"

void SkyEditor::_updateMiscellaneousMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "skyEditorMenuMiscellaneous")
	{
		// Temporary values
		float rotation = _fe3d.sky_getRotation(_currentSkyID);
		float lightness = _fe3d.sky_getLightness(_currentSkyID);
		fvec3 color = _fe3d.sky_getColor(_currentSkyID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("rotation", "Rotation", rotation * 1000.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("lightness", "Lightness", (lightness * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("colorR", "R", color.r * 255.0f, fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorG", "G", color.g * 255.0f, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui.getGlobalScreen()->createValueForm("colorB", "B", color.b * 255.0f, fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		// Update value forms
		if(_gui.getGlobalScreen()->checkValueForm("rotation", rotation))
		{
			_fe3d.sky_setRotation(_currentSkyID, rotation);
		}
		if(_gui.getGlobalScreen()->checkValueForm("lightness", lightness))
		{
			lightness /= 100.0f;
			_fe3d.sky_setLightness(_currentSkyID, lightness);
		}
		if(_gui.getGlobalScreen()->checkValueForm("colorR", color.r))
		{
			color.r /= 255.0f;
			_fe3d.sky_setColor(_currentSkyID, color);
		}
		if(_gui.getGlobalScreen()->checkValueForm("colorG", color.g))
		{
			color.g /= 255.0f;
			_fe3d.sky_setColor(_currentSkyID, color);
		}
		if(_gui.getGlobalScreen()->checkValueForm("colorB", color.b))
		{
			color.b /= 255.0f;
			_fe3d.sky_setColor(_currentSkyID, color);
		}
	}
}