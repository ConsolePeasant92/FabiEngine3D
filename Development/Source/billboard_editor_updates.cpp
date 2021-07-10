#include "billboard_editor.hpp"
#include "logger.hpp"

#include <algorithm>

void BillboardEditor::update()
{
	_updateBillboardManagement();
	_updateBillboardCreation();
	_updateBillboardChoosing();
	_updateBillboardEditing();
	_updateBillboardRemoval();
	_updateCamera();
	_updateMiscellaneous();
}

void BillboardEditor::_updateBillboardManagement()
{
	if (_isEditorLoaded)
	{
		// Temporary values
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();
		
		// GUI management
		if (screen->getID() == "billboardEditorMenuMain")
		{
			// Check if input received
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused())) // Back button
				{
					_gui.getGlobalScreen()->addAnswerForm("exit", "Save Changes?", Vec2(0.0f, 0.25f));
				}
				else if (screen->getButton("addBillboard")->isHovered()) // Add billboard button
				{
					_gui.getGlobalScreen()->addValueForm("newBillboardName", "New Billboard Name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
					_isCreatingBillboard = true;
				}
				else if (screen->getButton("editBillboard")->isHovered()) // Edit billboard button
				{
					_isChoosingBillboard = true;
					_isEditingBillboard = true;
					auto IDs = getLoadedBillboardIDs();
					for (auto& name : IDs) { name = name.substr(1); }
					_gui.getGlobalScreen()->addChoiceForm("billboards", "Select Billboard", Vec2(-0.4f, 0.1f), IDs);
				}
				else if (screen->getButton("deleteBillboard")->isHovered()) // Delete billboard button
				{
					_isChoosingBillboard = true;
					_isRemovingBillboard = true;
					auto IDs = getLoadedBillboardIDs();
					for (auto& name : IDs) { name = name.substr(1); }
					_gui.getGlobalScreen()->addChoiceForm("billboards", "Select Billboard", Vec2(-0.4f, 0.1f), IDs);
				}
			}

			// Check if user wants to save changes
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exit"))
			{
				saveBillboardEntitiesToFile();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
				unload();
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("exit"))
			{
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
				unload();
			}
		}
	}
}

void BillboardEditor::_updateBillboardCreation()
{
	if (_isEditorLoaded)
	{
		if (_isCreatingBillboard)
		{
			string newBillboardName = "";

			// Check if user filled in a new name
			if (_gui.getGlobalScreen()->checkValueForm("newBillboardName", newBillboardName, { _currentBillboardID }))
			{
				// @ sign not allowed
				if (newBillboardName.find('@') == string::npos)
				{
					// Spaces not allowed
					if (newBillboardName.find(' ') == string::npos)
					{
						// Add @ sign to new name
						newBillboardName = "@" + newBillboardName;

						// Check if name already exists
						if (std::find(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end(), newBillboardName) == _loadedBillboardIDs.end()) // If name not existing yet
						{
							// Go to editor
							_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");

							// Select billboard
							_currentBillboardID = newBillboardName;
							_loadedBillboardIDs.push_back(newBillboardName);

							// Miscellaneous
							_fe3d.billboardEntity_add(newBillboardName, Vec3(1.0f),	BILLBOARD_POSITION, Vec3(0.0f), Vec2(1.0f), false, false);
							_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID(), "Billboard: " +
								_currentBillboardID.substr(1), 0.025f);
							_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID(), true);
							_isCreatingBillboard = false;
							_isEditingBillboard = true;
						}
						else // Name already exists
						{
							Logger::throwWarning("Billboard name \"" + newBillboardName.substr(1) + "\" already exists!");
						}
					}
					else
					{
						Logger::throwWarning("Billboard name cannot contain any spaces!");
					}
				}
				else
				{
					Logger::throwWarning("Billboard name cannot contain '@'!");
				}
			}
		}
	}
}

