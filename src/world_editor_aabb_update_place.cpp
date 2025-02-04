#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateAabbPlacing()
{
	if(!_currentEditorAabbId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->aabb_getBasePosition(_currentEditorAabbId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->aabb_setBasePosition(_currentEditorAabbId, fvec3(value, newPosition.y, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->aabb_setBasePosition(_currentEditorAabbId, fvec3(newPosition.x, value, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newAabbId = (_currentEditorAabbId.substr(1) + "_" + to_string(_aabbIdCounter));

				_aabbIdCounter++;

				_duplicator->copyEditorAabb(newAabbId, _currentEditorAabbId);

				_fe3d->aabb_setBasePosition(newAabbId, fvec3(newPosition.x, newPosition.y, value));

				_loadedAabbIds.push_back(newAabbId);

				sort(_loadedAabbIds.begin(), _loadedAabbIds.end());

				_fe3d->aabb_setVisible(_currentEditorAabbId, false);
				_fe3d->aabb_setRaycastResponsive(_currentEditorAabbId, false);
				_fe3d->aabb_setCollisionResponsive(_currentEditorAabbId, false);

				_currentEditorAabbId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->aabb_setVisible(_currentEditorAabbId, false);
				_fe3d->aabb_setRaycastResponsive(_currentEditorAabbId, false);
				_fe3d->aabb_setCollisionResponsive(_currentEditorAabbId, false);

				_currentEditorAabbId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				_fe3d->aabb_setVisible(_currentEditorAabbId, false);
				_fe3d->aabb_setRaycastResponsive(_currentEditorAabbId, false);
				_fe3d->aabb_setCollisionResponsive(_currentEditorAabbId, false);

				return;
			}

			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				_fe3d->aabb_setVisible(_currentEditorAabbId, false);
				_fe3d->aabb_setRaycastResponsive(_currentEditorAabbId, false);
				_fe3d->aabb_setCollisionResponsive(_currentEditorAabbId, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_fe3d->aabb_setVisible(_currentEditorAabbId, false);
				_fe3d->aabb_setRaycastResponsive(_currentEditorAabbId, false);
				_fe3d->aabb_setCollisionResponsive(_currentEditorAabbId, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				_fe3d->aabb_setVisible(_currentEditorAabbId, false);
				_fe3d->aabb_setRaycastResponsive(_currentEditorAabbId, false);
				_fe3d->aabb_setCollisionResponsive(_currentEditorAabbId, false);

				_currentEditorAabbId = "";

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + AABB_TERRAIN_OFFSET);

			_fe3d->aabb_setVisible(_currentEditorAabbId, true);
			_fe3d->aabb_setRaycastResponsive(_currentEditorAabbId, true);
			_fe3d->aabb_setCollisionResponsive(_currentEditorAabbId, true);
			_fe3d->aabb_setBasePosition(_currentEditorAabbId, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				const auto newAabbId = (_currentEditorAabbId.substr(1) + "_" + to_string(_aabbIdCounter));

				_aabbIdCounter++;

				_duplicator->copyEditorAabb(newAabbId, _currentEditorAabbId);

				_fe3d->aabb_setBasePosition(newAabbId, newPosition);

				_loadedAabbIds.push_back(newAabbId);

				sort(_loadedAabbIds.begin(), _loadedAabbIds.end());
			}
		}
	}
}