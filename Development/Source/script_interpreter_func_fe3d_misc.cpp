#include "script_interpreter.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;

bool ScriptInterpreter::_executeFe3dMiscFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:application_pause")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute pausing functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:application_pause` as a networking server!");
				return true;
			}

			// Pause engine
			_fe3d.application_pause();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:application_resume")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute pausing functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:application_resume` as a networking server!");
				return true;
			}

			// Resume engine
			_fe3d.application_resume();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:application_stop")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			if (_fe3d.application_isExported()) // Application preview
			{
				_fe3d.application_stop();
			}
			else // Engine preview
			{
				_mustStopApplication = true;
			}
			
			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:print")
	{
		// Validate amount of arguments
		if (_validateListValueCount(arguments, 1))
		{
			// Determine which type of value to print
			if (arguments[0].getType() == ScriptValueType::VEC3)
			{
				Logger::throwInfo(_fe3d.misc_vec2str(arguments[0].getVec3()));
			}
			else if (arguments[0].getType() == ScriptValueType::STRING)
			{
				Logger::throwInfo(arguments[0].getString());
			}
			else if (arguments[0].getType() == ScriptValueType::DECIMAL)
			{
				string decimalString = to_string(arguments[0].getDecimal());
				Logger::throwInfo(decimalString.substr(0, decimalString.size() - 1));
			}
			else if (arguments[0].getType() == ScriptValueType::INTEGER)
			{
				Logger::throwInfo(to_string(arguments[0].getInteger()));
			}
			else if (arguments[0].getType() == ScriptValueType::BOOLEAN)
			{
				Logger::throwInfo(arguments[0].getBoolean() ? "true" : "false");
			}
			else
			{
				Logger::throwError("ScriptInterpreter::_executeFe3dMiscFunction");
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:cursor_set_visible")
	{
		auto types = { ScriptValueType::BOOLEAN };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as a networking server!");
				return true;
			}

			// Set cursor visibility
			_fe3d.misc_setCursorVisible(arguments[0].getBoolean());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:cursor_is_visible")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as a networking server!");
				return true;
			}

			// Return cursor visbility
			auto result = _fe3d.misc_isCursorVisible();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:cursor_center")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as a networking server!");
				return true;
			}

			// Center cursor
			_fe3d.misc_centerCursor();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:cursor_get_position_x")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as a networking server!");
				return true;
			}

			// Get cursor position X
			auto result = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPositionRelativeToViewport())).x;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, clamp(result, -1.0f, 1.0f)));
		}
	}
	else if (functionName == "fe3d:cursor_get_position_y")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute cursor functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as a networking server!");
				return true;
			}

			// Get cursor position Y
			auto result = _fe3d.misc_convertToNDC(_fe3d.misc_convertFromScreenCoords(_fe3d.misc_getCursorPositionRelativeToViewport())).y;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, clamp(result, -1.0f, 1.0f)));
		}
	}
	else if (functionName == "fe3d:window_get_width")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute window functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:window` functionality as a networking server!");
				return true;
			}

			// Get window width
			auto result = _fe3d.misc_getWindowSize().x;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
		}
	}
	else if (functionName == "fe3d:window_get_height")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute window functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:window` functionality as a networking server!");
				return true;
			}

			// Get window height
			auto result = _fe3d.misc_getWindowSize().y;
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
		}
	}
	else if (functionName == "fe3d:timer_start")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_startMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:timer_is_started")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.misc_isMillisecondTimerStarted();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:timer_stop")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.misc_stopMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:wireFrame_enable_rendering")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute wire frame functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:wireFrame` functionality as a networking server!");
				return true;
			}

			// Enable wire frame rendering
			_fe3d.misc_enableWireFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:wireFrame_disable_rendering")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute wire frame functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:wireFrame` functionality as a networking server!");
				return true;
			}

			// Disable wire frame rendering
			_fe3d.misc_disableWireFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:aabbs_enable_rendering")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute AABBs functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:aabbs` functionality as a networking server!");
				return true;
			}

			// Enable AABB rendering
			_fe3d.misc_enableAabbFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:aabbs_disable_rendering")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute AABBs functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:aabbs` functionality as a networking server!");
				return true;
			}

			// Disable AABB rendering
			_fe3d.misc_disableAabbFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:time_interval")
	{
		auto types = { ScriptValueType::INTEGER };

		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			auto result = _fe3d.misc_checkInterval(arguments[0].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:vsync_enable")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute Vsync functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as a networking server!");
				return true;
			}

			// Enable Vsync
			_fe3d.misc_enableVsync();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:vsync_disable")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute Vsync functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as a networking server!");
				return true;
			}

			// Disable Vsync
			_fe3d.misc_disableVsync();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:vynsc_is_enabled")
	{
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Cannot execute Vsync functionality when server is running
			if (_fe3d.networkServer_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as a networking server!");
				return true;
			}

			// Return Vsync status
			auto result = _fe3d.misc_isVsyncEnabled();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else
	{
		return false;
	}

	return true;
}