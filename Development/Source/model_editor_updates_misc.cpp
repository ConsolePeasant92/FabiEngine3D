#include "model_editor.hpp"

void ModelEditor::_updateCamera()
{
	if (_isEditorLoaded)
	{		
		// Check if third person view is enabled
		if (_fe3d.camera_isThirdPersonViewEnabled())
		{
			// Update distance scrolling
			auto scrollOffset = _fe3d.input_getMouseWheelY();
			auto cameraDistance = _fe3d.camera_getThirdPersonDistance();
			cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
			_fe3d.camera_setThirdPersonDistance(cameraDistance);

			// Update lookat position
			auto cameraLookat = _fe3d.camera_getThirdPersonLookat();
			if (_fe3d.input_isKeyDown(InputType::KEY_SPACE))
			{
				cameraLookat.y += CAMERA_LOOKAT_SPEED;
			}
			if (_fe3d.input_isKeyDown(InputType::KEY_LSHIFT))
			{
				cameraLookat.y -= CAMERA_LOOKAT_SPEED;
			}
			_fe3d.camera_setThirdPersonLookat(Vec3(cameraLookat.x, max(GRID_Y_OFFSET, cameraLookat.y), cameraLookat.z));

			// Hide cursor
			_fe3d.imageEntity_setVisible("@@cursor", false);

			// Disable shadows
			if (_fe3d.gfx_isShadowsEnabled())
			{
				_fe3d.gfx_disableShadows();
			}

			// Enable shadows
			const auto distance = _fe3d.camera_getThirdPersonDistance();
			_fe3d.gfx_enableShadows(Vec3(cameraLookat + Vec3(distance * 2.0f)),
				cameraLookat, distance * 4.0f, distance * 8.0f, 0.25f, false, false, 0);
		}

		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Check if allowed by editor
			if (!_isMovingToggled && !_isResizingToggled)
			{
				// Check if RMB pressed
				if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
				{
					// Check third person view status
					if (_fe3d.camera_isThirdPersonViewEnabled())
					{
						_fe3d.camera_disableThirdPersonView();
					}
					else
					{
						_fe3d.camera_enableThirdPersonView(
							_fe3d.camera_getThirdPersonYaw(),
							_fe3d.camera_getThirdPersonPitch(),
							_fe3d.camera_getThirdPersonDistance());
					}
				}
			}
		}

		// Disable third person view if necessary
		if (_fe3d.camera_isThirdPersonViewEnabled())
		{
			if (_gui.getGlobalScreen()->isFocused() || _isMovingToggled || _isResizingToggled)
			{
				_fe3d.camera_disableThirdPersonView();
			}
		}
	}
}

void ModelEditor::_updateMiscellaneous()
{
	if (_isEditorLoaded)
	{
		// Check if allowed by GUI
		if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
		{
			// Update reference model visibility
			if (_fe3d.input_isKeyPressed(InputType::KEY_R))
			{
				if (_fe3d.modelEntity_isVisible("@@cube"))
				{
					_fe3d.modelEntity_setVisible("@@cube", false);
				}
				else
				{
					_fe3d.modelEntity_setVisible("@@cube", true);
				}
			}

			// Update wire frame model rendering
			if (_fe3d.modelEntity_isExisting(_currentModelID))
			{
				if (_fe3d.input_isKeyPressed(InputType::KEY_F))
				{
					if (_fe3d.modelEntity_isWireFramed(_currentModelID))
					{
						_fe3d.modelEntity_setWireFramed(_currentModelID, false);
					}
					else
					{
						_fe3d.modelEntity_setWireFramed(_currentModelID, true);
					}
				}
			}

			// Update debug rendering
			if (_fe3d.input_isKeyPressed(InputType::KEY_H))
			{
				if (_fe3d.misc_isDebugRenderingEnabled())
				{
					_fe3d.misc_disableDebugRendering();
				}
				else
				{
					_fe3d.misc_enableDebugRendering();
				}
			}
		}
	}
}