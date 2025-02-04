#include "world_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void WorldEditor::_updateCamera()
{
	if(!_currentWorldId.empty())
	{
		if(_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT) && !_gui->getOverlay()->isFocused())
		{
			if(Tools::isCursorInsideDisplay() && !_fe3d->camera_isFirstPersonEnabled())
			{
				_fe3d->camera_setFirstPersonEnabled(true);
			}

			if(_fe3d->camera_isFirstPersonEnabled())
			{
				_fe3d->quad2d_setVisible(_fe3d->misc_getCursorId(), false);
			}
		}
		else
		{
			_fe3d->camera_setFirstPersonEnabled(false);

			if(Tools::isCursorInsideWindow())
			{
				_fe3d->quad2d_setVisible(_fe3d->misc_getCursorId(), true);
			}
		}

		if(!_gui->getOverlay()->isFocused())
		{
			const auto speed = (_editorSpeed / CAMERA_POSITION_SPEED_DIVIDER);
			const auto front = _fe3d->camera_getFrontWithoutPitch();
			const auto right = _fe3d->camera_getRight();

			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_W))
			{
				_fe3d->camera_move(fvec3((front.x * speed), 0.0, (front.z * speed)));
			}

			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_A))
			{
				_fe3d->camera_move(fvec3((right.x * -speed), 0.0, (right.z * -speed)));
			}

			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_S))
			{
				_fe3d->camera_move(fvec3((front.x * -speed), 0.0, (front.z * -speed)));
			}

			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_D))
			{
				_fe3d->camera_move(fvec3((right.x * speed), 0.0, (right.z * speed)));
			}

			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SPACEBAR))
			{
				_fe3d->camera_move(fvec3(0.0f, speed, 0.0f));
			}

			if(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SHIFT))
			{
				_fe3d->camera_move(fvec3(0.0f, -speed, 0.0f));
			}
		}
	}
	else
	{
		_fe3d->camera_setYaw(0.0f);
		_fe3d->camera_setPitch(0.0f);
	}
}

void WorldEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_G))
		{
			_isGridModeEnabled = !_isGridModeEnabled;
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
		{
			_isWireframeModeEnabled = !_isWireframeModeEnabled;
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_B))
		{
			_isAabbModeEnabled = !_isAabbModeEnabled;
		}
	}

	_fe3d->model_setVisible(GRID_ID, _isGridModeEnabled);

	_fe3d->model_setWireframed(GRID_ID, "", _isWireframeModeEnabled);

	if(!_fe3d->sky_getSelectedId().empty())
	{
		_fe3d->sky_setWireframed(_fe3d->sky_getSelectedId(), _isWireframeModeEnabled);
	}

	if(!_fe3d->terrain_getSelectedId().empty())
	{
		_fe3d->terrain_setWireframed(_fe3d->terrain_getSelectedId(), _isWireframeModeEnabled);
	}

	if(!_fe3d->water_getSelectedId().empty())
	{
		_fe3d->water_setWireframed(_fe3d->water_getSelectedId(), _isWireframeModeEnabled);
	}

	for(const auto & modelId : _loadedModelIds)
	{
		for(const auto & partId : _fe3d->model_getPartIds(modelId))
		{
			_fe3d->model_setWireframed(modelId, partId, _isWireframeModeEnabled);
		}

		if((modelId != _selectedModelId) && (modelId != _activeModelId))
		{
			for(const auto & childAabbId : _fe3d->model_getChildAabbIds(modelId))
			{
				_fe3d->aabb_setVisible(childAabbId, _isAabbModeEnabled);
			}
		}
	}

	for(const auto & quad3dId : _loadedQuad3dIds)
	{
		_fe3d->quad3d_setWireframed(quad3dId, _isWireframeModeEnabled);

		if((quad3dId != _selectedQuad3dId) && (quad3dId != _activeQuad3dId))
		{
			for(const auto & childAabbId : _fe3d->quad3d_getChildAabbIds(quad3dId))
			{
				_fe3d->aabb_setVisible(childAabbId, _isAabbModeEnabled);
			}
		}
	}

	for(const auto & text3dId : _loadedText3dIds)
	{
		_fe3d->text3d_setWireframed(text3dId, _isWireframeModeEnabled);

		if((text3dId != _selectedText3dId) && (text3dId != _activeText3dId))
		{
			for(const auto & childAabbId : _fe3d->text3d_getChildAabbIds(text3dId))
			{
				_fe3d->aabb_setVisible(childAabbId, _isAabbModeEnabled);
			}
		}
	}

	for(const auto & aabbId : _loadedAabbIds)
	{
		if((aabbId != _selectedAabbId) && (aabbId != _activeAabbId))
		{
			_fe3d->aabb_setVisible(aabbId, _isAabbModeEnabled);
		}
	}

	for(const auto & pointlightId : _loadedPointlightIds)
	{
		_fe3d->model_setWireframed("@@lamp_" + pointlightId, "", _isWireframeModeEnabled);

		if((pointlightId != _selectedPointlightId) && (pointlightId != _activePointlightId))
		{
			_fe3d->aabb_setVisible("@@lamp_" + pointlightId, _isAabbModeEnabled);
		}
	}

	for(const auto & spotlightId : _loadedSpotlightIds)
	{
		_fe3d->model_setWireframed("@@torch_" + spotlightId, "", _isWireframeModeEnabled);

		if((spotlightId != _selectedSpotlightId) && (spotlightId != _activeSpotlightId))
		{
			_fe3d->aabb_setVisible("@@torch_" + spotlightId, _isAabbModeEnabled);
		}
	}

	for(const auto & captorId : _loadedCaptorIds)
	{
		_fe3d->model_setWireframed("@@lens_" + captorId, "", _isWireframeModeEnabled);

		if((captorId != _selectedCaptorId) && (captorId != _activeCaptorId))
		{
			_fe3d->aabb_setVisible("@@lens_" + captorId, _isAabbModeEnabled);
		}
	}

	for(const auto & sound3dId : _loadedSound3dIds)
	{
		_fe3d->model_setWireframed("@@speaker_" + sound3dId, "", _isWireframeModeEnabled);

		if((sound3dId != _selectedSound3dId) && (sound3dId != _activeSound3dId))
		{
			_fe3d->aabb_setVisible("@@speaker_" + sound3dId, _isAabbModeEnabled);
		}
	}

	_fe3d->raycast_calculateCursorRay();

	if(!_fe3d->terrain_getSelectedId().empty())
	{
		_fe3d->raycast_calculateTerrainIntersection(Mathematics::calculateDistance(fvec3(_fe3d->terrain_getSize(_fe3d->terrain_getSelectedId())), fvec3(0.0f)), 0.1f);
		_fe3d->collision_calculateCameraWithTerrain(true, _editorSpeed);
	}

	_fe3d->raycast_calculateAabbsIntersection();
	_fe3d->collision_calculateCameraWithAabbs(true, true, true);

	const auto isSelected = (!_selectedModelId.empty() ||
							 !_selectedQuad3dId.empty() ||
							 !_selectedText3dId.empty() ||
							 !_selectedAabbId.empty() ||
							 !_selectedPointlightId.empty() ||
							 !_selectedSpotlightId.empty() ||
							 !_selectedCaptorId.empty() ||
							 !_selectedSound3dId.empty());

	const auto isActive = (!_activeModelId.empty() ||
						   !_activeQuad3dId.empty() ||
						   !_activeText3dId.empty() ||
						   !_activeAabbId.empty() ||
						   !_activePointlightId.empty() ||
						   !_activeSpotlightId.empty() ||
						   !_activeCaptorId.empty() ||
						   !_activeSound3dId.empty());

	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setVisible(isSelected);
	_gui->getOverlay()->getTextField(ACTIVE_TITLE_ID)->setVisible(isActive);
	_gui->getOverlay()->getTextField(SELECTED_TITLE_ID)->setPosition(fvec2(0.0f, (isActive ? 0.75f : 0.85f)));
	_gui->getOverlay()->getTextField(ACTIVE_TITLE_ID)->setPosition(fvec2(0.0f, 0.85f));
}

