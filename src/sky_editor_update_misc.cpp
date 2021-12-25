#include "sky_editor.hpp"
#include "logger.hpp"

void SkyEditor::_updateCamera()
{
	if(_fe3d.camera_isFirstPersonViewEnabled())
	{
		// Hide cursor
		_fe3d.image_setVisible("@@cursor", false);
	}

	if(!_gui.getOverlay()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Check if RMB pressed
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check first person view status
			if(_fe3d.camera_isFirstPersonViewEnabled())
			{
				_fe3d.camera_disableFirstPersonView();
			}
			else
			{
				_fe3d.camera_enableFirstPersonView(_fe3d.camera_getFirstPersonYaw(), _fe3d.camera_getFirstPersonPitch());
			}
		}
	}

	if(_fe3d.camera_isFirstPersonViewEnabled())
	{
		if(_gui.getOverlay()->isFocused())
		{
			_fe3d.camera_disableFirstPersonView();
		}
	}
}

void SkyEditor::_updateMiscellaneous()
{
	if(!_gui.getOverlay()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update wireframe rendering
		if(!_currentSkyID.empty())
		{
			if(_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d.sky_isWireframed(_currentSkyID))
				{
					_fe3d.sky_setWireframed(_currentSkyID, false);
				}
				else
				{
					_fe3d.sky_setWireframed(_currentSkyID, true);
				}
			}
		}
	}
}

void SkyEditor::_updateSkyCreating()
{
	if(_isCreatingSky)
	{
		// Temporary values
		string newSkyID;

		// Check if user filled in a new ID
		if(_gui.getOverlay()->checkValueForm("skyCreate", newSkyID, {}))
		{
			// Spaces not allowed
			if(newSkyID.find(' ') != string::npos)
			{
				Logger::throwWarning("Sky ID cannot contain any spaces!");
				return;
			}

			// @ sign not allowed
			if(newSkyID.find('@') != string::npos)
			{
				Logger::throwWarning("Sky ID cannot contain '@'!");
				return;
			}

			// Add @ sign to new ID
			newSkyID = ("@" + newSkyID);

			// Check if sky already exists
			if(find(_loadedSkyIDs.begin(), _loadedSkyIDs.end(), newSkyID) != _loadedSkyIDs.end())
			{
				Logger::throwWarning("Sky with ID \"" + newSkyID.substr(1) + "\" already exists!");
				return;
			}

			// Create sky
			_fe3d.sky_create(newSkyID);

			// Check if sky creation went well
			if(_fe3d.sky_isExisting(newSkyID))
			{
				// Go to next screen
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");

				// Select sky
				_currentSkyID = newSkyID;
				_loadedSkyIDs.push_back(newSkyID);
				_fe3d.sky_selectMainSky(newSkyID);

				// Miscellaneous
				_fe3d.text_setContent(_gui.getOverlay()->getTextField("skyID")->getEntityID(), "Sky: " + newSkyID.substr(1), 0.025f);
				_fe3d.text_setVisible(_gui.getOverlay()->getTextField("skyID")->getEntityID(), true);
				_isCreatingSky = false;
			}
		}
	}
}

void SkyEditor::_updateSkyChoosing()
{
	if(_isChoosingSky)
	{
		// Hide last sky
		_fe3d.sky_selectMainSky("@@background");

		// Get selected button ID
		string selectedButtonID = _gui.getOverlay()->checkChoiceForm("skyList");

		// Check if sky ID is hovered
		if(!selectedButtonID.empty())
		{
			// Show sky
			_fe3d.sky_selectMainSky("@" + selectedButtonID);

			// Check if LMB is pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select sky
				_currentSkyID = ("@" + selectedButtonID);

				// Go to next screen
				if(!_isDeletingSky)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("skyEditorMenuChoice");
					_fe3d.text_setContent(_gui.getOverlay()->getTextField("skyID")->getEntityID(), "Sky: " + _currentSkyID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getOverlay()->getTextField("skyID")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getOverlay()->deleteChoiceForm("skyList");
				_isChoosingSky = false;
			}
		}
		else if(_gui.getOverlay()->isChoiceFormCancelled("skyList"))
		{
			_isChoosingSky = false;
			_isDeletingSky = false;
			_gui.getOverlay()->deleteChoiceForm("skyList");
		}
	}
}

void SkyEditor::_updateSkyDeleting()
{
	if(_isDeletingSky && !_currentSkyID.empty())
	{
		// Add answer form
		if(!_gui.getOverlay()->isAnswerFormExisting("delete"))
		{
			_gui.getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		// Update answer form
		if(_gui.getOverlay()->isAnswerFormConfirmed("delete"))
		{
			// Delete entity
			_fe3d.sky_delete(_currentSkyID);

			// Delete from ID record
			_loadedSkyIDs.erase(remove(_loadedSkyIDs.begin(), _loadedSkyIDs.end(), _currentSkyID), _loadedSkyIDs.end());
			_isDeletingSky = false;
			_currentSkyID = "";

			// Select background
			_fe3d.sky_selectMainSky("@@background");
		}
		if(_gui.getOverlay()->isAnswerFormDenied("delete"))
		{
			// Select background
			_fe3d.sky_selectMainSky("@@background");

			// Miscellaneous
			_isDeletingSky = false;
			_currentSkyID = "";
		}
	}
}