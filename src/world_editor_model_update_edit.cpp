#include "world_editor.hpp"

void WorldEditor::_updateModelEditing()
{
	if(_currentTemplateModelId.empty() && _currentTemplateQuadId.empty() && _currentTemplateSoundId.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		const auto rightWindow = _gui->getRightViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedModel)
		{
			_selectedModelId = "";
		}
		else
		{
			_dontResetSelectedModel = false;
		}

		for(const auto & [modelId, templateId] : _loadedModelIds)
		{
			const auto isHovered = (hoveredAabbId.substr(0, modelId.size()) == modelId);

			if(isHovered && _fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
			{
				_selectModel(modelId);

				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if(_selectedModelId != _activeModelId)
					{
						_activateModel(_selectedModelId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorEntityId(), "engine\\assets\\image\\diffuse_map\\cursor_pointing.tga");
			}
			else
			{
				if((modelId != _selectedModelId) && (modelId != _activeModelId))
				{
					_deselectModel(modelId);
				}
			}
		}

		if(!_fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			if(_fe3d->misc_isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeModelId.empty())
				{
					if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedModelId.empty()) || _fe3d->input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeModelId = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		if(_selectedModelId.empty())
		{
			_updateModelHighlighting(_activeModelId, _activeModelHighlightDirection);
		}
		else
		{
			_updateModelHighlighting(_selectedModelId, _selectedModelHighlightDirection);
		}

		if(!_activeModelId.empty())
		{
			auto screen = rightWindow->getScreen("modelPropertiesMenu");
			auto currentAnimationIds = _fe3d->model_getAnimationIds(_activeModelId);

			rightWindow->setActiveScreen("modelPropertiesMenu");

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
			{
				screen->getButton("position")->setHoverable(false);
				screen->getButton("rotation")->setHoverable(true);
				screen->getButton("size")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rotation")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("rotation")->setHoverable(false);
				screen->getButton("size")->setHoverable(true);
			}
			else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
			{
				screen->getButton("position")->setHoverable(true);
				screen->getButton("rotation")->setHoverable(true);
				screen->getButton("size")->setHoverable(false);
			}
			else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation")->isHovered())
			{
				if(currentAnimationIds.empty())
				{
					auto animationIds = _animation3dEditor->getLoadedAnimationIds();

					for(auto & id : animationIds)
					{
						id = id.substr(1);
					}

					_gui->getOverlay()->openChoiceForm("animationList", "Select Animation", fvec2(0.0f, 0.1f), animationIds);
				}
				else
				{
					_fe3d->model_stopAnimation(_activeModelId, currentAnimationIds[0]);

					for(const auto & partId : _fe3d->model_getPartIds(_activeModelId))
					{
						if(!partId.empty())
						{
							_fe3d->model_setPartPosition(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartRotationOrigin(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartRotation(_activeModelId, partId, fvec3(0.0f));
							_fe3d->model_setPartSize(_activeModelId, partId, fvec3(1.0f));
						}
					}
				}
			}
			else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("freeze")->isHovered())
			{
				_fe3d->model_setFrozen(_activeModelId, !_fe3d->model_isFrozen(_activeModelId));
			}
			else if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyPressed(InputType::KEY_DELETE))
			{
				if(!currentAnimationIds.empty())
				{
					_fe3d->model_stopAnimation(_activeModelId, currentAnimationIds[0]);
				}

				_fe3d->model_delete(_activeModelId);
				_loadedModelIds.erase(_activeModelId);
				rightWindow->setActiveScreen("main");
				_activeModelId = "";
				return;
			}

			const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();
			if(!selectedOptionId.empty())
			{
				if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
				{
					if(!currentAnimationIds.empty())
					{
						_fe3d->model_stopAnimation(_activeModelId, currentAnimationIds[0]);

						for(const auto & partId : _fe3d->model_getPartIds(_activeModelId))
						{
							if(!partId.empty())
							{
								_fe3d->model_setPartPosition(_activeModelId, partId, fvec3(0.0f));
								_fe3d->model_setPartRotationOrigin(_activeModelId, partId, fvec3(0.0f));
								_fe3d->model_setPartRotation(_activeModelId, partId, fvec3(0.0f));
								_fe3d->model_setPartSize(_activeModelId, partId, fvec3(1.0f));
							}
						}
					}

					_fe3d->model_startAnimation(_activeModelId, ("@" + selectedOptionId), -1);

					_gui->getOverlay()->closeChoiceForm();
				}
			}
			else if(_gui->getOverlay()->isChoiceFormCancelled())
			{
				_gui->getOverlay()->closeChoiceForm();
			}

			auto position = _fe3d->model_getBasePosition(_activeModelId);
			auto rotation = _fe3d->model_getBaseRotation(_activeModelId);
			auto size = _fe3d->model_getBaseSize(_activeModelId);

			if(!screen->getButton("position")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / MODEL_POSITION_DIVIDER));
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / MODEL_POSITION_DIVIDER));
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / MODEL_POSITION_DIVIDER));
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / MODEL_POSITION_DIVIDER));
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / MODEL_POSITION_DIVIDER));
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / MODEL_POSITION_DIVIDER));

				_fe3d->model_setBasePosition(_activeModelId, position);
			}
			else if(!screen->getButton("rotation")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", rotation.x, MODEL_ROTATION_SPEED);
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", rotation.x, -MODEL_ROTATION_SPEED);
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", rotation.y, MODEL_ROTATION_SPEED);
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", rotation.y, -MODEL_ROTATION_SPEED);
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", rotation.z, MODEL_ROTATION_SPEED);
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", rotation.z, -MODEL_ROTATION_SPEED);

				_fe3d->model_setBaseRotation(_activeModelId, rotation);
			}
			else if(!screen->getButton("size")->isHoverable())
			{
				_handleValueChanging("modelPropertiesMenu", "xPlus", "x", size.x, (_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "xMinus", "x", size.x, -(_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "yPlus", "y", size.y, (_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "yMinus", "y", size.y, -(_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "zPlus", "z", size.z, (_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);
				_handleValueChanging("modelPropertiesMenu", "zMinus", "z", size.z, -(_editorSpeed / MODEL_SIZE_DIVIDER), MODEL_SIZE_MULTIPLIER, 0.0f);

				_fe3d->model_setBaseSize(_activeModelId, size);
			}

			screen->getButton("animation")->setTextContent(currentAnimationIds.empty() ? "Start Animation" : "Stop Animation");
			screen->getButton("freeze")->setTextContent(_fe3d->model_isFrozen(_activeModelId) ? "Unfreeze" : "Freeze");
		}
	}
}