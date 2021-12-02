#include "audio_editor.hpp"
#include "logger.hpp"

void AudioEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "audioEditorMenuChoice")
	{
		// Temporary values
		bool isExisting = _fe3d.sound2D_isExisting(_currentAudioID);
		bool isPlaying = isExisting && _fe3d.sound2D_isPlaying(_currentAudioID);
		bool isPaused = isExisting && _fe3d.sound2D_isPaused(_currentAudioID);

		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			// Stop audio preview
			if(isPlaying)
			{
				_fe3d.sound2D_stop(_currentAudioID, 0);
			}

			// Miscellaneous
			_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("audioID")->getEntityID(), false);
			_currentAudioID = "";
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("audioEditorMenuMain");
			return;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("play")->isHovered())
		{
			_fe3d.sound2D_play(_currentAudioID, 0, 0, false);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("resume")->isHovered())
		{
			_fe3d.sound2D_resume(_currentAudioID);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("pause")->isHovered())
		{
			_fe3d.sound2D_pause(_currentAudioID);
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			_fe3d.sound2D_stop(_currentAudioID, 0);
		}

		// Controlling audio playback through keyboard
		if(_fe3d.input_isKeyPressed(InputType::KEY_SPACE) && !isPlaying && !isPaused)
		{
			_fe3d.sound2D_play(_currentAudioID, 0, 0, false);
		}
		else if(_fe3d.input_isKeyPressed(InputType::KEY_R) && isPaused)
		{
			_fe3d.sound2D_resume(_currentAudioID);
		}
		else if(_fe3d.input_isKeyPressed(InputType::KEY_P) && isPlaying)
		{
			_fe3d.sound2D_pause(_currentAudioID);
		}
		else if(_fe3d.input_isKeyPressed(InputType::KEY_S) && (isPlaying || isPaused))
		{
			_fe3d.sound2D_stop(_currentAudioID, 0);
		}

		// Update buttons hoverability
		screen->getButton("play")->setHoverable(!isPlaying && !isPaused);
		screen->getButton("resume")->setHoverable(isPaused);
		screen->getButton("pause")->setHoverable(isPlaying);
		screen->getButton("stop")->setHoverable(isPlaying || isPaused);
	}
}