void WorldEditor::_updateWorldCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createWorld") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto worldId = _gui->getOverlay()->getValueFormContent();

		if(worldId.empty())
		{
			Logger::throwWarning("World ID cannot be empty");

			return;
		}

		if(any_of(worldId.begin(), worldId.end(), isspace))
		{
			Logger::throwWarning("World ID cannot contain any spaces");

			return;
		}

		if(any_of(worldId.begin(), worldId.end(), isupper))
		{
			Logger::throwWarning("World ID cannot contain any capitals");

			return;
		}

		if(worldId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
		{
			Logger::throwWarning("World ID cannot contain any specials");

			return;
		}

		const auto worldNames = _getWorldIds();

		if(find(worldNames.begin(), worldNames.end(), worldId) != worldNames.end())
		{
			Logger::throwWarning("World already exists");

			return;
		}

		_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);

		_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");

		_currentWorldId = worldId;
		_loadedWorldId = worldId;
	}
}

void WorldEditor::_updateWorldChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editWorld") || (_gui->getOverlay()->getChoiceFormId() == "deleteWorld"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentWorldId = selectedOptionId;

				if(_gui->getOverlay()->getChoiceFormId() == "deleteWorld")
				{
					_gui->getOverlay()->openAnswerForm("deleteWorld", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
				}
				else
				{
					if(loadWorldFromFile(_currentWorldId))
					{
						_fe3d->camera_setCursorSensitivity(CURSOR_SENSITIVITY);

						_gui->getRightViewport()->getWindow("main")->setActiveScreen("worldEditorMenuChoice");
					}
				}
			}
		}
	}
}

void WorldEditor::_updateWorldDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteWorld") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_deleteWorldFile(_currentWorldId);
			_currentWorldId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentWorldId = "";
		}
	}
}

void WorldEditor::_updateExceptionChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "selectException") && _gui->getOverlay()->isChoiceFormConfirmed())
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			_fe3d->captor_setExceptionId(_activeCaptorId, selectedOptionId);
		}
	}
}

void WorldEditor::_updateAnimation3dChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "selectAnimation3d") && _gui->getOverlay()->isChoiceFormConfirmed())
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			for(const auto & partId : _fe3d->animation3d_getPartIds(selectedOptionId))
			{
				if(!partId.empty() && !_fe3d->model_hasPart(_activeModelId, partId))
				{
					Logger::throwWarning("model does not have the required animation3D parts");

					return;
				}
			}

			if(!_fe3d->model_isAnimation3dStarted(_activeModelId, selectedOptionId))
			{
				_fe3d->model_startAnimation3d(_activeModelId, selectedOptionId, -1);
				_fe3d->model_pauseAnimation3d(_activeModelId, selectedOptionId);
			}
		}
	}
}

void WorldEditor::_updateAnimation2dChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "selectAnimation2d") && _gui->getOverlay()->isChoiceFormConfirmed())
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();
		const auto currentAnimation2dId = _fe3d->quad3d_getAnimation2dId(_activeQuad3dId);

		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
		{
			if(!currentAnimation2dId.empty())
			{
				_fe3d->quad3d_stopAnimation2d(_activeQuad3dId, currentAnimation2dId);
			}

			_fe3d->quad3d_startAnimation2d(_activeQuad3dId, selectedOptionId, -1);
		}
	}
}