void BillboardEditor::_updateBillboardChoosing()
{
	if (_isEditorLoaded)
	{
		if (_isChoosingBillboard)
		{
			// Get selected button ID
			string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("billboards");

			// Hide last billboard
			if (_hoveredBillboardID != "")
			{
				_fe3d.billboardEntity_setVisible(_hoveredBillboardID, false);
			}

			// Check if a billboard name is hovered
			if (selectedButtonID != "")
			{
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT)) // LMB pressed
				{
					// Select billboard
					_currentBillboardID = "@" + selectedButtonID;
					_hoveredBillboardID = "";

					// Go to editor
					if (_isEditingBillboard)
					{
						_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuChoice");
						_fe3d.textEntity_setTextContent(_gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID(), "Billboard: " +
							_currentBillboardID.substr(1), 0.025f);
						_fe3d.textEntity_setVisible(_gui.getGlobalScreen()->getTextfield("selectedBillboardName")->getEntityID(), true);
					}

					// Miscellaneous
					_fe3d.billboardEntity_setVisible(_currentBillboardID, true);
					_gui.getGlobalScreen()->removeChoiceForm("billboards");
					_isChoosingBillboard = false;
				}
				else
				{
					// Set new hovered billboard
					_hoveredBillboardID = "@" + selectedButtonID;
				}
			}
			else if (_gui.getGlobalScreen()->isChoiceFormCancelled("billboards")) // Cancelled choosing
			{
				_isChoosingBillboard = false;
				_isEditingBillboard = false;
				_isRemovingBillboard = false;
				_gui.getGlobalScreen()->removeChoiceForm("billboards");
			}
			else // Nothing hovered
			{
				_hoveredBillboardID = "";
			}

			// Show hovered billboard
			if (_hoveredBillboardID != "")
			{
				_fe3d.billboardEntity_setVisible(_hoveredBillboardID, true);
			}
		}
	}
}

void BillboardEditor::_updateBillboardRemoval()
{
	if (_isEditorLoaded)
	{
		if (_isRemovingBillboard && _currentBillboardID != "")
		{
			_gui.getGlobalScreen()->addAnswerForm("removeBillboard", "Are you sure?", Vec2(0.0f, 0.25f));

			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("removeBillboard"))
			{
				// Go to main screen
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("billboardEditorMenuMain");

				// Delete billboard
				_fe3d.billboardEntity_delete(_currentBillboardID);
				_loadedBillboardIDs.erase(std::remove(_loadedBillboardIDs.begin(), _loadedBillboardIDs.end(), _currentBillboardID), _loadedBillboardIDs.end());
				_currentBillboardID = "";

				// Miscellaneous
				_gui.getGlobalScreen()->removeAnswerForm("removeBillboard");
				_isRemovingBillboard = false;
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("removeBillboard"))
			{
				_fe3d.billboardEntity_setVisible(_currentBillboardID, false);
				_isRemovingBillboard = false;
				_currentBillboardID = "";
			}
		}
	}
}

void BillboardEditor::_updateCamera()
{
	if (_isEditorLoaded)
	{
		// Check if a billboard is active
		if ((_currentBillboardID != "") || (_hoveredBillboardID != ""))
		{
			// Temporary values
			Vec2 billboardSize = _fe3d.billboardEntity_getSize((_currentBillboardID != "") ? _currentBillboardID : _hoveredBillboardID);
			float cameraDistance = (std::max(billboardSize.x, billboardSize.y));
			float cameraHeight = BILLBOARD_POSITION.y + (billboardSize.y / 2.0f);

			// Get scroll wheel input
			if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
			{
				float rotationAcceleration = static_cast<float>(_fe3d.input_getMouseWheelY()) / SCROLL_WHEEL_DIVIDER;
				_cameraAcceleration += rotationAcceleration;
			}
			_cameraAcceleration *= 0.975f;
			_totalCameraRotation += _cameraAcceleration;

			// Calculate new camera position
			float x = cameraDistance * sin(_totalCameraRotation);
			float y = cameraHeight;
			float z = cameraDistance * cos(_totalCameraRotation);

			// Update camera position
			_fe3d.camera_setPosition(Vec3(x, y, z));

			// Update camera lookat position
			Vec3 cameraLookatPosition = Vec3(0.0f, cameraHeight, 0.0f);
			_fe3d.camera_setThirdPersonLookat(cameraLookatPosition);

			// Disable shadows
			if (_fe3d.gfx_isShadowsEnabled())
			{
				_fe3d.gfx_disableShadows();
			}

			// Enable shadows
			_fe3d.gfx_enableShadows(Vec3(cameraLookatPosition + Vec3(cameraDistance * 2.0f)),
				cameraLookatPosition, cameraDistance * 4.0f, cameraDistance * 8.0f, 0.5f, false, false, 0);
		}
		else
		{
			// Set default camera view
			_fe3d.camera_setPosition(CAMERA_POSITION);
			_fe3d.camera_setThirdPersonLookat(BILLBOARD_POSITION);
			_totalCameraRotation = 0.0f;
			_cameraAcceleration = 0.0f;

			// Disable shadows
			if (_fe3d.gfx_isShadowsEnabled())
			{
				_fe3d.gfx_disableShadows(true);
			}
		}
	}
}