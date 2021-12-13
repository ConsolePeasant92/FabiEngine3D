#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCollisionSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:collision_enable_camera_terrain_response")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.collision_enableTerrainResponse(arguments[0].getDecimal(), arguments[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_disable_camera_terrain_response")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.collision_disableTerrainResponse();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_set_camera_box")
	{
		// Bottom top left right front back
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.collision_setCameraBox(
				arguments[0].getDecimal(), arguments[1].getDecimal(),
				arguments[2].getDecimal(), arguments[3].getDecimal(),
				arguments[4].getDecimal(), arguments[5].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_enable_camera_response")
	{
		auto types = {SVT::BOOLEAN, SVT::BOOLEAN, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			_fe3d.collision_enableCameraResponse(arguments[0].getBoolean(), arguments[1].getBoolean(), arguments[2].getBoolean());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_disable_camera_response")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.collision_disableCameraResponse();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute collision functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:collision` functionality as networking server!");
	}

	return true;
}