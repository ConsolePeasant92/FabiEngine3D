#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dAnimationFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if (functionName == "fe3d:model_start_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::INTEGER };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_animationEditor.startAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_is_animation_started")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _animationEditor.isAnimationStarted(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:model_is_animation_playing")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _animationEditor.isAnimationPlaying(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:model_is_animation_paused")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _animationEditor.isAnimationPaused(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:model_is_animation_fading")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				auto result = _animationEditor.isAnimationFading(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:model_pause_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_animationEditor.pauseAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_resume_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_animationEditor.resumeAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_fade_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::INTEGER };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_animationEditor.fadeAnimation(arguments[1].getString(), arguments[0].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_stop_animation")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				_animationEditor.stopAnimation(arguments[1].getString(), arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:model_set_animation_speed")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				// Retrieve animation data
				string errorMessage = "Tried to set animation speed with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if (animationData != nullptr)
				{
					animationData->speedMultiplier = arguments[2].getDecimal();
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
				}
			}
		}
	}
	else if (functionName == "fe3d:model_set_animation_autopaused")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				// Retrieve animation data
				string errorMessage = "Tried to set animation autopaused option with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if (animationData != nullptr)
				{
					animationData->isAutoPaused = arguments[2].getBoolean();
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
				}
			}
		}
	}
	else if (functionName == "fe3d:model_get_animation_speed")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation speed with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if (animationData != nullptr)
				{
					auto result = animationData->speedMultiplier;
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
				}
			}
		}
	}
	else if (functionName == "fe3d:model_is_animation_autopaused")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation autopause option with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);

				// Check if animation was found
				if (animationData != nullptr)
				{
					auto result = animationData->isAutoPaused;
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
				}
			}
		}
	}
	else if (functionName == "fe3d:model_get_animation_frame_index")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueAmount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing model ID
			if (_validateFe3dModelEntity(arguments[0].getString()))
			{
				// Retrieve animation data
				string errorMessage = "Tried to get animation frame index with ID \"" + arguments[1].getString() + "\" on model with ID \"" + arguments[0].getString() + "\": ";
				auto animationData = _animationEditor.getAnimationData(arguments[1].getString(), arguments[0].getString(), errorMessage);
				
				// Check if animation was found
				if (animationData != nullptr)
				{
					auto result = animationData->frameIndex;
					returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, static_cast<int>(result)));
				}
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute model functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:model` functionality as a networking server!");
	}

	return true;
}