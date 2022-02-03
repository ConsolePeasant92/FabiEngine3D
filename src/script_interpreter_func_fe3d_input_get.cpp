#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dInputGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:input_is_key_down")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateKeyInputString(args[0]->getString()))
			{
				const auto result = _fe3d->input_isKeyDown(KEY_INPUT_STRING_MAP.at(args[0]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_is_key_pressed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateKeyInputString(args[0]->getString()))
			{
				const auto result = _fe3d->input_isKeyPressed(KEY_INPUT_STRING_MAP.at(args[0]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_is_mouse_down")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateMouseInputString(args[0]->getString()))
			{
				const auto result = _fe3d->input_isMouseDown(MOUSE_INPUT_STRING_MAP.at(args[0]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_is_mouse_pressed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateMouseInputString(args[0]->getString()))
			{
				const auto result = _fe3d->input_isMousePressed(MOUSE_INPUT_STRING_MAP.at(args[0]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:input_get_mousewheel_direction")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->input_getMouseWheelY();

			returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:input` functionality as networking server");
		return true;
	}

	return true;
}