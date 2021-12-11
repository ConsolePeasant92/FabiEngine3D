#include "sprite_animation_editor.hpp"
#include "logger.hpp"

void SpriteAnimationEditor::update()
{
	// Animation execution
	_updateAnimationExecution();

	// Editor updates
	if(_isEditorLoaded)
	{
		_updateMainMenu();
	}
	if(_isEditorLoaded)
	{
		_updateChoiceMenu();
	}
	if(_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

void SpriteAnimationEditor::_updateMainMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if(screen->getID() == "spriteAnimationEditorMenuMain")
	{
		// Button management
		if((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("animationCreate", "Create Animation", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingAnimation = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_gui.getGlobalScreen()->createChoiceForm("animationList", "Edit Animation", fvec2(-0.5f, 0.1f), getAllAnimationIDs());
			_isChoosingAnimation = true;
		}
		else if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			auto IDs = getAllAnimationIDs();
			for(auto& ID : IDs)
			{
				ID = ID.substr(1);
			}
			_gui.getGlobalScreen()->createChoiceForm("animationList", "Delete Animation", fvec2(-0.5f, 0.1f), IDs);
			_isChoosingAnimation = true;
			_isDeletingAnimation = true;
		}

		// Update answer forms
		if(_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveAnimationsToFile();
			unload();
			return;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}
	}
}

void SpriteAnimationEditor::_updateAnimationCreating()
{
	if(_isCreatingAnimation)
	{
		// Check if user filled in a new ID
		string newAnimationID = "";
		if(_gui.getGlobalScreen()->checkValueForm("animationCreate", newAnimationID, {_currentAnimationID}))
		{
			// Spaces not allowed
			if(newAnimationID.find(' ') == string::npos)
			{
				// Check if animation already exists
				auto animationIDs = getAllAnimationIDs();
				if(find(animationIDs.begin(), animationIDs.end(), newAnimationID) == animationIDs.end())
				{
					// Go to next screen
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("spriteAnimationEditorMenuChoice");

					// Create animation
					_animations.push_back(make_shared<SpriteAnimation>(newAnimationID));

					// Select animation
					_currentAnimationID = newAnimationID;

					// Miscellaneous
					_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), "Animation: " + newAnimationID, 0.025f);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), true);
					_isCreatingAnimation = false;

				}
				else // ID already exists
				{
					Logger::throwWarning("Animation ID \"" + newAnimationID + "\" already exists!");
				}
			}
			else
			{
				Logger::throwWarning("Animation ID cannot contain any spaces!");
			}
		}
	}
}

void SpriteAnimationEditor::_updateAnimationChoosing()
{
	if(_isChoosingAnimation)
	{
		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("animationList");

		// Check if a animation ID is hovered
		if(!selectedButtonID.empty())
		{
			// Check if LMB is pressed
			if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Select animation
				_currentAnimationID = selectedButtonID;

				// Go to next screen
				if(!_isDeletingAnimation)
				{
					_gui.getViewport("left")->getWindow("main")->setActiveScreen("spriteAnimationEditorMenuChoice");
					_fe3d.text_setContent(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), "Animation: " + selectedButtonID, 0.025f);
					_fe3d.text_setVisible(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), true);
				}

				// Miscellaneous
				_fe3d.image_setVisible(PREVIEW_IMAGE_ID, true);
				_gui.getGlobalScreen()->deleteChoiceForm("animationList");
				_isChoosingAnimation = false;
			}
		}
		else if(_gui.getGlobalScreen()->isChoiceFormCancelled("animationList")) // Cancelled choosing
		{
			_isChoosingAnimation = false;
			_isDeletingAnimation = false;
			_gui.getGlobalScreen()->deleteChoiceForm("animationList");
		}
	}
}

void SpriteAnimationEditor::_updateAnimationDeleting()
{
	if(_isDeletingAnimation && _currentAnimationID != "")
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
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("spriteAnimationEditorMenuMain");

			// Delete animation
			_fe3d.image_setVisible(PREVIEW_IMAGE_ID, false);
			_deleteAnimation(_currentAnimationID);
			_currentAnimationID = "";

			// Miscellaneous
			_isDeletingAnimation = false;
		}
		if(_gui.getGlobalScreen()->isAnswerFormDenied("delete"))
		{
			_isDeletingAnimation = false;
			_currentAnimationID = "";
		}
	}
}