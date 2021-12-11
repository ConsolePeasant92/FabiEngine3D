#include "water_editor.hpp"
#include "logger.hpp"

void WaterEditor::_updateCamera()
{
	// Check if third person view is enabled
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		// Update distance scrolling
		auto scrollOffset = _fe3d.input_getMouseWheelY();
		auto cameraDistance = _fe3d.camera_getThirdPersonDistance();
		cameraDistance = max(MIN_CAMERA_DISTANCE, cameraDistance - (static_cast<float>(scrollOffset) * CAMERA_DISTANCE_SPEED));
		_fe3d.camera_setThirdPersonDistance(cameraDistance);

		// Hide cursor
		_fe3d.image_setVisible("@@cursor", false);
	}

	// Check if allowed by GUI
	if(!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Check if RMB pressed
		if(_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_RIGHT))
		{
			// Check third person view status
			if(_fe3d.camera_isThirdPersonViewEnabled())
			{
				_fe3d.camera_disableThirdPersonView();
			}
			else
			{
				_fe3d.camera_enableThirdPersonView(_fe3d.camera_getThirdPersonYaw(), _fe3d.camera_getThirdPersonPitch());
			}
		}
	}

	// Disable third person view if necessary
	if(_fe3d.camera_isThirdPersonViewEnabled())
	{
		if(_gui.getGlobalScreen()->isFocused())
		{
			_fe3d.camera_disableThirdPersonView();
		}
	}
}

void WaterEditor::_updateMiscellaneous()
{
	// Check if allowed by GUI
	if(!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
	{
		// Update reference model visibility
		if(_fe3d.input_isKeyPressed(InputType::KEY_R))
		{
			if(_fe3d.model_isVisible("@@box"))
			{
				_fe3d.model_setVisible("@@box", false);
			}
			else
			{
				_fe3d.model_setVisible("@@box", true);
			}
		}

		// Update wireframe rendering
		if(_fe3d.water_isExisting(_currentWaterID))
		{
			if(_fe3d.input_isKeyPressed(InputType::KEY_F))
			{
				if(_fe3d.water_isWireframed(_currentWaterID))
				{
					_fe3d.water_setWireframed(_currentWaterID, false);
				}
				else
				{
					_fe3d.water_setWireframed(_currentWaterID, true);
				}
			}
		}

		// Update debug rendering
		if(_fe3d.input_isKeyPressed(InputType::KEY_H))
		{
			if(_fe3d.misc_isDebugRenderingEnabled())
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