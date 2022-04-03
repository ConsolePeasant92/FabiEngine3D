#include "water_editor.hpp"

void WaterEditor::_updateMiscellaneousMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "waterEditorMenuMiscellaneous")
	{
		auto size = _fe3d->water_getSize(_currentWaterId);
		auto rippleSpeed = _fe3d->water_getRippleSpeed(_currentWaterId);
		auto waveSpeed = _fe3d->water_getWaveSpeed(_currentWaterId);
		auto waveHeight = _fe3d->water_getWaveHeight(_currentWaterId);
		auto maxDepth = _fe3d->water_getMaxDepth(_currentWaterId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("waterEditorMenuChoice");
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("size", "Size", size, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("waveHeight")->isHovered())
		{
			_gui->getOverlay()->openValueForm("waveHeight", "Wave Height", (waveHeight * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("maxDepth")->isHovered())
		{
			_gui->getOverlay()->openValueForm("maxDepth", "Max Depth", maxDepth, fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rippleSpeed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("rippleSpeedX", "X", (rippleSpeed.x * 100000.0f), fvec2(-0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("rippleSpeedY", "Y", (rippleSpeed.y * 100000.0f), fvec2(0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("waveSpeed")->isHovered())
		{
			_gui->getOverlay()->openValueForm("waveSpeedX", "X", (waveSpeed.x * 100000.0f), fvec2(-0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->openValueForm("waveSpeedY", "Y", (waveSpeed.y * 100000.0f), fvec2(0.15f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("size", size, {0.0f}))
		{
			_fe3d->water_setSize(_currentWaterId, size);
		}
		if(_gui->getOverlay()->checkValueForm("rippleSpeedX", rippleSpeed.x))
		{
			rippleSpeed.x /= 100000.0f;
			_fe3d->water_setRippleSpeed(_currentWaterId, rippleSpeed);
		}
		if(_gui->getOverlay()->checkValueForm("rippleSpeedY", rippleSpeed.y))
		{
			rippleSpeed.y /= 100000.0f;
			_fe3d->water_setRippleSpeed(_currentWaterId, rippleSpeed);
		}
		if(_gui->getOverlay()->checkValueForm("waveSpeedX", waveSpeed.x))
		{
			waveSpeed.x /= 100000.0f;
			_fe3d->water_setWaveSpeed(_currentWaterId, waveSpeed);
		}
		if(_gui->getOverlay()->checkValueForm("waveSpeedY", waveSpeed.y))
		{
			waveSpeed.y /= 100000.0f;
			_fe3d->water_setWaveSpeed(_currentWaterId, waveSpeed);
		}
		if(_gui->getOverlay()->checkValueForm("waveHeight", waveHeight))
		{
			waveHeight /= 100.0f;
			_fe3d->water_setWaveHeight(_currentWaterId, waveHeight);
		}
		if(_gui->getOverlay()->checkValueForm("maxDepth", maxDepth))
		{
			_fe3d->water_setMaxDepth(_currentWaterId, maxDepth);
		}
	}
}