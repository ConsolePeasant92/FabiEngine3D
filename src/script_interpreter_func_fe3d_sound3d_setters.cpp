#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSoundSetter3D(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:sound3d_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Temporary values
			string newID = arguments[0].getString();
			string previewID = arguments[1].getString();

			// @ sign is reserved
			if(newID[0] == '@')
			{
				_throwScriptError("new sound ID (\"" + arguments[0].getString() + "\") cannot start with '@'");
				return true;
			}

			// Check if sound already exists
			if(_fe3d.sound3D_isExisting(newID))
			{
				_throwScriptError("sound with ID \"" + newID + "\" already exists!");
				return true;
			}

			// Validate preview sound ID
			if(_validateFe3dSound3D("@" + previewID, true))
			{
				// Temporary values
				auto position = fvec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal());
				auto maxVolume = arguments[5].getDecimal();
				auto maxDistance = arguments[6].getDecimal();

				// Add sound
				_worldEditor.copyPreviewSound(newID, ("@" + previewID), position);
				_fe3d.sound3D_setMaxVolume(newID, maxVolume);
				_fe3d.sound3D_setMaxDistance(newID, maxDistance);

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_delete_all")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Iterate through sounds
			for(const auto& ID : _fe3d.sound3D_getAllIDs())
			{
				// @ sign is reserved
				if(ID[0] != '@')
				{
					_fe3d.sound3D_delete(ID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound3d_play")
	{
		auto types = {SVT::STRING, SVT::INTEGER, SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_play(arguments[0].getString(), arguments[1].getInteger(), arguments[2].getInteger(), false);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_play_forced")
	{
		auto types = {SVT::STRING, SVT::INTEGER, SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_play(arguments[0].getString(), arguments[1].getInteger(), arguments[2].getInteger(), true);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_pause")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_pause(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_pause_all")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.sound3D_pauseAll();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound3d_resume")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_resume(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_resume_all")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.sound3D_resumeAll();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound3d_stop")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_stop(arguments[0].getString(), arguments[1].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_stop_all")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			_fe3d.sound3D_stopAll();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound3d_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_setPosition(
					arguments[0].getString(),
					fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_move(
					arguments[0].getString(),
					fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_moveTo(
					arguments[0].getString(),
					fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()),
					arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_set_max_volume")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_setMaxVolume(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_set_max_distance")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dSound3D(arguments[0].getString(), false))
			{
				_fe3d.sound3D_setMaxDistance(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute sound functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:sound3d` functionality as networking server!");
	}

	return true;
}