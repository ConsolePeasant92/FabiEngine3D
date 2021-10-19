#include "animation_editor.hpp"
#include "logger.hpp"

void AnimationEditor::_updateChoiceMenu()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "animationEditorMenuChoice")
	{
		// Temporary values
		auto currentAnimation = _getAnimation(_currentAnimationID);

		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
		{
			// Stop animation if playing
			if (isAnimationStarted(_currentAnimationID, currentAnimation->getPreviewModelID()))
			{
				stopAnimation(_currentAnimationID, currentAnimation->getPreviewModelID());
			}

			// Reset preview model transformation
			if (_fe3d.modelEntity_isExisting(currentAnimation->getPreviewModelID()))
			{
				// For every model part
				for (const auto& partID : currentAnimation->getPartIDs())
				{
					if (partID.empty()) // Base transformation
					{
						_fe3d.modelEntity_setBasePosition(currentAnimation->getPreviewModelID(), Vec3(0.0f));
						_fe3d.modelEntity_setBaseRotationOrigin(currentAnimation->getPreviewModelID(), Vec3(0.0f));
						_fe3d.modelEntity_setBaseRotation(currentAnimation->getPreviewModelID(), Vec3(0.0f));
						_fe3d.modelEntity_setBaseSize(currentAnimation->getPreviewModelID(), currentAnimation->getInitialSize());
					}
					else // Part transformation
					{
						_fe3d.modelEntity_setPartPosition(currentAnimation->getPreviewModelID(), partID, Vec3(0.0f));
						_fe3d.modelEntity_setPartRotationOrigin(currentAnimation->getPreviewModelID(), partID, Vec3(0.0f));
						_fe3d.modelEntity_setPartRotation(currentAnimation->getPreviewModelID(), partID, Vec3(0.0f));
						_fe3d.modelEntity_setPartSize(currentAnimation->getPreviewModelID(), partID, Vec3(1.0f));
					}
				}
			}

			// Hide preview model
			if (_fe3d.modelEntity_isExisting(currentAnimation->getPreviewModelID()))
			{
				_fe3d.modelEntity_setWireFramed(currentAnimation->getPreviewModelID(), false);
				_fe3d.modelEntity_setVisible(currentAnimation->getPreviewModelID(), false);
			}

			// Reset some values
			_currentAnimationID = "";
			_currentFrameIndex = 0;
			_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("animationID")->getEntityID(), false);
			_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextField("animationFrame")->getEntityID(), false);
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuMain");
			return;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("preview")->isHovered())
		{
			auto modelIDs = _modelEditor.getLoadedModelIDs();
			for (auto& ID : modelIDs) { ID = ID.substr(1); }
			_gui.getGlobalScreen()->createChoiceForm("modelList", "Select Model", Vec2(-0.5f, 0.1f), modelIDs);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("play")->isHovered())
		{
			// Reset preview model transformation
			for (const auto& partID : currentAnimation->getPartIDs())
			{
				if (partID.empty()) // Base transformation
				{
					_fe3d.modelEntity_setBasePosition(currentAnimation->getPreviewModelID(), Vec3(0.0f));
					_fe3d.modelEntity_setBaseRotationOrigin(currentAnimation->getPreviewModelID(), Vec3(0.0f));
					_fe3d.modelEntity_setBaseRotation(currentAnimation->getPreviewModelID(), Vec3(0.0f));
					_fe3d.modelEntity_setBaseSize(currentAnimation->getPreviewModelID(), currentAnimation->getInitialSize());
				}
				else // Part transformation
				{
					_fe3d.modelEntity_setPartPosition(currentAnimation->getPreviewModelID(), partID, Vec3(0.0f));
					_fe3d.modelEntity_setPartRotationOrigin(currentAnimation->getPreviewModelID(), partID, Vec3(0.0f));
					_fe3d.modelEntity_setPartRotation(currentAnimation->getPreviewModelID(), partID, Vec3(0.0f));
					_fe3d.modelEntity_setPartSize(currentAnimation->getPreviewModelID(), partID, Vec3(1.0f));
				}
			}

			// Start animation
			startAnimation(_currentAnimationID, currentAnimation->getPreviewModelID(), 0);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("stop")->isHovered())
		{
			// Stop animation
			stopAnimation(_currentAnimationID, currentAnimation->getPreviewModelID());

			// Reset preview model transformation
			_fe3d.modelEntity_setBaseSize(currentAnimation->getPreviewModelID(), currentAnimation->getInitialSize());
			for (const auto& partID : currentAnimation->getPartIDs())
			{
				if (partID.empty()) // Base transformation
				{
					_fe3d.modelEntity_setBasePosition(currentAnimation->getPreviewModelID(), Vec3(0.0f));
					_fe3d.modelEntity_setBaseRotationOrigin(currentAnimation->getPreviewModelID(), Vec3(0.0f));
					_fe3d.modelEntity_setBaseRotation(currentAnimation->getPreviewModelID(), Vec3(0.0f));
					_fe3d.modelEntity_setBaseSize(currentAnimation->getPreviewModelID(), currentAnimation->getInitialSize());
				}
				else // Part transformation
				{
					_fe3d.modelEntity_setPartPosition(currentAnimation->getPreviewModelID(), partID, Vec3(0.0f));
					_fe3d.modelEntity_setPartRotationOrigin(currentAnimation->getPreviewModelID(), partID, Vec3(0.0f));
					_fe3d.modelEntity_setPartRotation(currentAnimation->getPreviewModelID(), partID, Vec3(0.0f));
					_fe3d.modelEntity_setPartSize(currentAnimation->getPreviewModelID(), partID, Vec3(1.0f));
				}
			}
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("addFrame")->isHovered())
		{
			// Copy current frame
			auto lastFrameCopy = currentAnimation->getFrames()[_currentFrameIndex];

			// Check if model has multiple parts
			if (_fe3d.modelEntity_isExisting(currentAnimation->getPreviewModelID()) &&
				_fe3d.modelEntity_isMultiParted(currentAnimation->getPreviewModelID()))
			{
				// Check if only default frame exists
				if (currentAnimation->getFrames().size() == 1)
				{
					// Clear frame
					lastFrameCopy.clearParts();

					// Add default data for every model part
					for (auto partID : currentAnimation->getPartIDs())
					{
						lastFrameCopy.addPart(partID, Vec3(0.0f), Vec3(0.0f), Vec3(0.0f), AnimationSpeedType::LINEAR, TransformationType::MOVEMENT);
					}
				}
			}

			// Add copied frame
			auto frames = currentAnimation->getFrames();
			frames.insert((frames.begin() + _currentFrameIndex), lastFrameCopy);
			currentAnimation->setFrames(frames);
			_currentFrameIndex++;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			// First stop animation
			if (isAnimationStarted(_currentAnimationID, currentAnimation->getPreviewModelID()))
			{
				stopAnimation(_currentAnimationID, currentAnimation->getPreviewModelID());
			}

			// Go to next screen
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("animationEditorMenuFrame");
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			// Delete frame
			auto frames = currentAnimation->getFrames();
			frames.erase(frames.begin() + _currentFrameIndex);
			currentAnimation->setFrames(frames);

			// Correct index
			if (_currentFrameIndex == currentAnimation->getFrames().size())
			{
				_currentFrameIndex--;
			}
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("prev")->isHovered())
		{
			_currentFrameIndex--;
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("next")->isHovered())
		{
			_currentFrameIndex++;
		}

		// Update buttons hoverability
		bool isPlaying = (isAnimationExisting(_currentAnimationID) && isAnimationStarted(_currentAnimationID, currentAnimation->getPreviewModelID()));
		bool hasPreviewModel = _fe3d.modelEntity_isExisting(currentAnimation->getPreviewModelID());
		screen->getButton("preview")->setHoverable(!isPlaying);
		screen->getButton("play")->setHoverable(!isPlaying && hasPreviewModel && currentAnimation->getFrames().size() > 1);
		screen->getButton("stop")->setHoverable(isPlaying && hasPreviewModel);
		screen->getButton("addFrame")->setHoverable(currentAnimation->getFrames().size() < MAX_FRAME_COUNT && !isPlaying && hasPreviewModel);
		screen->getButton("edit")->setHoverable(_currentFrameIndex > 0 && !isPlaying);
		screen->getButton("delete")->setHoverable(currentAnimation->getFrames().size() > 1 && _currentFrameIndex > 0 && !isPlaying && hasPreviewModel);
		screen->getButton("prev")->setHoverable(_currentFrameIndex > 0 && !isPlaying);
		screen->getButton("next")->setHoverable(_currentFrameIndex < (currentAnimation->getFrames().size() - 1) && !isPlaying && hasPreviewModel);

		// Update frame index display
		if (!isPlaying)
		{
			_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextField("animationFrame")->getEntityID(), "Frame: " + to_string(_currentFrameIndex + 1), 0.025f);
		}

		// Update preview model visibility
		if (_fe3d.modelEntity_isExisting(currentAnimation->getPreviewModelID()))
		{
			_fe3d.modelEntity_setVisible(currentAnimation->getPreviewModelID(), !_gui.getGlobalScreen()->isChoiceFormExisting("modelList"));
		}

		// Get selected button ID
		string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("modelList");

		// Hide last model
		if (_hoveredModelID != "")
		{
			_fe3d.modelEntity_setVisible(_hoveredModelID, false);
		}

		// Check if model ID is hovered
		if (!selectedButtonID.empty())
		{
			// Set new hovered model
			_hoveredModelID = ("@" + selectedButtonID);

			// Check if LMB is pressed
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				// Check if parts are present
				bool hasAllParts = true;
				for (const auto& partID : currentAnimation->getPartIDs())
				{
					// Part cannot be empty
					if (!partID.empty())
					{
						hasAllParts = hasAllParts && _fe3d.modelEntity_hasPart(_hoveredModelID, partID);
					}
				}

				// Throw warning if necessary
				if (!hasAllParts)
				{
					Logger::throwWarning("Preview model does not have required animation parts!");
					return;
				}

				// Change values
				currentAnimation->setPreviewModelID(_hoveredModelID);
				currentAnimation->setInitialSize(_fe3d.modelEntity_getBaseSize(_hoveredModelID));

				// Check if first time choosing preview model
				if (currentAnimation->getFrames().empty())
				{
					// Create default frame
					AnimationFrame defaultFrame;

					// Add default part
					currentAnimation->addPart("", Vec3(0.0f), Vec3(0.0f), Vec3(0.0f));
					defaultFrame.addPart("", Vec3(0.0f), Vec3(0.0f), Vec3(0.0f), AnimationSpeedType::LINEAR, TransformationType::MOVEMENT);

					// Add custom parts
					auto partIDs = _fe3d.modelEntity_getPartIDs(_hoveredModelID);
					if (partIDs.size() > 1)
					{
						// Iterate through parts
						for (auto partID : partIDs)
						{
							// Add part to animation
							currentAnimation->addPart(partID, Vec3(0.0f), Vec3(0.0f), Vec3(0.0f));

							// Add part to frame
							defaultFrame.addPart(partID, Vec3(0.0f), Vec3(0.0f), Vec3(0.0f), AnimationSpeedType::LINEAR, TransformationType::MOVEMENT);
						}
					}

					// Add default frame to animation
					currentAnimation->addFrame(defaultFrame);
				}

				// Miscellaneous
				_gui.getGlobalScreen()->deleteChoiceForm("modelList");
				_hoveredModelID = "";
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("modelList")) // Cancelled choosing
		{
			_gui.getGlobalScreen()->deleteChoiceForm("modelList");
		}
		else
		{
			_hoveredModelID = "";
		}

		// Show hovered model
		if (_hoveredModelID != "")
		{
			_fe3d.modelEntity_setVisible(_hoveredModelID, true);
		}
	}
}