#include "quad3d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad3dEditor::_updateCamera()
{
	if(_fe3d->camera_isThirdPersonEnabled())
	{
		const auto cameraLookat = _fe3d->camera_getThirdPersonLookat();
		const auto distanceOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_Q)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_E)));
		const auto lookatOffset = (static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SPACEBAR)) - static_cast<float>(_fe3d->input_isKeyboardHeld(KeyboardKeyType::KEY_SHIFT)));

		_fe3d->camera_setThirdPersonDistance(max(MIN_CAMERA_DISTANCE, (_fe3d->camera_getThirdPersonDistance() - (distanceOffset * CAMERA_DISTANCE_SPEED))));
		_fe3d->camera_setThirdPersonLookat(fvec3(cameraLookat.x, max(0.0f, (cameraLookat.y + (lookatOffset * CAMERA_LOOKAT_SPEED))), cameraLookat.z));
		_fe3d->quad2d_setVisible(_fe3d->misc_getCursorId(), false);
	}

	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_RIGHT))
		{
			_fe3d->camera_setThirdPersonEnabled(!_fe3d->camera_isThirdPersonEnabled());
		}
	}

	if(_gui->getOverlay()->isFocused())
	{
		_fe3d->camera_setThirdPersonEnabled(false);
	}
}

void Quad3dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_G))
		{
			_fe3d->model_setVisible(GRID_ID, !_fe3d->model_isVisible(GRID_ID));
		}

		if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_R))
		{
			_fe3d->model_setVisible(BOX_ID, !_fe3d->model_isVisible(BOX_ID));
		}

		if(!_currentQuad3dId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				_fe3d->quad3d_setWireframed(_currentQuad3dId, !_fe3d->quad3d_isWireframed(_currentQuad3dId));
			}
		}
	}
}

void Quad3dEditor::_updateQuad3dCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createQuad3d") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto quad3dId = _gui->getOverlay()->getValueFormContent();

		if(quad3dId.empty())
		{
			Logger::throwWarning("Quad3D ID cannot be empty");

			return;
		}

		if(any_of(quad3dId.begin(), quad3dId.end(), isspace))
		{
			Logger::throwWarning("Quad3D ID cannot contain any spaces");

			return;
		}

		if(any_of(quad3dId.begin(), quad3dId.end(), isupper))
		{
			Logger::throwWarning("Quad3D ID cannot contain any capitals");

			return;
		}

		if(quad3dId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
		{
			Logger::throwWarning("Quad3D ID cannot contain any specials");

			return;
		}

		quad3dId = ("@" + quad3dId);

		if(find(_loadedQuad3dIds.begin(), _loadedQuad3dIds.end(), quad3dId) != _loadedQuad3dIds.end())
		{
			Logger::throwWarning("Quad3D already exists");

			return;
		}

		_fe3d->quad3d_create(quad3dId, false);

		_loadedQuad3dIds.push_back(quad3dId);

		sort(_loadedQuad3dIds.begin(), _loadedQuad3dIds.end());

		_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");
		_gui->getOverlay()->getTextField(QUAD3D_TITLE_ID)->setTextContent("Quad3D: " + quad3dId.substr(1));
		_gui->getOverlay()->getTextField(QUAD3D_TITLE_ID)->setVisible(true);

		_currentQuad3dId = quad3dId;
	}
}

void Quad3dEditor::_updateQuad3dChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editQuad3d") || (_gui->getOverlay()->getChoiceFormId() == "deleteQuad3d"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredQuad3dId.empty())
			{
				_fe3d->quad3d_setVisible(_hoveredQuad3dId, false);

				_hoveredQuad3dId = "";
			}
		}
		else
		{
			if(_hoveredQuad3dId.empty())
			{
				_hoveredQuad3dId = ("@" + selectedOptionId);

				_fe3d->quad3d_setVisible(_hoveredQuad3dId, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentQuad3dId = _hoveredQuad3dId;
				_hoveredQuad3dId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteQuad3d")
				{
					_gui->getOverlay()->openAnswerForm("deleteQuad3d", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad3dEditorMenuChoice");

					_gui->getOverlay()->getTextField(QUAD3D_TITLE_ID)->setTextContent("Quad3D: " + _currentQuad3dId.substr(1));
					_gui->getOverlay()->getTextField(QUAD3D_TITLE_ID)->setVisible(true);
				}
			}
		}
	}
	else
	{
		if(!_hoveredQuad3dId.empty())
		{
			_fe3d->quad3d_setVisible(_hoveredQuad3dId, false);

			_hoveredQuad3dId = "";
		}
	}
}

void Quad3dEditor::_updateQuad3dDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteQuad3d") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->quad3d_delete(_currentQuad3dId);

			_loadedQuad3dIds.erase(remove(_loadedQuad3dIds.begin(), _loadedQuad3dIds.end(), _currentQuad3dId), _loadedQuad3dIds.end());

			_currentQuad3dId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_fe3d->quad3d_setVisible(_currentQuad3dId, false);

			_currentQuad3dId = "";
		}
	}
}