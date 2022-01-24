#include "model_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void ModelEditor::_updateMainAabbMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuAabbMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuChoice");
			_fe3d->misc_disableAabbFrameRendering();
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->createValueForm("aabbCreate", "Create AABB", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingAabb = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto Ids = _fe3d->aabb_getChildIds(_currentModelId, AabbParentEntityType::MODEL);
			for(auto& id : Ids)
			{
				id = id.substr(string(_currentModelId + "@").size());
			}
			sort(Ids.begin(), Ids.end());
			_gui->getOverlay()->createChoiceForm("aabbList", "Edit AABB", fvec2(-0.5f, 0.1f), Ids);
			_isChoosingAabb = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto Ids = _fe3d->aabb_getChildIds(_currentModelId, AabbParentEntityType::MODEL);
			for(auto& id : Ids)
			{
				id = id.substr(string(_currentModelId + "@").size());
			}
			sort(Ids.begin(), Ids.end());
			_gui->getOverlay()->createChoiceForm("aabbList", "Delete AABB", fvec2(-0.5f, 0.1f), Ids);
			_isChoosingAabb = true;
			_isDeletingAabb = true;
		}
	}
}

void ModelEditor::_updateChoiceAabbMenu()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "modelEditorMenuAabbChoice")
	{
		auto position = _fe3d->aabb_getPosition(_currentModelId + "@" + _currentAabbId);
		auto size = _fe3d->aabb_getSize(_currentModelId + "@" + _currentAabbId);

		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_fe3d->aabb_setVisible((_currentModelId + "@" + _currentAabbId), false);
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbMain");
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("aabbId")->getEntityId(), false);
			_currentAabbId = "";
			return;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("position")->isHovered())
		{
			_gui->getOverlay()->createValueForm("positionX", "X", (position.x * 100.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("positionY", "Y", (position.y * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("positionZ", "Z", (position.z * 100.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("size")->isHovered())
		{
			_gui->getOverlay()->createValueForm("sizeX", "X", (size.x * 100.0f), fvec2(-0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("sizeY", "Y", (size.y * 100.0f), fvec2(0.0f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
			_gui->getOverlay()->createValueForm("sizeZ", "Z", (size.z * 100.0f), fvec2(0.25f, 0.1f), fvec2(0.15f, 0.1f), fvec2(0.0f, 0.1f));
		}

		if(_gui->getOverlay()->checkValueForm("positionX", position.x))
		{
			position.x /= 100.0f;
			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), position);
		}
		if(_gui->getOverlay()->checkValueForm("positionY", position.y))
		{
			position.y /= 100.0f;
			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), position);
		}
		if(_gui->getOverlay()->checkValueForm("positionZ", position.z))
		{
			position.z /= 100.0f;
			_fe3d->aabb_setLocalPosition((_currentModelId + "@" + _currentAabbId), position);
		}
		if(_gui->getOverlay()->checkValueForm("sizeX", size.x))
		{
			size.x /= 100.0f;
			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), size);
		}
		if(_gui->getOverlay()->checkValueForm("sizeY", size.y))
		{
			size.y /= 100.0f;
			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), size);
		}
		if(_gui->getOverlay()->checkValueForm("sizeZ", size.z))
		{
			size.z /= 100.0f;
			_fe3d->aabb_setLocalSize((_currentModelId + "@" + _currentAabbId), size);
		}
	}
}

void ModelEditor::_updateAabbCreating()
{
	if(_isCreatingAabb)
	{
		string newAabbId;

		if(_gui->getOverlay()->checkValueForm("aabbCreate", newAabbId, {}))
		{
			if(newAabbId.find(' ') != string::npos)
			{
				Logger::throwWarning("AABB id cannot contain any spaces!");
				return;
			}

			if(newAabbId.find('@') != string::npos)
			{
				Logger::throwWarning("AABB id cannot contain '@'!");
				return;
			}

			if(_fe3d->aabb_isExisting(_currentModelId + "@" + newAabbId))
			{
				Logger::throwWarning("AABB with id \"" + newAabbId + "\" already exists!");
				return;
			}

			_currentAabbId = newAabbId;

			_fe3d->aabb_create(_currentModelId + "@" + _currentAabbId, false);
			_fe3d->aabb_setFollowParentVisibility((_currentModelId + "@" + _currentAabbId), false);
			_fe3d->aabb_setParentEntityId((_currentModelId + "@" + _currentAabbId), _currentModelId);
			_fe3d->aabb_setParentEntityType((_currentModelId + "@" + _currentAabbId), AabbParentEntityType::MODEL);

			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbChoice");
			_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("aabbId")->getEntityId(), ("AABB: " + _currentAabbId), 0.025f);
			_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("aabbId")->getEntityId(), true);

			_isCreatingAabb = false;
		}
	}
}

void ModelEditor::_updateAabbChoosing()
{
	if(_isChoosingAabb)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("aabbList");

		if(!selectedButtonId.empty())
		{
			if(_hoveredAabbId.empty())
			{
				_hoveredAabbId = selectedButtonId;
				_fe3d->aabb_setVisible((_currentModelId + "@" + _hoveredAabbId), true);
			}

			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentAabbId = selectedButtonId;
				_hoveredAabbId = "";

				if(!_isDeletingAabb)
				{
					_gui->getLeftViewport()->getWindow("main")->setActiveScreen("modelEditorMenuAabbChoice");

					_fe3d->text2d_setContent(_gui->getOverlay()->getTextField("aabbId")->getEntityId(), ("AABB: " + _currentAabbId), 0.025f);
					_fe3d->text2d_setVisible(_gui->getOverlay()->getTextField("aabbId")->getEntityId(), true);
				}

				_gui->getOverlay()->deleteChoiceForm("aabbList");
				_isChoosingAabb = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("aabbList"))
		{
			_gui->getOverlay()->deleteChoiceForm("aabbList");
			_isChoosingAabb = false;
			_isDeletingAabb = false;
		}
		else
		{
			if(!_hoveredAabbId.empty())
			{
				_fe3d->aabb_setVisible((_currentModelId + "@" + _hoveredAabbId), false);
				_hoveredAabbId = "";
			}
		}
	}
}

void ModelEditor::_updateAabbDeleting()
{
	if(_isDeletingAabb && !_currentAabbId.empty())
	{
		if(!_gui->getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_fe3d->aabb_delete(_currentModelId + "@" + _currentAabbId);
			_isDeletingAabb = false;
			_currentAabbId = "";
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_isDeletingAabb = false;
			_currentAabbId = "";
		}
	}
}