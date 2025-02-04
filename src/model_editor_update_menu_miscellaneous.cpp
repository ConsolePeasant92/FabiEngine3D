#include "model_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void ModelEditor::_updateMiscellaneousMenu()
{
	const auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuMiscellaneous")
	{
		const auto isPartSelected = (!_fe3d->model_isMultiParted(_currentModelId) || !_currentPartId.empty());
		const auto isNoPartSelected = (!_fe3d->model_isMultiParted(_currentModelId) || _currentPartId.empty());
		const auto size = (isNoPartSelected ? _fe3d->model_getBaseSize(_currentModelId) : fvec3(0.0f));
		const auto opacity = (isPartSelected ? _fe3d->model_getOpacity(_currentModelId, _currentPartId) : 0.0f);
		const auto minAlpha = (isPartSelected ? _fe3d->model_getMinAlpha(_currentModelId, _currentPartId) : 0.0f);
		const auto isFaceCulled = (isPartSelected ? _fe3d->model_isFaceCulled(_currentModelId, _currentPartId) : false);
		const auto levelOfDetailId = (isNoPartSelected ? _fe3d->model_getLevelOfDetailId(_currentModelId) : "");
		const auto levelOfDetailDistance = (isNoPartSelected ? _fe3d->model_getLevelOfDetailDistance(_currentModelId) : 0.0f);
		const auto rotationOrder = (isNoPartSelected ? _fe3d->model_getRotationOrder(_currentModelId) : DirectionOrderType::XYZ);

		if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

			return;
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->openValueForm("sizeX", "X", (size.x * SIZE_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("sizeY", "Y", (size.y * SIZE_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			_gui->getOverlay()->openValueForm("sizeZ", "Z", (size.z * SIZE_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("opacity")->isHovered())
		{
			if(_currentPartId.empty())
			{
				_gui->getOverlay()->openValueForm("opacity", "Opacity", (opacity * OPACITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			}
			else
			{
				_gui->getOverlay()->openValueForm("opacity", "Opacity", (_originalPartOpacity * OPACITY_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("minAlpha")->isHovered())
		{
			_gui->getOverlay()->openValueForm("minAlpha", "Min Alpha", (minAlpha * MIN_ALPHA_FACTOR), VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("isFaceCulled")->isHovered())
		{
			_fe3d->model_setFaceCulled(_currentModelId, _currentPartId, !isFaceCulled);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("levelOfDetailId")->isHovered())
		{
			if(levelOfDetailId.empty())
			{
				_gui->getOverlay()->openValueForm("levelOfDetailId", "LOD Model ID", "", VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
			}
			else
			{
				_gui->getOverlay()->openValueForm("levelOfDetailId", "LOD Model ID", levelOfDetailId.substr(1), VALUE_FORM_POSITION, VALUE_FORM_SIZE, true, true, true);
			}
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("levelOfDetailDistance")->isHovered())
		{
			_gui->getOverlay()->openValueForm("levelOfDetailDistance", "LOD Distance", levelOfDetailDistance, VALUE_FORM_POSITION, VALUE_FORM_SIZE, false, true, false);
		}
		else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("rotationOrder")->isHovered())
		{
			switch(rotationOrder)
			{
				case DirectionOrderType::XYZ:
				{
					_fe3d->model_setRotationOrder(_currentModelId, DirectionOrderType::XZY);

					break;
				}
				case DirectionOrderType::XZY:
				{
					_fe3d->model_setRotationOrder(_currentModelId, DirectionOrderType::YXZ);

					break;
				}
				case DirectionOrderType::YXZ:
				{
					_fe3d->model_setRotationOrder(_currentModelId, DirectionOrderType::YZX);

					break;
				}
				case DirectionOrderType::YZX:
				{
					_fe3d->model_setRotationOrder(_currentModelId, DirectionOrderType::ZXY);

					break;
				}
				case DirectionOrderType::ZXY:
				{
					_fe3d->model_setRotationOrder(_currentModelId, DirectionOrderType::ZYX);

					break;
				}
				case DirectionOrderType::ZYX:
				{
					_fe3d->model_setRotationOrder(_currentModelId, DirectionOrderType::XYZ);

					break;
				}
			}
		}

		if((_gui->getOverlay()->getValueFormId() == "sizeX") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setBaseSize(_currentModelId, fvec3((value / SIZE_FACTOR), size.y, size.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "sizeY") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setBaseSize(_currentModelId, fvec3(size.x, (value / SIZE_FACTOR), size.z));
		}
		else if((_gui->getOverlay()->getValueFormId() == "sizeZ") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setBaseSize(_currentModelId, fvec3(size.x, size.y, (value / SIZE_FACTOR)));
		}
		else if((_gui->getOverlay()->getValueFormId() == "opacity") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			if(_currentPartId.empty())
			{
				_fe3d->model_setOpacity(_currentModelId, _currentPartId, (value / OPACITY_FACTOR));
			}
			else
			{
				_originalPartOpacity = opacity;
			}
		}
		else if((_gui->getOverlay()->getValueFormId() == "minAlpha") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setMinAlpha(_currentModelId, _currentPartId, (value / MIN_ALPHA_FACTOR));
		}
		else if((_gui->getOverlay()->getValueFormId() == "levelOfDetailId") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto value = _gui->getOverlay()->getValueFormContent();

			if(value.empty())
			{
				_fe3d->model_setLevelOfDetailId(_currentModelId, "");
			}
			else if(find(_loadedModelIds.begin(), _loadedModelIds.end(), ("@" + value)) == _loadedModelIds.end())
			{
				Logger::throwWarning("LOD model does not exist");
			}
			else
			{
				_fe3d->model_setLevelOfDetailId(_currentModelId, ("@" + value));
			}
		}
		else if((_gui->getOverlay()->getValueFormId() == "levelOfDetailDistance") && _gui->getOverlay()->isValueFormConfirmed())
		{
			const auto content = _gui->getOverlay()->getValueFormContent();
			const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

			_fe3d->model_setLevelOfDetailDistance(_currentModelId, value);
		}

		screen->getButton("isFaceCulled")->setTextContent(isFaceCulled ? "Culling: ON" : "Culling: OFF");

		switch(rotationOrder)
		{
			case DirectionOrderType::XYZ:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: X Y Z");

				break;
			}
			case DirectionOrderType::XZY:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: X Z Y");

				break;
			}
			case DirectionOrderType::YXZ:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: Y X Z");

				break;
			}
			case DirectionOrderType::YZX:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: Y Z X");

				break;
			}
			case DirectionOrderType::ZXY:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: Z X Y");

				break;
			}
			case DirectionOrderType::ZYX:
			{
				screen->getButton("rotationOrder")->setTextContent("Rotation: Z Y X");

				break;
			}
		}

		screen->getButton("size")->setHoverable(isNoPartSelected, true);
		screen->getButton("opacity")->setHoverable(isPartSelected, true);
		screen->getButton("minAlpha")->setHoverable(isPartSelected, true);
		screen->getButton("isFaceCulled")->setHoverable(isPartSelected, true);
		screen->getButton("levelOfDetailId")->setHoverable(isNoPartSelected, true);
		screen->getButton("levelOfDetailDistance")->setHoverable(isNoPartSelected, true);
		screen->getButton("rotationOrder")->setHoverable(isNoPartSelected, true);
	}
}