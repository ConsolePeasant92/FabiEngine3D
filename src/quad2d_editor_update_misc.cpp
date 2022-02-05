#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad2dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
	{
		if(!_currentQuadId.empty())
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F))
			{
				_fe3d->quad2d_setWireframed(_currentQuadId, !_fe3d->quad2d_isWireframed(_currentQuadId));
			}
		}
	}
}

void Quad2dEditor::_updateQuadCreating()
{
	if(_isCreatingQuad)
	{
		string newQuadId;

		if(_gui->getOverlay()->checkValueForm("quadCreate", newQuadId, {_currentQuadId}))
		{
			if(any_of(newQuadId.begin(), newQuadId.end(), isspace))
			{
				Logger::throwWarning("Quad ID cannot contain any spaces");
				return;
			}

			if(!all_of(newQuadId.begin(), newQuadId.end(), isalnum))
			{
				Logger::throwWarning("Quad ID cannot contain any specials");
				return;
			}

			if(any_of(newQuadId.begin(), newQuadId.end(), isupper))
			{
				Logger::throwWarning("Quad ID cannot contain any capitals");
				return;
			}

			newQuadId = ("@" + newQuadId);

			if(find(_loadedQuadIds.begin(), _loadedQuadIds.end(), newQuadId) != _loadedQuadIds.end())
			{
				Logger::throwWarning("Quad already exists");
				return;
			}

			if(getCurrentProjectId().empty())
			{
				abort();
			}

			_fe3d->quad2d_create(newQuadId, true);

			if(_fe3d->quad2d_isExisting(newQuadId))
			{
				_fe3d->quad2d_setPosition(newQuadId, Tools::convertPositionRelativeToViewport(fvec2(0.0f)));
				_fe3d->quad2d_setSize(newQuadId, Tools::convertSizeRelativeToViewport(fvec2(QUAD_SIZE.x, (QUAD_SIZE.y * Tools::getWindowAspectRatio()))));

				_currentQuadId = newQuadId;
				_loadedQuadIds.push_back(newQuadId);

				_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuChoice");
				_gui->getOverlay()->getTextField("quadId")->changeTextContent("Quad2D: " + newQuadId.substr(1));
				_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), true);
				_isCreatingQuad = false;
			}
		}
	}
}

void Quad2dEditor::_updateQuadChoosing()
{
	if(_isChoosingQuad)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("quadList");

		if(!selectedButtonId.empty())
		{
			if(_hoveredQuadId.empty())
			{
				_hoveredQuadId = ("@" + selectedButtonId);
				_fe3d->quad2d_setVisible(_hoveredQuadId, false);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentQuadId = _hoveredQuadId;
				_hoveredQuadId = "";

				if(!_isDeletingQuad)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuChoice");

					_gui->getOverlay()->getTextField("quadId")->changeTextContent("Quad2D: " + selectedButtonId.substr(1));
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("quadId")->getEntityId(), true);
				}

				_fe3d->quad2d_setVisible(_currentQuadId, true);
				_gui->getOverlay()->deleteChoiceForm("quadList");
				_isChoosingQuad = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("quadList"))
		{
			_gui->getOverlay()->deleteChoiceForm("quadList");
			_isChoosingQuad = false;
			_isDeletingQuad = false;
		}
		else
		{
			if(!_hoveredQuadId.empty())
			{
				_fe3d->quad2d_setVisible(_hoveredQuadId, true);
				_hoveredQuadId = "";
			}
		}
	}
}

void Quad2dEditor::_updateQuadDeleting()
{
	if(_isDeletingQuad && !_currentQuadId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->quad2d_delete(_currentQuadId);

			_loadedQuadIds.erase(remove(_loadedQuadIds.begin(), _loadedQuadIds.end(), _currentQuadId), _loadedQuadIds.end());
			_currentQuadId = "";
			_isDeletingQuad = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_currentQuadId = "";
			_isDeletingQuad = false;
		}
	}
}