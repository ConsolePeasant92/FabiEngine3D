#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateSound3dPlacing()
{
	if(!_currentEditorSound3dId.empty())
	{
		if(_fe3d->terrain_getSelectedId().empty())
		{
			const auto newPosition = _fe3d->sound3d_getPosition(_currentEditorSound3dId);

			if((_gui->getOverlay()->getValueFormId() == "positionX") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->sound3d_setPosition(_currentEditorSound3dId, fvec3(value, newPosition.y, newPosition.z));
				_fe3d->model_setBasePosition(SPEAKER_ID, fvec3(value, newPosition.y, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionY") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);

				_fe3d->sound3d_setPosition(_currentEditorSound3dId, fvec3(newPosition.x, value, newPosition.z));
				_fe3d->model_setBasePosition(SPEAKER_ID, fvec3(newPosition.x, value, newPosition.z));
			}
			else if((_gui->getOverlay()->getValueFormId() == "positionZ") && _gui->getOverlay()->isValueFormConfirmed())
			{
				const auto content = _gui->getOverlay()->getValueFormContent();
				const auto value = (Tools::isInteger(content) ? static_cast<float>(Tools::parseInteger(content)) : 0.0f);
				const auto newSound3dId = (_currentEditorSound3dId.substr(1) + "_" + to_string(_sound3dIdCounter));
				const auto newModelId = ("@@speaker_" + newSound3dId);

				_sound3dIdCounter++;

				_duplicator->copyEditorSound3d(newSound3dId, _currentEditorSound3dId);

				_fe3d->sound3d_setPosition(newSound3dId, fvec3(newPosition.x, newPosition.y, value));
				_fe3d->sound3d_start(newSound3dId, -1, 0);

				_loadedSound3dIds.push_back(newSound3dId);

				sort(_loadedQuad3dIds.begin(), _loadedQuad3dIds.end());

				_fe3d->model_create(newModelId, SPEAKER_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, fvec3(newPosition.x, newPosition.y, value));
				_fe3d->model_setBaseSize(newModelId, SPEAKER_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_bindToParent(newModelId, newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, SPEAKER_AABB_SIZE);

				_fe3d->sound3d_stop(_currentEditorSound3dId, 0);
				_fe3d->model_setVisible(SPEAKER_ID, false);

				_currentEditorSound3dId = "";
			}

			if((_gui->getOverlay()->getValueFormId() != "positionX") && (_gui->getOverlay()->getValueFormId() != "positionY") && (_gui->getOverlay()->getValueFormId() != "positionZ"))
			{
				_fe3d->sound3d_stop(_currentEditorSound3dId, 0);
				_fe3d->model_setVisible(SPEAKER_ID, false);

				_currentEditorSound3dId = "";
			}
		}
		else
		{
			if(!_fe3d->raycast_isPointOnTerrainValid())
			{
				if(_fe3d->sound3d_isStarted(_currentEditorSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentEditorSound3dId, 0);
				}

				_fe3d->model_setVisible(SPEAKER_ID, false);

				return;
			}

			if(!Tools::isCursorInsideDisplay() || _gui->getOverlay()->isFocused())
			{
				if(_fe3d->sound3d_isStarted(_currentEditorSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentEditorSound3dId, 0);
				}

				_fe3d->model_setVisible(SPEAKER_ID, false);

				return;
			}

			if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				if(_fe3d->sound3d_isStarted(_currentEditorSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentEditorSound3dId, 0);
				}

				_fe3d->model_setVisible(SPEAKER_ID, false);

				return;
			}

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_MIDDLE))
			{
				if(_fe3d->sound3d_isStarted(_currentEditorSound3dId, 0))
				{
					_fe3d->sound3d_stop(_currentEditorSound3dId, 0);
				}

				_fe3d->model_setVisible(SPEAKER_ID, false);

				_currentEditorSound3dId = "";

				return;
			}

			const auto newPosition = (_fe3d->raycast_getPointOnTerrain() + SOUND3D_TERRAIN_OFFSET);

			if(!_fe3d->sound3d_isStarted(_currentEditorSound3dId, 0))
			{
				_fe3d->sound3d_start(_currentEditorSound3dId, -1, 0);
			}

			_fe3d->sound3d_setPosition(_currentEditorSound3dId, newPosition);
			_fe3d->model_setVisible(SPEAKER_ID, true);
			_fe3d->model_setBasePosition(SPEAKER_ID, newPosition);

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
			{
				const auto newSound3dId = (_currentEditorSound3dId.substr(1) + "_" + to_string(_sound3dIdCounter));
				const auto newModelId = ("@@speaker_" + newSound3dId);

				_sound3dIdCounter++;

				_duplicator->copyEditorSound3d(newSound3dId, _currentEditorSound3dId);

				_fe3d->sound3d_setPosition(newSound3dId, newPosition);
				_fe3d->sound3d_start(newSound3dId, -1, 0);

				_loadedSound3dIds.push_back(newSound3dId);

				sort(_loadedQuad3dIds.begin(), _loadedQuad3dIds.end());

				_fe3d->model_create(newModelId, SPEAKER_MESH_PATH);
				_fe3d->model_setBasePosition(newModelId, newPosition);
				_fe3d->model_setBaseSize(newModelId, SPEAKER_SIZE);
				_fe3d->model_setShadowed(newModelId, false);
				_fe3d->model_setReflected(newModelId, false);
				_fe3d->model_setRefracted(newModelId, false);
				_fe3d->model_setBright(newModelId, "", true);

				_fe3d->aabb_create(newModelId, true);
				_fe3d->aabb_setVisible(newModelId, false);
				_fe3d->aabb_bindToParent(newModelId, newModelId, AabbParentType::MODEL);
				_fe3d->aabb_setLocalSize(newModelId, SPEAKER_AABB_SIZE);
			}
		}
	}
}