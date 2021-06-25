#include "script_interpreter.hpp"

bool ScriptInterpreter::_validateFe3dTerrainEntity()
{
	// Check if entity exists
	if (_fe3d.terrainEntity_getSelectedID().empty())
	{
		_throwScriptError("current scene has no terrain entity!");
		return false;
	}

	return true;
}

bool ScriptInterpreter::_executeFe3dTerrainEntityFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:terrain_get_pixel_height")
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate terrain existence
			if (_validateFe3dTerrainEntity())
			{
				float halfTerrainSize = _fe3d.terrainEntity_getSize(_fe3d.terrainEntity_getSelectedID()) / 2.0f;
				auto result = _fe3d.terrainEntity_getPixelHeight(_fe3d.terrainEntity_getSelectedID(), 
					arguments[0].getDecimal() + halfTerrainSize, arguments[1].getDecimal() + halfTerrainSize);
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:terrain_get_max_height")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrainEntity())
			{
				auto result = _fe3d.terrainEntity_getMaxHeight(_fe3d.terrainEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:terrain_get_size")
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrainEntity())
			{
				auto result = _fe3d.terrainEntity_getSize(_fe3d.terrainEntity_getSelectedID());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute terrain functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:terrain` functionality as a networking server!");
	}

	return true;
}