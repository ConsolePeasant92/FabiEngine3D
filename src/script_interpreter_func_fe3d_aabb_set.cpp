#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAabbSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:aabb_place")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(_fe3d->aabb_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("AABB already exists");

				return true;
			}

			if(_validateFe3dAabb(args[1]->getString(), true))
			{
				_duplicator->copyEditorAabb(args[0]->getString(), ("@" + args[1]->getString()));

				_fe3d->aabb_setBasePosition(args[0]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_delete")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_duplicator->deleteCopiedAabb(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & aabbId : _fe3d->aabb_getIds())
			{
				if(aabbId[0] != '@')
				{
					if(_fe3d->aabb_getParentId(args[0]->getString()).empty())
					{
						_duplicator->deleteCopiedAabb(aabbId);
					}
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:aabb_set_min_clip_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_setMinClipPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_max_clip_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_setMaxClipPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_visible")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_setVisible(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_setBasePosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_size")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_setBaseSize(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_move")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_moveBase(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_scale")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_scaleBase(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_move_to")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_moveBaseTo(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()), args[4]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_scale_to")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_scaleBaseTo(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()), args[4]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_color")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_setColor(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_raycast_responsive")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_setRaycastResponsive(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_collision_responsive")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");

					return true;
				}

				_fe3d->aabb_setCollisionResponsive(args[0]->getString(), args[1]->getBoolean());

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
		_throwRuntimeError("cannot access `fe3d:aabb` functionality as a networking server");

		return true;
	}

	return true;
}