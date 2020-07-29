#include "scene_editor.hpp"

#include <algorithm>

void SceneEditor::_updateLightScreen()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuLighting")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuLighting");

			// GUI management
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("ambient")->isHovered()) // Ambient light button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuLightingAmbient");
				}
				else if (screen->getButton("directional")->isHovered()) // Directional light button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuLightingDirectional");
				}
				else if (screen->getButton("point")->isHovered()) // Point light button
				{
					_leftWindow->setActiveScreen("sceneEditorMenuLightingPoint");
				}
				else if (screen->getButton("back")->isHovered()) // Back button
				{
					_leftWindow->setActiveScreen("sceneEditorMenu");
				}
			}
		}
	}
}

void SceneEditor::_updateAmbientLightScreen()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuLightingAmbient")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuLightingAmbient");

			// GUI management
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("color")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("ambientColorG", "G(0-255)", _ambientLightColor.g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
					_gui->getGlobalScreen()->addValueForm("ambientColorR", "R(0-255)", _ambientLightColor.r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
					_gui->getGlobalScreen()->addValueForm("ambientColorB", "B(0-255)", _ambientLightColor.b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("intensity")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("ambientIntensity", "Ambient intensity", _ambientLightIntensity * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuLighting");
				}
			}

			// Ambient value conversion
			if (_gui->getGlobalScreen()->checkValueForm("ambientIntensity", _ambientLightIntensity))
			{
				_ambientLightIntensity /= 100.0f;
			}

			// Color R values conversion
			if (_gui->getGlobalScreen()->checkValueForm("ambientColorR", _ambientLightColor.r))
			{
				_ambientLightColor.r = std::clamp(_ambientLightColor.r / 255.0f, 0.0f, 1.0f);
			}

			// Color G values conversion
			if (_gui->getGlobalScreen()->checkValueForm("ambientColorG", _ambientLightColor.g))
			{
				_ambientLightColor.g = std::clamp(_ambientLightColor.g / 255.0f, 0.0f, 1.0f);
			}

			// Color B values conversion
			if (_gui->getGlobalScreen()->checkValueForm("ambientColorB", _ambientLightColor.b))
			{
				_ambientLightColor.b = std::clamp(_ambientLightColor.b / 255.0f, 0.0f, 1.0f);
			}

			// Update ambient lighting
			_fe3d.gfx_enableAmbientLighting(_ambientLightColor, _ambientLightIntensity);
		}
	}
}

void SceneEditor::_updateDirectionalLightScreen()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuLightingDirectional")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuLightingDirectional");

			// GUI management
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("color")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("directionalColorG", "G(0-255)", _directionalLightColor.g * 255.0f, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
					_gui->getGlobalScreen()->addValueForm("directionalColorR", "R(0-255)", _directionalLightColor.r * 255.0f, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
					_gui->getGlobalScreen()->addValueForm("directionalColorB", "B(0-255)", _directionalLightColor.b * 255.0f, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("position")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("positionY", "Y", _directionalLightPosition.y, vec2(0.0f, 0.0f), vec2(0.2f, 0.1f));
					_gui->getGlobalScreen()->addValueForm("positionX", "X", _directionalLightPosition.x, vec2(-0.25f, 0.0f), vec2(0.2f, 0.1f));
					_gui->getGlobalScreen()->addValueForm("positionZ", "Z", _directionalLightPosition.z, vec2(0.25f, 0.0f), vec2(0.2f, 0.1f));
				}
				else if (screen->getButton("intensity")->isHovered())
				{
					_gui->getGlobalScreen()->addValueForm("directionalIntensity", "Directional intensity", _directionalLightIntensity * 100.0f, vec2(0.0f), vec2(0.3f, 0.1f));
				}
				else if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuLighting");
				}
			}

			// Directional value conversion
			if (_gui->getGlobalScreen()->checkValueForm("directionalIntensity", _directionalLightIntensity))
			{
				_directionalLightIntensity /= 100.0f;
			}

			// Color R values conversion
			if (_gui->getGlobalScreen()->checkValueForm("directionalColorR", _directionalLightColor.r))
			{
				_directionalLightColor.r = std::clamp(_directionalLightColor.r / 255.0f, 0.0f, 1.0f);
			}

			// Color G values conversion
			if (_gui->getGlobalScreen()->checkValueForm("directionalColorG", _directionalLightColor.g))
			{
				_directionalLightColor.g = std::clamp(_directionalLightColor.g / 255.0f, 0.0f, 1.0f);
			}

			// Color B values conversion
			if (_gui->getGlobalScreen()->checkValueForm("directionalColorB", _directionalLightColor.b))
			{
				_directionalLightColor.b = std::clamp(_directionalLightColor.b / 255.0f, 0.0f, 1.0f);
			}

			// Get position values
			_gui->getGlobalScreen()->checkValueForm("positionX", _directionalLightPosition.x);
			_gui->getGlobalScreen()->checkValueForm("positionY", _directionalLightPosition.y);
			_gui->getGlobalScreen()->checkValueForm("positionZ", _directionalLightPosition.z);

			// Update directional lighting
			_fe3d.gfx_enableDirectionalLighting(_directionalLightPosition, _directionalLightColor, _directionalLightIntensity);
		}
	}
}

void SceneEditor::_updatePointLightScreen()
{
	if (_isLoaded)
	{
		if (_leftWindow->getActiveScreen()->getID() == "sceneEditorMenuLightingPoint")
		{
			auto screen = _leftWindow->getScreen("sceneEditorMenuLightingPoint");

			// GUI management
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (screen->getButton("add")->isHovered())
				{
					_isPlacingPointlight = true;
				}
				else if (screen->getButton("back")->isHovered())
				{
					_leftWindow->setActiveScreen("sceneEditorMenuLighting");
					_isPlacingPointlight = false;
				}
			}
		}
	}
}