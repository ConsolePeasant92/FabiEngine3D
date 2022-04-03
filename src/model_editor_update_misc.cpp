#include "model_editor.hpp"
#include "tools.hpp"
#include "logger.hpp"

void ModelEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		auto scrollOffset = _fe3d->input_getMouseWheelY();
		auto cameraDistance = _fe3d->camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d->camera_setThirdPersonDistance(cameraDistance);

		auto cameraLookat = _fe3d->camera_getThirdPersonLookat();
		if(_fe3d->input_isKeyDown(InputType::KEY_SPACE))
		{
			cameraLookat.y += CAMERA_LOOKAT_SPEED;
		}
		if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT) || _fe3d->input_isKeyDown(InputType::KEY_RSHIFT))
		{
			cameraLookat.y -= CAMERA_LOOKAT_SPEED;
		}
		cameraLookat.y = max(-GRID_Y_OFFSET, cameraLookat.y);
		_fe3d->camera_setThirdPersonLookat(cameraLookat);

		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorEntityId(), false);

		const auto distance = _fe3d->camera_getThirdPersonDistance();
		_fe3d->graphics_setShadowPositionOffset(fvec3(cameraLookat + fvec3(distance)));
		_fe3d->graphics_setShadowLookatOffset(cameraLookat);
		_fe3d->graphics_setShadowSize(distance * 2.0f);
	}

	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			_fe3d->camera_setThirdPersonEnabled(!_fe3d->camera_isThirdPersonEnabled());
		}
	}

	if(_gui->getOverlay()->isFocused())
	{
		_fe3d->camera_setThirdPersonEnabled(false);
	}
}

void ModelEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyPressed(InputType::KEY_R))
		{
			_fe3d->model_setVisible("@@box", !_fe3d->model_isVisible("@@box"));
		}

		if(!_currentModelId.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				for(const auto & partId : _fe3d->model_getPartIds(_currentModelId))
				{
					_fe3d->model_setWireframed(_currentModelId, partId, !_fe3d->model_isWireframed(_currentModelId, partId));
				}
			}
		}
	}

	if(!_currentModelId.empty())
	{
		const auto partId = (_hoveredPartId.empty() ? _currentPartId : _hoveredPartId);

		if(partId.empty())
		{
			_selectedPartHighlightDirection = 1;
		}
		else
		{
			const auto opacity = _fe3d->model_getOpacity(_currentModelId, partId);

			if(opacity == 0.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			if(opacity == 1.0f)
			{
				_selectedPartHighlightDirection *= -1;
			}

			const float speed = (PART_HIGHLIGHT_SPEED * static_cast<float>(_selectedPartHighlightDirection));
			_fe3d->model_setOpacity(_currentModelId, partId, (opacity + speed));
		}
	}
}

