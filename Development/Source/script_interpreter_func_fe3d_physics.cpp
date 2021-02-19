#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dPhysicsFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:raycast_enable_terrain_positioning") // Enable raycasting
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL }; // Distance + precision

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.misc_enableTerrainRaycasting(arguments[0].getDecimal(), arguments[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:raycast_disable_terrain_positioning") // Disable raycasting
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.misc_disableTerrainRaycasting();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:raycast_get_vector") // Get the raycast vector
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrainEntity())
			{
				auto result = _fe3d.misc_getRaycastVector();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:raycast_get_position_on_terrain") // Get the cursor position on the terrain
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrainEntity())
			{
				auto result = _fe3d.misc_getRaycastPositionOnTerrain();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:raycast_is_position_on_terrain_valid") // Check if the position on the terrain is valid
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrainEntity())
			{
				auto result = _fe3d.misc_isRaycastPositionOnTerrainValid();
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:raycast_into_model") // Raycasting into multiple gameEntities
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::BOOLEAN }; // GameEntityID + aabbPartID + canBeOccluded

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			string result = "";

			// Find aabbEntity ID
			string searchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
			auto foundAabbID = _fe3d.collision_checkCursorInEntities(searchID, arguments[2].getBoolean()).first;

			// Retrieve bound gameEntity ID
			if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::GAME_ENTITY))
			{
				result = _fe3d.aabbEntity_getParentID(foundAabbID);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_models") // Raycasting into all gameEntities
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Temporary values
			string result = "";

			// Find aabbEntity ID
			auto foundAabbID = _fe3d.collision_checkCursorInAny().first;

			// Check if aabbEntity entity has a parent gameEntity
			if (!foundAabbID.empty() && _fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::GAME_ENTITY)
			{
				result = _fe3d.aabbEntity_getParentID(foundAabbID);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboard") // Raycasting into multiple billboardEntities
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN }; // BillboardEntityID + canBeOccluded

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			string result = "";

			// Find aabbEntity ID
			auto foundAabbID = _fe3d.collision_checkCursorInEntities(arguments[0].getString(), arguments[1].getBoolean()).first;

			// Retrieve bound billboardEntity ID
			if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
			{
				result = _fe3d.aabbEntity_getParentID(foundAabbID);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboards") // Raycasting into all billboardEntities
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Temporary values
			string result = "";

			// Find aabbEntity ID
			auto foundAabbID = _fe3d.collision_checkCursorInAny().first;

			// Check if aabbEntity entity has a parent billboardEntity
			if (!foundAabbID.empty() && _fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY)
			{
				result = _fe3d.aabbEntity_getParentID(foundAabbID);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_model_distance") // Raycasting into multiple gameEntities and retrieving the distance
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::BOOLEAN }; // GameEntityID + aabbPartID + canBeOccluded

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			string searchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
			auto intersection = _fe3d.collision_checkCursorInEntities(searchID, arguments[2].getBoolean());
			float result = -1.0f;

			// Retrieve bound gameEntity ID
			if (!intersection.first.empty() && (_fe3d.aabbEntity_getParentType(intersection.first) == AabbParentType::GAME_ENTITY))
			{
				result = intersection.second;
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_models_distance") // Raycasting into all gameEntities and retrieving the distance
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Find aabbEntity ID
			auto intersection = _fe3d.collision_checkCursorInAny();
			float result = -1.0f;

			// Check if aabbEntity entity has a parent gameEntity
			if (!intersection.first.empty() && _fe3d.aabbEntity_getParentType(intersection.first) == AabbParentType::GAME_ENTITY)
			{
				result = intersection.second;
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboard_distance") // Raycasting into multiple billboardEntities and retrieving the distance
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN }; // BillboardEntityID + canBeOccluded

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			auto intersection = _fe3d.collision_checkCursorInEntities(arguments[0].getString(), arguments[1].getBoolean());
			float result = -1.0f;

			// Retrieve bound billboardEntity ID
			if (!intersection.first.empty() && (_fe3d.aabbEntity_getParentType(intersection.first) == AabbParentType::BILLBOARD_ENTITY))
			{
				result = intersection.second;
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboards_distance") // Raycasting into all billboardEntities and retrieving the distance
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Find aabbEntity ID
			auto intersection = _fe3d.collision_checkCursorInAny();
			float result = -1.0f;

			// Check if aabbEntity entity has a parent billboardEntity
			if (!intersection.first.empty() && _fe3d.aabbEntity_getParentType(intersection.first) == AabbParentType::BILLBOARD_ENTITY)
			{
				result = intersection.second;
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:collision_enable_camera_terrain_response") // Enable collision response between camera & terrain
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL }; // CameraHeight + cameraSpeed

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.collision_enableCameraTerrainResponse(arguments[0].getDecimal(), arguments[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_disable_camera_terrain_response") // Disable collision response between camera & terrain
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.collision_disableCameraTerrainResponse();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_is_camera_under_terrain") // Check if camera is under terrain point
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			bool result = _fe3d.collision_checkCameraWithTerrain();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:collision_set_camera_box") // Save camera box size
	{
		// Bottom top left right front back
		auto types =
		{
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL,
			ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.collision_setCameraBoxSize(
				arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal(),
				arguments[3].getDecimal(), arguments[4].getDecimal(), arguments[5].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_enable_camera_aabb_response") // Enable collision response between camera & aabbEntity
	{
		// xResponse yResponse zResponse
		auto types =
		{
			ScriptValueType::BOOLEAN, ScriptValueType::BOOLEAN, ScriptValueType::BOOLEAN
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.collision_enableCameraResponse(arguments[0].getBoolean(), arguments[1].getBoolean(), arguments[2].getBoolean());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_disable_camera_aabb_response") // Disable collision response between camera & aabbEntity
	{
		// Validate arguments
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.collision_disableCameraResponse();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_model") // Check if camera collided with a gameEntity aabbEntity group
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::STRING }; // GameEntity ID + aabbEntity part ID + direction

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate direction
			if (arguments[2].getString() != "X" && arguments[2].getString() != "Y" && 
				arguments[2].getString() != "Z" && arguments[2].getString() != "")
			{
				_throwScriptError("Invalid direction argument!");
				return true;
			}

			// Temporary values
			string result = "";

			// Find aabbEntity
			string searchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
			auto foundAabbID = _fe3d.collision_checkCameraWithEntities(searchID);

			// Retrieve bound gameEntity ID
			if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::GAME_ENTITY))
			{
				// Check direction
				string searchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
				auto directionX = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::X);
				auto directionY = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::Y);
				auto directionZ = _fe3d.collision_checkCameraWithEntityDirection(foundAabbID, Direction::Z);
				if ((directionX && arguments[2].getString() == "X") ||
					(directionY && arguments[2].getString() == "Y") ||
					(directionZ && arguments[2].getString() == "Z") ||
					((directionX || directionY || directionZ) && arguments[2].getString().empty()))
				{
					result = _fe3d.aabbEntity_getParentID(foundAabbID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_models") // Check if camera collided with any gameEntity aabbEntity
	{
		auto types = { ScriptValueType::STRING }; // Direction

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate direction
			if (arguments[0].getString() != "X" && arguments[0].getString() != "Y" &&
				arguments[0].getString() != "Z" && arguments[0].getString() != "")
			{
				_throwScriptError("Invalid direction argument!");
				return true;
			}

			// Temporary values
			string result = "";

			// Find aabbEntity
			auto foundAabbID = _fe3d.collision_checkCameraWithAny();

			// Retrieve bound gameEntity ID
			if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::GAME_ENTITY))
			{
				// Check direction
				auto directionX = _fe3d.collision_checkCameraWithAnyDirection(Direction::X);
				auto directionY = _fe3d.collision_checkCameraWithAnyDirection(Direction::Y);
				auto directionZ = _fe3d.collision_checkCameraWithAnyDirection(Direction::Z);
				if ((directionX && arguments[0].getString() == "X") ||
					(directionY && arguments[0].getString() == "Y") ||
					(directionZ && arguments[0].getString() == "Z") ||
					((directionX || directionY || directionZ) && arguments[0].getString().empty()))
				{
					result = _fe3d.aabbEntity_getParentID(foundAabbID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_camera_aabb") // Check if camera collided with a specific aabbEntity
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING }; // aabbEntity ID + Direction

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate direction
			if (arguments[1].getString() != "X" && arguments[1].getString() != "Y" && 
				arguments[1].getString() != "Z" && arguments[1].getString() != "")
			{
				_throwScriptError("Invalid direction argument!");
				return true;
			}

			// Validate existing aabbEntity ID
			if (_validateFe3dAabbEntity(arguments[0].getString()))
			{
				// Temporary values
				bool result = false;

				// Check if requested aabbEntity is existing
				if (_fe3d.aabbEntity_isExisting(arguments[0].getString()))
				{
					// Check if requested aabbEntity has no parent
					if (_fe3d.aabbEntity_getParentType(arguments[0].getString()) == AabbParentType::NONE)
					{
						// Check direction
						auto directionX = _fe3d.collision_checkCameraWithEntityDirection(arguments[0].getString(), Direction::X);
						auto directionY = _fe3d.collision_checkCameraWithEntityDirection(arguments[0].getString(), Direction::Y);
						auto directionZ = _fe3d.collision_checkCameraWithEntityDirection(arguments[0].getString(), Direction::Z);
						if ((directionX && arguments[1].getString() == "X") ||
							(directionY && arguments[1].getString() == "Y") ||
							(directionZ && arguments[1].getString() == "Z") ||
							((directionX || directionY || directionZ) && arguments[1].getString().empty()))
						{
							result = true;
						}
					}
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:collision_check_camera_aabbs") // Check if camera collided with any aabbEntity
	{
		auto types = { ScriptValueType::STRING }; // Direction

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Validate direction
			if (arguments[0].getString() != "X" && arguments[0].getString() != "Y" &&
				arguments[0].getString() != "Z" && arguments[0].getString() != "")
			{
				_throwScriptError("Invalid direction argument!");
				return true;
			}

			// Temporary values
			bool result = false;

			// Find aabbEntity
			auto foundAabbID = _fe3d.collision_checkCameraWithAny();

			// Check if found and requested aabbEntity has no parent
			if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::NONE))
			{
				// Check direction
				auto directionX = _fe3d.collision_checkCameraWithAnyDirection(Direction::X);
				auto directionY = _fe3d.collision_checkCameraWithAnyDirection(Direction::Y);
				auto directionZ = _fe3d.collision_checkCameraWithAnyDirection(Direction::Z);
				if ((directionX && arguments[0].getString() == "X") ||
					(directionY && arguments[0].getString() == "Y") ||
					(directionZ && arguments[0].getString() == "Z") ||
					((directionX || directionY || directionZ) && arguments[0].getString().empty()))
				{
					result = true;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:collision_check_model_models") // Check if gameEntity aabbEntity collided with another gameEntity aabbEntity
	{
		auto types = 
		{ 
			ScriptValueType::STRING, ScriptValueType::STRING, // GameEntity ID + aabbEntity part ID
			ScriptValueType::STRING, ScriptValueType::STRING  // GameEntity ID + aabbEntity part ID
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			string result = "";

			// Check if no aabbEntity part is specified
			if (arguments[1].getString().empty())
			{
				// Get part IDs
				for (auto& selfSearchID : _fe3d.aabbEntity_getBoundIDs(arguments[0].getString(), true, false))
				{
					// Find aabbEntity ID
					string otherSearchID = arguments[2].getString() + (!arguments[3].getString().empty() ? ("_" + arguments[3].getString()) : "");
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, otherSearchID);

					// Retrieve bound gameEntity ID
					if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::GAME_ENTITY))
					{
						result = foundAabbID;
						break;
					}
				}
			}
			else
			{
				// Check if self aabbEntity entity exists
				string selfSearchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
				if (!_fe3d.aabbEntity_isExisting(selfSearchID))
				{
					_throwScriptError("Requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				string otherSearchID = arguments[2].getString() + (!arguments[3].getString().empty() ? ("_" + arguments[3].getString()) : "");
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, otherSearchID);

				// Retrieve bound gameEntity ID
				if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::GAME_ENTITY))
				{
					result = foundAabbID;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_model_billboards") // Check if gameEntity aabbEntity collided with another billboardEntity aabbEntity
	{
		auto types =
		{
			ScriptValueType::STRING, ScriptValueType::STRING, // GameEntity ID + aabbEntity part ID
			ScriptValueType::STRING // BillboardEntity ID
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			string result = "";

			// Check if no aabbEntity part is specified
			if (arguments[1].getString().empty())
			{
				// Get part IDs
				for (auto& selfSearchID : _fe3d.aabbEntity_getBoundIDs(arguments[0].getString(), false, true))
				{
					// Find aabbEntity ID
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

					// Retrieve bound gameEntity ID
					if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
					{
						result = foundAabbID;
						break;
					}
				}
			}
			else
			{
				// Check if self aabbEntity entity exists
				string selfSearchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
				if (!_fe3d.aabbEntity_isExisting(selfSearchID))
				{
					_throwScriptError("Requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

				// Retrieve bound gameEntity ID
				if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
				{
					result = foundAabbID;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else if (functionName == "fe3d:collision_check_model_aabbs") // Check if gameEntity aabbEntity collided with another AABB
	{
		auto types =
		{
			ScriptValueType::STRING, ScriptValueType::STRING, // GameEntity ID + aabbEntity part ID
			ScriptValueType::STRING // aabbEntity ID
		};

		// Validate arguments
		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			string result = "";

			// Check if no aabbEntity part is specified
			if (arguments[1].getString().empty())
			{
				// Get part IDs
				for (auto& selfSearchID : _fe3d.aabbEntity_getBoundIDs(arguments[0].getString(), true, false))
				{
					// Find aabbEntity ID
					auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

					// Check if found
					if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::NONE))
					{
						result = foundAabbID;
						break;
					}
				}
			}
			else
			{
				// Check if self aabbEntity entity exists
				string selfSearchID = arguments[0].getString() + (!arguments[1].getString().empty() ? ("_" + arguments[1].getString()) : "");
				if (!_fe3d.aabbEntity_isExisting(selfSearchID))
				{
					_throwScriptError("Requested model AABB with ID \"" + selfSearchID + "\" does not exist!");
					return true;
				}

				// Find aabbEntity ID
				auto foundAabbID = _fe3d.collision_checkEntityWithEntities(selfSearchID, arguments[2].getString());

				// Check if found
				if (!foundAabbID.empty() && (_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::NONE))
				{
					result = foundAabbID;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
		}
	}
	else
	{
		return false;
	}

	return true;
}