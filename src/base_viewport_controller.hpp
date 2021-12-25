#pragma once

#include "fe3d.hpp"
#include "gui_manager.hpp"

class BaseViewportController
{
public:
	BaseViewportController(FabiEngine3D& fe3d, GuiManager& gui);

	virtual void initialize() = 0;
	virtual void update() = 0;

	static const vector<float> calculateButtonPositions(unsigned int buttonCount, float buttonHeight);

	static const float calculateTextWidth(const string& text, float charWidth);

protected:
	FabiEngine3D& _fe3d;
	GuiManager& _gui;
};