void ModelEditor::_updateModelCreating()
{
	if(_isCreatingModel)
	{
		string newModelId;

		if(_gui->getOverlay()->getValueFormId() == "modelCreate")
		{
			if(_gui->getOverlay()->isValueFormConfirmed())
			{
				if(newModelId.empty())
				{
					Logger::throwWarning("Model ID cannot be empty");
					return;
				}

				if(any_of(newModelId.begin(), newModelId.end(), isspace))
				{
					Logger::throwWarning("Model ID cannot contain any spaces");
					return;
				}

				if(any_of(newModelId.begin(), newModelId.end(), isupper))
				{
					Logger::throwWarning("Model ID cannot contain any capitals");
					return;
				}

				newModelId = ("@" + newModelId);

				if(find(_loadedEntityIds.begin(), _loadedEntityIds.end(), newModelId) != _loadedEntityIds.end())
				{
					Logger::throwWarning("Model already exists");
					return;
				}

				if(getCurrentProjectId().empty())
				{
					abort();
				}

				const auto rootPath = Tools::getRootDirectoryPath();
				const auto targetDirectoryPath = ("projects\\" + getCurrentProjectId() + "\\assets\\mesh\\");

				if(!Tools::isDirectoryExisting(rootPath + targetDirectoryPath))
				{
					Logger::throwWarning("Directory `" + targetDirectoryPath + "` does not exist");
					_isCreatingModel = false;
					return;
				}

				const auto filePath = Tools::chooseExplorerFile((rootPath + targetDirectoryPath), "OBJ");
				if(filePath.empty())
				{
					_isCreatingModel = false;
					return;
				}

				if((filePath.size() > (rootPath.size() + targetDirectoryPath.size())) && (filePath.substr(rootPath.size(), targetDirectoryPath.size()) != targetDirectoryPath))
				{
					Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`");
					_isCreatingModel = false;
					return;
				}

				const string finalFilePath = filePath.substr(rootPath.size());
				_fe3d->misc_clearMeshCache(finalFilePath);

				_fe3d->model_create(newModelId, finalFilePath);

				if(_fe3d->model_isExisting(newModelId))
				{
					_currentModelId = newModelId;
					_loadedEntityIds.push_back(newModelId);
					sort(_loadedEntityIds.begin(), _loadedEntityIds.end());

					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
					_gui->getOverlay()->getTextField("modelId")->setTextContent("Model: " + newModelId.substr(1));
					_gui->getOverlay()->getTextField("modelId")->setVisible(true);
					_isCreatingModel = false;
				}
			}
			if(_gui->getOverlay()->isValueFormCancelled())
			{
				_gui->getOverlay()->closeValueForm();
			}
		}
	}
}

void ModelEditor::_updateModelChoosing()
{
	if(_isChoosingModel)
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_hoveredModelId.empty())
			{
				_hoveredModelId = ("@" + selectedOptionId);
				_fe3d->model_setVisible(_hoveredModelId, true);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentModelId = _hoveredModelId;
				_hoveredModelId = "";
				_isChoosingModel = false;

				if(_isDeletingModel)
				{
					_gui->getOverlay()->openAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");

					_gui->getOverlay()->getTextField("modelId")->setTextContent("Model: " + _currentModelId.substr(1));
					_gui->getOverlay()->getTextField("modelId")->setVisible(true);
				}

				_gui->getOverlay()->closeChoiceForm();
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled())
		{
			_isChoosingModel = false;
			_isDeletingModel = false;

			_gui->getOverlay()->closeChoiceForm();
		}
		else
		{
			if(!_hoveredModelId.empty())
			{
				_fe3d->model_setVisible(_hoveredModelId, false);
				_hoveredModelId = "";
			}
		}
	}
}

void ModelEditor::_updateModelDeleting()
{
	if(_isDeletingModel && !_isChoosingModel)
	{
		if(_gui->getOverlay()->isAnswerFormAccepted())
		{
			_fe3d->model_delete(_currentModelId);

			_loadedEntityIds.erase(remove(_loadedEntityIds.begin(), _loadedEntityIds.end(), _currentModelId), _loadedEntityIds.end());
			_currentModelId = "";
			_isDeletingModel = false;

			_gui->getOverlay()->closeAnswerForm();
		}
		if(_gui->getOverlay()->isAnswerFormDenied())
		{
			_fe3d->model_setVisible(_currentModelId, false);

			_currentModelId = "";
			_isDeletingModel = false;

			_gui->getOverlay()->closeAnswerForm();
		}
	}
}

void ModelEditor::_updatePartChoosing()
{
	if(_isChoosingPart)
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(!selectedOptionId.empty())
		{
			if(_hoveredPartId.empty())
			{
				_hoveredPartId = selectedOptionId;
				_originalPartOpacity = _fe3d->model_getOpacity(_currentModelId, _hoveredPartId);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentPartId = _hoveredPartId;
				_hoveredPartId = "";
				_isChoosingPart = false;

				_gui->getOverlay()->closeChoiceForm();
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled())
		{
			_isChoosingPart = false;

			_gui->getOverlay()->closeChoiceForm();
		}
		else
		{
			if(!_hoveredPartId.empty())
			{
				_fe3d->model_setOpacity(_currentModelId, _hoveredPartId, _originalPartOpacity);
				_hoveredPartId = "";
			}
		}
	}
}