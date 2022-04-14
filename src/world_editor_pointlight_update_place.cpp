#include "world_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void WorldEditor::_updatePointlightPlacing()
{
	if(_isPlacingPointlight)
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->pointlight_getPosition(TEMPLATE_POINTLIGHT_ID);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->pointlight_setPosition(TEMPLATE_POINTLIGHT_ID, fvec3(content, newPosition.y, newPosition.z));
				_fe3d->model_setBasePosition(TEMPLATE_LAMP_ID, fvec3(content, newPosition.y, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));

				_fe3d->pointlight_setPosition(TEMPLATE_POINTLIGHT_ID, fvec3(newPosition.x, content, newPosition.z));
				_fe3d->model_setBasePosition(TEMPLATE_LAMP_ID, fvec3(newPosition.x, content, newPosition.z));
			}
			if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = static_cast<float>(Tools::parseInteger(_gui->getOverlay()->getValueFormContent()));
				const auto newId = ("pointlight_" + to_string(_idCounter));
				const auto newModelId = ("@@lamp_" + newId);

				_idCounter++;

				if(_fe3d->pointlight_getIds().size() == _fe3d->pointlight_getMaxEntityCount())
				{
					Logger::throwWarning("pointlight maximum is reached");
					return;
				}

				_loadedPointlightIds.push_back(newId);

				_fe3d->pointlight_create(newId);
				_fe3d->pointlight_setPosition(newId, fvec3(newPosition.x, newPosition.y, content));
				_fe3d->pointlight_setRadius(newId, fvec3(DEFAULT_POINTLIGHT_RADIUS));
				_fe3d->pointlight_setIntensity(newId, DEFAULT_POINTLIGHT_INTENSITY);

				_fe3d->model_create(newModelId, "engine\\assets\\mesh\\lamp.obj");
				_fe3d->model_setBasePosition(newModelId, fvec3(newPosition.x, newPosition.y, content));
				_fe3d->model_setBaseSize(newModelId, DEFAULT_LAMP_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_LAMP_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);

				_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);

				_isPlacingPointlight = false;
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);

				_isPlacingPointlight = false;
			}
		}
		else
		{
			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
				return;
			}

			if(_fe3d->input_isMouseHeld(ButtonType::BUTTON_RIGHT))
			{
				_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
				return;
			}

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_MIDDLE))
			{
				_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
				_isPlacingPointlight = false;
				return;
			}

			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, false);
				_fe3d->model_setVisible(TEMPLATE_LAMP_ID, false);
				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + POINTLIGHT_TERRAIN_OFFSET);
			_fe3d->pointlight_setVisible(TEMPLATE_POINTLIGHT_ID, true);
			_fe3d->pointlight_setPosition(TEMPLATE_POINTLIGHT_ID, newPosition);
			_fe3d->model_setVisible(TEMPLATE_LAMP_ID, true);
			_fe3d->model_setBasePosition(TEMPLATE_LAMP_ID, newPosition);

			if(_fe3d->input_isMousePressed(ButtonType::BUTTON_LEFT))
			{
				auto newId = ("pointlight_" + to_string(_idCounter));
				auto newModelId = ("@@lamp_" + newId);

				_idCounter++;

				if(_fe3d->pointlight_getIds().size() == _fe3d->pointlight_getMaxEntityCount())
				{
					Logger::throwWarning("pointlight maximum is reached");
					return;
				}

				_loadedPointlightIds.push_back(newId);

				_fe3d->pointlight_create(newId);
				_fe3d->pointlight_setPosition(newId, newPosition);
				_fe3d->pointlight_setRadius(newId, fvec3(DEFAULT_POINTLIGHT_RADIUS));
				_fe3d->pointlight_setIntensity(newId, DEFAULT_POINTLIGHT_INTENSITY);

				_fe3d->model_create(newModelId, "engine\\assets\\mesh\\lamp.obj");
				_fe3d->model_setBasePosition(newModelId, newPosition);
				_fe3d->model_setBaseSize(newModelId, DEFAULT_LAMP_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setParentId(newModelId, newModelId);
				_fe3d->aabb_setParentType(newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, DEFAULT_LAMP_AABB_SIZE);
				_fe3d->aabb_setCollisionResponsive(newModelId, false);
			}
		}
	}
}