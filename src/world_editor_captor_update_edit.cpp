#include "world_editor.hpp"
#include "tools.hpp"

void WorldEditor::_updateCaptorEditing()
{
	if(_currentTemplateModelId.empty() &&
	   _currentTemplateQuad3dId.empty() &&
	   _currentTemplateText3dId.empty() &&
	   _currentTemplateAabbId.empty() &&
	   _currentTemplatePointlightId.empty() &&
	   _currentTemplateSpotlightId.empty() &&
	   _currentTemplateSound3dId.empty() &&
	   !_isPlacingCaptor)
	{
		const auto window = _gui->getLeftViewport()->getWindow("main");
		const auto hoveredAabbId = _fe3d->raycast_getClosestAabbId();

		if(!_dontResetSelectedCaptor)
		{
			_selectedCaptorId = "";
		}
		else
		{
			_dontResetSelectedCaptor = false;
		}

		for(const auto & placedCaptorId : _loadedCaptorIds)
		{
			const auto isHovered = (hoveredAabbId == ("@@lens_" + placedCaptorId));

			if(isHovered && Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused() && !_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
			{
				_selectCaptor(placedCaptorId);

				if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT))
				{
					if(_selectedCaptorId != _activeCaptorId)
					{
						_activateCaptor(_selectedCaptorId);
					}
				}

				_fe3d->quad2d_setDiffuseMap(_fe3d->misc_getCursorId(), CURSOR_TEXTURE_PATH);
			}
			else
			{
				if((placedCaptorId != _selectedCaptorId) && (placedCaptorId != _activeCaptorId))
				{
					_deselectCaptor(placedCaptorId);
				}
			}
		}

		if(!_fe3d->input_isMouseHeld(MouseButtonType::BUTTON_RIGHT))
		{
			if(Tools::isCursorInsideDisplay() && !_gui->getOverlay()->isFocused())
			{
				if(!_activeCaptorId.empty())
				{
					if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && _selectedCaptorId.empty()) || _fe3d->input_isMouseHeld(MouseButtonType::BUTTON_MIDDLE))
					{
						window->setActiveScreen("empty");

						_activeCaptorId = "";
					}
				}
			}
		}

		if(!_activeCaptorId.empty())
		{
			const auto screen = window->getScreen("captorPropertiesMenu");

			window->setActiveScreen("captorPropertiesMenu");

			if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("exception")->isHovered())
			{
				vector<string> modelIds = {};

				for(auto & [placedId, templateId] : _loadedModelIds)
				{
					modelIds.push_back(placedId);
				}

				_gui->getOverlay()->openChoiceForm("selectException", "Select Exception", CENTER_CHOICE_FORM_POSITION, modelIds);
			}
			else if(_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("capture")->isHovered())
			{
				_fe3d->captor_capture(_activeCaptorId);
			}
			else if((_fe3d->input_isMousePressed(MouseButtonType::BUTTON_LEFT) && screen->getButton("delete")->isHovered()) || _fe3d->input_isKeyboardPressed(KeyboardKeyType::KEY_DELETE))
			{
				_fe3d->model_delete("@@lens_" + _activeCaptorId);
				_fe3d->captor_delete(_activeCaptorId);

				window->setActiveScreen("empty");

				_loadedCaptorIds.erase(remove(_loadedCaptorIds.begin(), _loadedCaptorIds.end(), _activeCaptorId), _loadedCaptorIds.end());

				_activeCaptorId = "";

				return;
			}

			auto position = _fe3d->captor_getPosition(_activeCaptorId);

			_handleInputBox("captorPropertiesMenu", "xMinus", "x", "xPlus", position.x, (_editorSpeed / CAPTOR_POSITION_SPEED_DIVIDER));
			_handleInputBox("captorPropertiesMenu", "yMinus", "y", "yPlus", position.y, (_editorSpeed / CAPTOR_POSITION_SPEED_DIVIDER));
			_handleInputBox("captorPropertiesMenu", "zMinus", "z", "zPlus", position.z, (_editorSpeed / CAPTOR_POSITION_SPEED_DIVIDER));

			_fe3d->captor_setPosition(_activeCaptorId, position);
			_fe3d->model_setBasePosition(("@@lens_" + _activeCaptorId), position);
		}
	}
}