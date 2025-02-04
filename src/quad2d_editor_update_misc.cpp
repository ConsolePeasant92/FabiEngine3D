#include "quad2d_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void Quad2dEditor::_updateMiscellaneous()
{
	if(!_gui->getOverlay()->isFocused() && Tools::isCursorInsideDisplay())
	{
		if(!_currentQuad2dId.empty())
		{
			if(_fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_F))
			{
				_fe3d->quad2d_setWireframed(_currentQuad2dId, !_fe3d->quad2d_isWireframed(_currentQuad2dId));
			}
		}
	}
}

void Quad2dEditor::_updateQuad2dCreating()
{
	if((_gui->getOverlay()->getValueFormId() == "createQuad2d") && _gui->getOverlay()->isValueFormConfirmed())
	{
		auto quad2dId = _gui->getOverlay()->getValueFormContent();

		if(quad2dId.empty())
		{
			Logger::throwWarning("Quad2D ID cannot be empty");

			return;
		}

		if(any_of(quad2dId.begin(), quad2dId.end(), isspace))
		{
			Logger::throwWarning("Quad2D ID cannot contain any spaces");

			return;
		}

		if(any_of(quad2dId.begin(), quad2dId.end(), isupper))
		{
			Logger::throwWarning("Quad2D ID cannot contain any capitals");

			return;
		}

		if(quad2dId.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_") != string::npos)
		{
			Logger::throwWarning("Quad2D ID cannot contain any specials");

			return;
		}

		quad2dId = ("@" + quad2dId);

		if(find(_loadedQuad2dIds.begin(), _loadedQuad2dIds.end(), quad2dId) != _loadedQuad2dIds.end())
		{
			Logger::throwWarning("Quad2D already exists");

			return;
		}

		if(getCurrentProjectId().empty())
		{
			abort();
		}

		_fe3d->quad2d_create(quad2dId, true);

		if(_fe3d->quad2d_isExisting(quad2dId))
		{
			_fe3d->quad2d_setPosition(quad2dId, Tools::convertPositionRelativeToDisplay(fvec2(0.0f)));
			_fe3d->quad2d_setSize(quad2dId, Tools::convertSizeRelativeToDisplay(fvec2(QUAD2D_SIZE.x, (QUAD2D_SIZE.y * Tools::getWindowAspectRatio()))));

			_loadedQuad2dIds.push_back(quad2dId);

			sort(_loadedQuad2dIds.begin(), _loadedQuad2dIds.end());

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuChoice");
			_gui->getOverlay()->getTextField(QUAD2D_TITLE_ID)->setTextContent("Quad2D: " + quad2dId.substr(1));
			_gui->getOverlay()->getTextField(QUAD2D_TITLE_ID)->setVisible(true);

			_currentQuad2dId = quad2dId;
		}
	}
}

void Quad2dEditor::_updateQuad2dChoosing()
{
	if((_gui->getOverlay()->getChoiceFormId() == "editQuad2d") || (_gui->getOverlay()->getChoiceFormId() == "deleteQuad2d"))
	{
		const auto selectedOptionId = _gui->getOverlay()->getChoiceFormOptionId();

		if(selectedOptionId.empty())
		{
			if(!_hoveredQuad2dId.empty())
			{
				_fe3d->quad2d_setVisible(_hoveredQuad2dId, false);

				_hoveredQuad2dId = "";
			}
		}
		else
		{
			if(_hoveredQuad2dId.empty())
			{
				_hoveredQuad2dId = ("@" + selectedOptionId);

				_fe3d->quad2d_setVisible(_hoveredQuad2dId, true);
			}

			if(_gui->getOverlay()->isChoiceFormConfirmed())
			{
				_currentQuad2dId = _hoveredQuad2dId;
				_hoveredQuad2dId = "";

				if(_gui->getOverlay()->getChoiceFormId() == "deleteQuad2d")
				{
					_gui->getOverlay()->openAnswerForm("deleteQuad2d", "Are You Sure?", "Yes", "No", ANSWER_FORM_POSITION);
				}
				else
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("quad2dEditorMenuChoice");

					_gui->getOverlay()->getTextField(QUAD2D_TITLE_ID)->setTextContent("Quad2D: " + _currentQuad2dId.substr(1));
					_gui->getOverlay()->getTextField(QUAD2D_TITLE_ID)->setVisible(true);
				}
			}
		}
	}
	else
	{
		if(!_hoveredQuad2dId.empty())
		{
			_fe3d->quad2d_setVisible(_hoveredQuad2dId, false);

			_hoveredQuad2dId = "";
		}
	}
}

void Quad2dEditor::_updateQuad2dDeleting()
{
	if((_gui->getOverlay()->getAnswerFormId() == "deleteQuad2d") && _gui->getOverlay()->isAnswerFormConfirmed())
	{
		if(_gui->getOverlay()->getAnswerFormDecision() == "Yes")
		{
			_fe3d->quad2d_delete(_currentQuad2dId);

			_loadedQuad2dIds.erase(remove(_loadedQuad2dIds.begin(), _loadedQuad2dIds.end(), _currentQuad2dId), _loadedQuad2dIds.end());

			_currentQuad2dId = "";
		}
		else if(_gui->getOverlay()->getAnswerFormDecision() == "No")
		{
			_currentQuad2dId = "";
		}
	}
}