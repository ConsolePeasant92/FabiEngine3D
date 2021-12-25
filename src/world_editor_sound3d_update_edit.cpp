#include "world_editor.hpp"

void WorldEditor::_updateSoundEditing()
{
	auto rightWindow = _gui.getViewport("right")->getWindow("main");

	if(_currentTemplateModelID.empty() && _currentTemplateBillboardID.empty() && _currentTemplateSoundID.empty() && !_isPlacingPointlight && !_isPlacingSpotlight && !_isPlacingReflection)
	{
		// Reset selected speaker from last frame
		if(!_dontResetSelectedSpeaker)
		{
			_selectedSpeakerID = "";
		}
		else
		{
			_dontResetSelectedSpeaker = false;
		}

		// Check which entity is selected
		auto hoveredAabbID = _fe3d.raycast_checkCursorInAny().first;

		// Check if user selected a speaker model
		for(const auto& ID : _fe3d.model_getIDs())
		{
			// Must be sound template entity
			if(ID.substr(0, string("@@speaker").size()) == "@@speaker")
			{
				// Cursor must be in 3D space, no GUI interruptions, no RMB holding down
				if(hoveredAabbID == ID && _fe3d.misc_isCursorInsideViewport() &&
				   !_gui.getOverlay()->isFocused() && !_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Select hovered speaker
					_selectSound(ID.substr(string("@@speaker_").size()));

					// Change cursor
					_fe3d.image_setDiffuseMap("@@cursor", "engine\\assets\\texture\\cursor_pointing.png");

					// Check if user clicked speaker
					if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
					{
						// Check if same speaker is not clicked again
						if(_selectedSpeakerID != _activeSpeakerID)
						{
							_activateSound(_selectedSpeakerID.substr(string("@@speaker_").size()));
						}
					}
				}
				else
				{
					// Unselect if necessary
					if((ID != _selectedSpeakerID) && (ID != _activeSpeakerID))
					{
						_unselectSound(ID);
					}
				}
			}
		}

		// Check if RMB not down
		if(!_fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check if allowed by GUI
			if(_fe3d.misc_isCursorInsideViewport() && !_gui.getOverlay()->isFocused())
			{
				// Check if speaker is active
				if(!_activeSpeakerID.empty())
				{
					// Check if active speaker cancelled
					if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && _selectedSpeakerID.empty()) || _fe3d.input_isMouseDown(InputType::MOUSE_BUTTON_MIDDLE))
					{
						_activeSpeakerID = "";
						rightWindow->setActiveScreen("main");
					}
				}
			}
		}

		// Update speaker highlighting
		if(_selectedSpeakerID != _activeSpeakerID)
		{
			_updateSpeakerHighlighting(_selectedSpeakerID, _selectedSpeakerHighlightDirection);
		}
		_updateSpeakerHighlighting(_activeSpeakerID, _activeSpeakerHighlightDirection);

		// Update properties screen
		if(!_activeSpeakerID.empty())
		{
			// Temporary values
			const string activeSoundID = _activeSpeakerID.substr(string("@@speaker_").size());
			auto screen = rightWindow->getScreen("soundPropertiesMenu");

			// Activate screen
			rightWindow->setActiveScreen("soundPropertiesMenu");

			// Button management
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
				{
					_fe3d.model_delete(_activeSpeakerID);
					_fe3d.sound3d_delete(activeSoundID);
					rightWindow->setActiveScreen("main");
					_activeSpeakerID = "";
					return;
				}
			}

			// Alternative way of deleting
			if(_fe3d.input_isKeyPressed(InputType::KEY_DELETE))
			{
				_fe3d.model_delete(_activeSpeakerID);
				_fe3d.sound3d_delete(activeSoundID);
				rightWindow->setActiveScreen("main");
				_activeSpeakerID = "";
				return;
			}

			// Get current values
			auto position = _fe3d.sound3d_getPosition(activeSoundID);
			auto maxDistance = _fe3d.sound3d_getMaxDistance(activeSoundID);
			auto maxVolume = _fe3d.sound3d_getMaxVolume(activeSoundID);

			// Handle position
			_handleValueChanging("soundPropertiesMenu", "xPlus", "x", position.x, (_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "xMinus", "x", position.x, -(_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "yPlus", "y", position.y, (_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "yMinus", "y", position.y, -(_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "zPlus", "z", position.z, (_editorSpeed / 100.0f));
			_handleValueChanging("soundPropertiesMenu", "zMinus", "z", position.z, -(_editorSpeed / 100.0f));
			_fe3d.sound3d_setPosition(activeSoundID, position);

			// Handle distance
			_handleValueChanging("soundPropertiesMenu", "distancePlus", "distance", maxDistance, (_editorSpeed / 100.0f), 1.0f, 0.0f);
			_handleValueChanging("soundPropertiesMenu", "distanceMinus", "distance", maxDistance, -(_editorSpeed / 100.0f), 1.0f, 0.0f);
			_fe3d.sound3d_setMaxDistance(activeSoundID, maxDistance);

			// Handle volume
			_handleValueChanging("soundPropertiesMenu", "volumePlus", "volume", maxVolume, SOUND_VOLUME_CHANGING_SPEED, 100.0f, 0.0f, 1.0f);
			_handleValueChanging("soundPropertiesMenu", "volumeMinus", "volume", maxVolume, -SOUND_VOLUME_CHANGING_SPEED, 100.0f, 0.0f, 1.0f);
			_fe3d.sound3d_setMaxVolume(activeSoundID, maxVolume);
		}

		// Check if sound is still selected or active
		if(_selectedSpeakerID.empty() && _activeSpeakerID.empty())
		{
			_fe3d.text_setVisible(_gui.getOverlay()->getTextField("soundID")->getEntityID(), false);
		}
	}
}