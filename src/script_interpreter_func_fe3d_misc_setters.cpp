#include "script_interpreter.hpp"
#include "logger.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dMiscSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:application_pause")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:application_pause` functionality as a networking server!");
				return true;
			}

			// Pause engine
			_fe3d.application_pause();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:application_resume")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:application_resume` functionality as a networking server!");
				return true;
			}

			// Resume engine
			_fe3d.application_resume();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:application_stop")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(Config::getInst().isApplicationExported()) // Application preview
			{
				_fe3d.application_stop();
			}
			else // Engine preview
			{
				_mustStopApplication = true;
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:print")
	{
		if(_validateArgumentCount(arguments, 1))
		{
			// Determine which type of value to print
			if(arguments[0].getType() == SVT::STRING)
			{
				Logger::throwInfo(arguments[0].getString());
			}
			else if(arguments[0].getType() == SVT::DECIMAL)
			{
				string decimalString = to_string(arguments[0].getDecimal());
				Logger::throwInfo(decimalString.substr(0, decimalString.size() - 1));
			}
			else if(arguments[0].getType() == SVT::INTEGER)
			{
				Logger::throwInfo(to_string(arguments[0].getInteger()));
			}
			else if(arguments[0].getType() == SVT::BOOLEAN)
			{
				Logger::throwInfo(arguments[0].getBoolean() ? "true" : "false");
			}
			else
			{
				Logger::throwError("ScriptInterpreter::_executeFe3dMiscFunction");
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:cursor_set_visible")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as networking server!");
				return true;
			}

			// Set cursor visibility
			_fe3d.misc_setCursorVisible(arguments[0].getBoolean());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:cursor_center")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:cursor` functionality as networking server!");
				return true;
			}

			// Center cursor
			_fe3d.misc_centerCursor();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:timer_start")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.misc_startMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:timer_stop")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.misc_stopMillisecondTimer();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:wireframe_enable_rendering")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:wireframe` functionality as networking server!");
				return true;
			}

			// Enable wireframe rendering
			_fe3d.misc_enableWireframeRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:wireframe_disable_rendering")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:wireframe` functionality as networking server!");
				return true;
			}

			// Disable wireframe rendering
			_fe3d.misc_disableWireframeRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:aabbs_enable_rendering")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:aabbs` functionality as networking server!");
				return true;
			}

			// Enable AABB rendering
			_fe3d.misc_enableAabbFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:aabbs_disable_rendering")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:aabbs` functionality as networking server!");
				return true;
			}

			// Disable AABB rendering
			_fe3d.misc_disableAabbFrameRendering();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:time_interval")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto result = _fe3d.misc_checkInterval(arguments[0].getInteger());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:vsync_enable")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as networking server!");
				return true;
			}

			// Enable Vsync
			_fe3d.misc_enableVsync();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:vsync_disable")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Cannot execute when server is running
			if(_fe3d.server_isRunning())
			{
				_throwScriptError("cannot access `fe3d:vsync` functionality as networking server!");
				return true;
			}

			// Disable Vsync
			_fe3d.misc_disableVsync();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	return true;
}