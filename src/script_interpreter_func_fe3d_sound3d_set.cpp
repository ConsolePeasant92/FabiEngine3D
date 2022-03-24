#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSound3dSetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:sound3d_place")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(_fe3d->sound3d_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("sound already exists");
				return true;
			}

			if(_validateFe3dSound3d(args[1]->getString(), true))
			{
				_fe3d->sound3d_create(args[0]->getString(), _fe3d->sound3d_getAudioPath("@" + args[1]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				_fe3d->sound3d_delete(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto& id : _fe3d->sound3d_getIds())
			{
				if(id[0] != '@')
				{
					_fe3d->sound3d_delete(id);
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sound3d_start")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->sound3d_isStarted(args[0]->getString(), args[1]->getInteger()))
			{
				_throwRuntimeError("sound2D is already started");
				return true;
			}
			if((args[1]->getInteger() == 0) || (args[1]->getInteger() < -1))
			{
				_throwRuntimeError("play count is invalid");
				return true;
			}

			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				_fe3d->sound3d_start(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_pause")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				if(!_fe3d->sound3d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");
					return true;
				}
				if(_fe3d->sound3d_isPaused(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is already paused");
					return true;
				}

				_fe3d->sound3d_pause(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_resume")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				if(!_fe3d->sound3d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");
					return true;
				}
				if(!_fe3d->sound3d_isPaused(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not paused");
					return true;
				}

				_fe3d->sound3d_resume(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_stop")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				if(!_fe3d->sound3d_isStarted(args[0]->getString(), args[1]->getInteger()))
				{
					_throwRuntimeError("sound2D is not started");
					return true;
				}

				_fe3d->sound3d_stop(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				_fe3d->sound3d_setPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				_fe3d->sound3d_move(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				_fe3d->sound3d_moveTo(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()), args[4]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_set_max_volume")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				_fe3d->sound3d_setMaxVolume(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sound3d_set_max_distance")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSound3d(args[0]->getString(), false))
			{
				_fe3d->sound3d_setMaxDistance(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
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