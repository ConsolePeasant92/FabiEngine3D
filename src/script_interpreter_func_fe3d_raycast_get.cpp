#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dRaycastGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:raycast_get_cursor_ray_position_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayPosition().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_position_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayPosition().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_position_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayPosition().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayDirection().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayDirection().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayDirection().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_point_on_terrain_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getPointOnTerrain().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_point_on_terrain_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getPointOnTerrain().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_point_on_terrain_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getPointOnTerrain().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_is_point_on_terrain_valid")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_isPointOnTerrainValid();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_closest_model")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto aabbId = _fe3d->raycast_getClosestAabbId();

			string result = "";

			if(!aabbId.empty())
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::MODEL)
					{
						if(args[0]->getString().empty())
						{
							result = _fe3d->aabb_getParentId(aabbId);
						}
						else
						{
							const auto rawAabbId = aabbId.substr(string("model@").size());
							const auto subAabbId = rawAabbId.substr(rawAabbId.find('@'));

							if(subAabbId == args[1]->getString())
							{
								result = _fe3d->aabb_getParentId(aabbId);
							}
						}
					}
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_closest_quad3d")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto aabbId = _fe3d->raycast_getClosestAabbId();

			string result = "";

			if(!aabbId.empty())
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::QUAD3D)
					{
						result = _fe3d->aabb_getParentId(aabbId);
					}
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_closest_text3d")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto aabbId = _fe3d->raycast_getClosestAabbId();

			string result = "";

			if(!aabbId.empty())
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::TEXT3D)
					{
						result = _fe3d->aabb_getParentId(aabbId);
					}
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_models")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto aabbIds = _fe3d->raycast_getAabbIds();

			for(const auto & aabbId : aabbIds)
			{
				if(!aabbId.empty())
				{
					if(_fe3d->aabb_hasParent(aabbId))
					{
						if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::MODEL)
						{
							if(args[0]->getString().empty())
							{
								const auto result = _fe3d->aabb_getParentId(aabbId);

								returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
							}
							else
							{
								const auto rawAabbId = aabbId.substr(string("model@").size());
								const auto subAabbId = rawAabbId.substr(rawAabbId.find('@'));

								if(subAabbId == args[1]->getString())
								{
									const auto result = _fe3d->aabb_getParentId(aabbId);

									returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
								}
							}
						}
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_quad3ds")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto aabbIds = _fe3d->raycast_getAabbIds();

			for(const auto & aabbId : aabbIds)
			{
				if(!aabbId.empty())
				{
					if(_fe3d->aabb_hasParent(aabbId))
					{
						if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::QUAD3D)
						{
							const auto result = _fe3d->aabb_getParentId(aabbId);

							returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
						}
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_text3ds")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto aabbIds = _fe3d->raycast_getAabbIds();

			for(const auto & aabbId : aabbIds)
			{
				if(!aabbId.empty())
				{
					if(_fe3d->aabb_hasParent(aabbId))
					{
						if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::TEXT3D)
						{
							const auto result = _fe3d->aabb_getParentId(aabbId);

							returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
						}
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_distance_to_model")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				const auto fullAabbId = ("model@" + args[0]->getString() + "@" + args[1]->getString());

				if(_validateFe3dAabb(fullAabbId, false))
				{
					const auto result = _fe3d->raycast_getDistanceToAabb(fullAabbId);

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_distance_to_quad3d")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->raycast_getDistanceToAabb(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_distance_to_text3d")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->raycast_getDistanceToAabb(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:raycast` functionality as a networking server");

		return true;
	}

	return true;
}