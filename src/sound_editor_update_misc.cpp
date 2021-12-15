#include "sound_editor.hpp"
#include "logger.hpp"
#include "tools.hpp"

void SoundEditor::_updateSoundCreating()
{
	if(_isCreatingSound)
	{
		string newSoundID = "";

		// Check if user filled in a new ID
		if(_gui.getGlobalScreen()->checkValueForm("soundCreate", newSoundID, {_currentSoundID}))
		{
			// Check if ID starts with @ sign
			if(newSoundID[0] != '@')
			{
				// Check if ID contains spaces
				if(newSoundID.find(' ') == string::npos)
				{
					// Add @ sign to new ID
					newSoundID = ("@" + newSoundID);

					// Check if sound not already exists
					if(find(_loadedSoundIDs.begin(), _loadedSoundIDs.end(), newSoundID) == _loadedSoundIDs.end())
					{
						// Validate project ID
						if(_currentProjectID.empty())
						{
							Logger::throwError("SoundEditor::_updateSoundCreating");
						}

						// Get the chosen file name
						const auto rootDirectoryPath = Tools::getRootDirectoryPath();
						const string targetDirectoryPath = string("projects\\" + _currentProjectID + "\\assets\\audio\\");

						// Validate target directory
						if(!Tools::isDirectoryExisting(rootDirectoryPath + targetDirectoryPath))
						{
							Logger::throwWarning("Directory `" + targetDirectoryPath + "` is missing!");
							_isCreatingSound = false;
							return;
						}

						// Validate chosen file
						const string filePath = Tools::chooseExplorerFile(string(rootDirectoryPath + targetDirectoryPath), "WAV");
						if(filePath.empty())
						{
							_isCreatingSound = false;
							return;
						}

						// Validate directory of file
						if(filePath.size() > (rootDirectoryPath.size() + targetDirectoryPath.size()) &&
						   filePath.substr(rootDirectoryPath.size(), targetDirectoryPath.size()) != targetDirectoryPath)
						{
							Logger::throwWarning("File cannot be outside of `" + targetDirectoryPath + "`!");
							_isCreatingSound = false;
							return;
						}

						// Create sound
						const string finalFilePath = filePath.substr(rootDirectoryPath.size());
						_fe3d.misc_clearSoundCache(finalFilePath);
						_fe3d.sound2d_create(newSoundID, finalFilePath);

						// Check if sound creation went well
						if(_fe3d.sound2d_isExisting(newSoundID))
						{
							// Go to next screen
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("soundEditorMenuChoice");

							// Select sound
							_currentSoundID = newSoundID;
							_loadedSoundIDs.push_back(newSoundID);

							// Miscellaneous
							_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), "Sound: " + newSoundID.substr(1), 0.025f);
							_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), true);
							_isCreatingSound = false;
						}
					}
					else
					{
						Logger::throwWarning("Sound with ID \"" + newSoundID.substr(1) + "\" already exists!");
					}
				}
				else
				{
					Logger::throwWarning("Sound ID cannot contain any spaces!");
				}
			}
			else
			{
				Logger::throwWarning("Sound ID cannot begin with '@'!");
			}
		}
	}
}

void SoundEditor::_updateSoundChoosing()
{
	if(_isChoosingSound)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("soundList");

		// Check if a sound ID is hovered
		if(!selectedButtonID.empty())
		{
			// Check if LMB is pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select sound
				_currentSoundID = ("@" + selectedButtonID);

				// Go to next screen
				if(!_isDeletingSound)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("soundEditorMenuChoice");
					_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), "Sound: " + selectedButtonID.substr(1), 0.025f);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("soundID")->getEntityID(), true);
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("soundList");
				_isChoosingSound = false;
			}
		}
		else if(_gui.getGlobalScreen()->isChoiceFormCancelled("soundList")) // Cancelled choosing
		{
			_isChoosingSound = false;
			_isDeletingSound = false;
			_gui.getGlobalScreen()->deleteChoiceForm("soundList");
		}
	}
}

void SoundEditor::_updateSoundDeleting()
{
	if(_isDeletingSound && !_currentSoundID.empty())
	{
		// Add answer form
		if(!_gui.getGlobalScreen()->isAnswerFormExisting("delete"))
		{
			_gui.getGlobalScreen()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
		}

		// Update answer form
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("delete"))
		{
			// Go to main screen
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("soundEditorMenuMain");

			// Delete sound
			if(_fe3d.sound2d_isExisting(_currentSoundID))
			{
				_fe3d.sound2d_delete(_currentSoundID);
			}

			// Miscellaneous
			_loadedSoundIDs.erase(remove(_loadedSoundIDs.begin(), _loadedSoundIDs.end(), _currentSoundID), _loadedSoundIDs.end());
			_currentSoundID = "";
			_isDeletingSound = false;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_isChoosingSound = true;
			_currentSoundID = "";
		}
	}
}