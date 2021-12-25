#include "script_interpreter.hpp"

const bool ScriptInterpreter::_validateListIndex(const ScriptVariable& list, unsigned int index)
{
	if(list.getType() == ScriptVariableType::SINGLE)
	{
		_throwScriptError("variable \"" + list.getID() + "\" not of type LIST!");
		return false;
	}

	if(index < 0)
	{
		_throwScriptError("LIST index negative!");
		return false;
	}

	if(index >= list.getValueCount())
	{
		_throwScriptError("LIST index out of range!");
		return false;
	}

	return true;
}

const bool ScriptInterpreter::_validateArgumentCount(const vector<ScriptValue>& values, unsigned int count)
{
	if(values.size() == count) // Correct amount of arguments
	{
		return true;
	}
	else if(values.size() < count) // Not enough arguments
	{
		_throwScriptError("not enough arguments!");
		return false;
	}
	else // Too many arguments
	{
		_throwScriptError("too many arguments!");
		return false;
	}
}

const bool ScriptInterpreter::_validateArgumentTypes(const vector<ScriptValue>& values, const vector<ScriptValueType>& types)
{
	for(size_t i = 0; i < values.size(); i++)
	{
		// Compare value types
		if(values[i].getType() != types[i])
		{
			_throwScriptError("incorrect argument type!");
			return false;
		}
	}

	return true;
}

void ScriptInterpreter::_processListPush(const string& scriptLine)
{
	string nameString = "";
	for(const auto& c : scriptLine.substr(PUSHING_KEYWORD.size() + 1))
	{
		if(c == ' ')
		{
			break;
		}
		else
		{
			nameString += c;
		}
	}

	if(nameString.empty())
	{
		_throwScriptError("LIST name missing!");
		return;
	}

	auto minLineSize = (PUSHING_KEYWORD.size() + nameString.size() + 3);
	if(scriptLine.size() < minLineSize)
	{
		_throwScriptError("value missing!");
		return;
	}

	string valueString = scriptLine.substr(minLineSize - 1);

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("LIST not existing!");
		return;
	}

	auto& listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(listVariable.isConstant())
	{
		_throwScriptError("cannot push to constant LIST!");
		return;
	}

	if(_isListValue(valueString))
	{
		_throwScriptError("cannot push LIST to LIST!");
		return;
	}
	else if(_isStringValue(valueString))
	{
		// Remove the []
		valueString.erase(valueString.begin());
		valueString.pop_back();

		// Add value
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::STRING, valueString));
	}
	else if(_isDecimalValue(valueString))
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::DECIMAL, stof(_limitDecimalString(valueString))));
	}
	else if(_isIntegerValue(valueString))
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::INTEGER, stoi(_limitIntegerString(valueString))));
	}
	else if(_isBooleanValue(valueString))
	{
		listVariable.addValue(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, (valueString == "<true>")));
	}
	else
	{
		// Check if variable is not existing
		if(!_isLocalVariableExisting(valueString) && !_isGlobalVariableExisting(valueString))
		{
			_throwScriptError("invalid value!");
			return;
		}

		// Retrieve right variable
		const auto& rightVariable = (_isLocalVariableExisting(valueString) ? _getLocalVariable(valueString) : _getGlobalVariable(valueString));

		// Check if pushing list to list
		if(rightVariable.getType() == ScriptVariableType::MULTIPLE)
		{
			_throwScriptError("cannot push LIST to LIST!");
			return;
		}

		// Add value
		listVariable.addValue(rightVariable.getValue());
	}
}

void ScriptInterpreter::_processListPull(const string& scriptLine)
{
	string nameString = "";
	for(const auto& c : scriptLine.substr(PULLING_KEYWORD.size() + 1))
	{
		if(c == ' ')
		{
			break;
		}
		else
		{
			nameString += c;
		}
	}

	if(nameString.empty())
	{
		_throwScriptError("LIST name missing!");
		return;
	}

	if(scriptLine.size() < (PULLING_KEYWORD.size() + nameString.size() + 3))
	{
		_throwScriptError("LIST index missing!");
		return;
	}

	string indexString = scriptLine.substr(PULLING_KEYWORD.size() + nameString.size() + 2);

	if(!_isIntegerValue(indexString) && !_isLocalVariableExisting(indexString) && !_isGlobalVariableExisting(indexString))
	{
		_throwScriptError("invalid LIST index!");
		return;
	}

	if(!_isLocalVariableExisting(nameString) && !_isGlobalVariableExisting(nameString))
	{
		_throwScriptError("LIST not existing!");
		return;
	}

	auto& listVariable = (_isLocalVariableExisting(nameString) ? _getLocalVariable(nameString) : _getGlobalVariable(nameString));

	if(listVariable.isConstant())
	{
		_throwScriptError("cannot push to constant LIST!");
		return;
	}

	unsigned int index = -1;
	if(_isIntegerValue(indexString)) // Integer index
	{
		index = stoi(_limitIntegerString(indexString));
	}
	else // Variable index
	{
		// Retrieve index variable
		auto indexVariable = (_isLocalVariableExisting(indexString) ? _getLocalVariable(indexString) : _getGlobalVariable(indexString));

		// Check if not integer
		if(indexVariable.getValue().getType() != ScriptValueType::INTEGER)
		{
			_throwScriptError("LIST index not of type INT!");
			return;
		}

		// Set index
		index = indexVariable.getValue().getInteger();
	}

	if(!_validateListIndex(listVariable, index))
	{
		return;
	}

	listVariable.removeValue(index);
}