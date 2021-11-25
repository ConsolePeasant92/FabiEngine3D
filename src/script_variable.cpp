#include "script_variable.hpp"
#include "logger.hpp"

ScriptVariable::ScriptVariable(FabiEngine3D& fe3d, ScriptVariableScope scope, ScriptVariableType type,
							   const string& ID, bool constant, vector<ScriptValue> values)
	:
	_fe3d(fe3d),
	_scope(scope),
	_type(type),
	_ID(ID),
	_isConstant(constant)
{
	for(const auto& value : values)
	{
		_values.push_back(make_shared<ScriptValue>(value));
	}
}

const string& ScriptVariable::getID() const
{
	return _ID;
}

const ScriptVariableScope ScriptVariable::getScope() const
{
	return _scope;
}

const ScriptVariableType ScriptVariable::getType() const
{
	return _type;
}

const bool ScriptVariable::isConstant() const
{
	return _isConstant;
}

void ScriptVariable::setValues(vector<ScriptValue> values)
{
	_values.clear();

	for(const auto& value : values)
	{
		_values.push_back(make_shared<ScriptValue>(value));
	}
}

void ScriptVariable::setValue(ScriptValue value, unsigned int index)
{
	// Check if variable is immutable
	if(_isConstant)
	{
		Logger::throwError("ScriptVariable::changeValue");
	}

	// Delete old value
	_values.erase(_values.begin() + index);
	_values.insert(_values.begin() + index, make_shared<ScriptValue>(value));
}

void ScriptVariable::addValue(ScriptValue value)
{
	_values.push_back(make_shared<ScriptValue>(value));
}

void ScriptVariable::removeValue(unsigned int index)
{
	_values.erase(_values.begin() + index);
}

ScriptValue& ScriptVariable::getValue(unsigned int index) const
{
	// Validate index
	if(index >= _values.size())
	{
		Logger::throwError("ScriptVariable::getValue");
	}

	return *_values[index];
}

const vector<shared_ptr<ScriptValue>>& ScriptVariable::getValues() const
{
	return _values;
}

const unsigned int ScriptVariable::getValueCount() const
{
	return static_cast<unsigned int>(_values.size());
}