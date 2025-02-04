#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSound2dGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:sound2d_is_existing")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			const auto result = _fe3d->sound2d_isExisting(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:sound2d_get_editor_id")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				const auto result = _duplicator->getEditorSound2dId(args[0]->getString()).substr(1);

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_find_ids")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			for(const auto & result : _fe3d->sound2d_getIds())
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
	else if(functionName == "fe3d:sound2d_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & result : _fe3d->sound2d_getIds())
			{
				if(result[0] != '@')
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:sound2d_get_audio_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound2d_getAudioPath(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_is_started")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_is_paused")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				if(!_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");

					return true;
				}

				const auto result = _fe3d->sound2d_isPaused(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_get_volume")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				if(!_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");

					return true;
				}

				const auto result = _fe3d->sound2d_getVolume(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_get_left_intensity")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				if(!_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");

					return true;
				}

				const auto result = _fe3d->sound2d_getLeftIntensity(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_get_right_intensity")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				if(!_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");

					return true;
				}

				const auto result = _fe3d->sound2d_getRightIntensity(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_get_current_time")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				if(!_fe3d->sound2d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");

					return true;
				}

				const auto result = _fe3d->sound2d_getCurrentTime(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_get_started_count")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound2d_getStartedCount(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_get_play_count")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->sound2d_getPlayCount(args[0]->getString(), args[0]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:sound2d_is_device_connected")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->sound2d_isDeviceConnected();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:sound2d` functionality as a networking server");

		return true;
	}

	return true;
}