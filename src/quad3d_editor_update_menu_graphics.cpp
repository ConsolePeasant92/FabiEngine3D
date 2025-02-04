#include "quad3d_editor.hpp"
#include "tools.hpp"

void Quad3dEditor::_updateGraphicsMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "quad3dEditorMenuGraphics")
	{
		const auto emissionIntensity = _fe3d->quad3d_getEmissionIntensity(_currentQuad3dId);
		const auto lightness = _fe3d->quad3d_getLightness(_currentQuad3dId);
		const auto isBright = _fe3d->quad3d_isBright(_currentQuad3dId);
		const auto isReflected = _fe3d->quad3d_isReflected(_currentQuad3dId);
		const auto isRefracted = _fe3d->quad3d_isRefracted(_currentQuad3dId);
		const auto isShadowed = _fe3d->quad3d_isShadowed(_currentQuad3dId);
		const auto color = _fe3d->quad3d_getColor(_currentQuad3dId);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("color")->isHovered())
		{
			_gui->getOverlay()->openValueForm("colorR", "Red", (color.r * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorG", "Green", (color.g * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("colorB", "Blue", (color.b * COLOR_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("lightness")->isHovered())
		{
			_gui->getOverlay()->openValueForm("lightness", "Lightness", (lightness * LIGHTNESS_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("emissionIntensity")->isHovered())
		{
			_gui->getOverlay()->openValueForm("emissionIntensity", "Emission Intensity", (emissionIntensity * EMISSION_INTENSITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isBright")->isHovered())
		{
			_fe3d->quad3d_setBright(_currentQuad3dId, !isBright);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isShadowed")->isHovered())
		{
			_fe3d->quad3d_setShadowed(_currentQuad3dId, !isShadowed);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isReflected")->isHovered())
		{
			_fe3d->quad3d_setReflected(_currentQuad3dId, !isReflected);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isRefracted")->isHovered())
		{
			_fe3d->quad3d_setRefracted(_currentQuad3dId, !isRefracted);
		}

		if((_gui->getOverlay()->getValueFormId() == "colorR") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad3d_setColor(_currentQuad3dId, fvec3((value / COLOR_FACTOR), color.g, color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorG") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad3d_setColor(_currentQuad3dId, fvec3(color.r, (value / COLOR_FACTOR), color.b));
		}
		else if((_gui->getOverlay()->getValueFormId() == "colorB") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad3d_setColor(_currentQuad3dId, fvec3(color.r, color.g, (value / COLOR_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "lightness") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad3d_setLightness(_currentQuad3dId, (value / LIGHTNESS_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "emissionIntensity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->quad3d_setEmissionIntensity(_currentQuad3dId, (value / EMISSION_INTENSITY_FACTOR));
		}

		screen->getButton("isBright")->setTextContent(isBright ? "Bright: ON" : "Bright: OFF");
		screen->getButton("isReflected")->setTextContent(isReflected ? "Reflected: ON" : "Reflected: OFF");
		screen->getButton("isRefracted")->setTextContent(isRefracted ? "Refracted: ON" : "Refracted: OFF");
		screen->getButton("isShadowed")->setTextContent(isShadowed ? "Shadowed: ON" : "Shadowed: OFF");
	}
}