#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSound3dGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:sound3d_is_existing")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			const auto result = _fe3d->sound3d_isExisting(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:sound3d_get_editor_id")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				const auto result = _duplicator->getEditorSound3dId(args[0]->getString()).substr(1);

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_find_ids")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			for(const auto & result : _fe3d->sound3d_getIds())
			{
				if(result[0] != '@')
				{
					if(args[0]->getString() == result.substr(0, args[0]->getString().size()))
					{
						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & result : _fe3d->sound3d_getIds())
			{
				if(result[0] != '@')
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_audio_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound3d_getAudioPath(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_is_started")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound3d_isStarted(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_is_paused")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				if(!_fe3d->sound3d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound3D is not started");

					return true;
				}

				const auto result = _fe3d->sound3d_isPaused(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_volume")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				if(!_fe3d->sound3d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound3D is not started");

					return true;
				}

				const auto result = _fe3d->sound3d_getVolume(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_left_intensity")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				if(!_fe3d->sound3d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound3D is not started");

					return true;
				}

				const auto result = _fe3d->sound3d_getLeftIntensity(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_right_intensity")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				if(!_fe3d->sound3d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound3D is not started");

					return true;
				}

				const auto result = _fe3d->sound3d_getRightIntensity(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_current_time")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				if(!_fe3d->sound3d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound3D is not started");

					return true;
				}

				const auto result = _fe3d->sound3d_getCurrentTime(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_started_count")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound3d_getStartedCount(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_is_device_connected")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->sound3d_isDeviceConnected();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:sound3d_get_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound3d_getPosition(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound3d_getPosition(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_position_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound3d_getPosition(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_max_volume")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound3d_getMaxVolume(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_max_distance")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound3d_getMaxDistance(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_get_play_count")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound3d_getPlayCount(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:sound3d` functionality as a networking server");

		return true;
	}

	return true;
}