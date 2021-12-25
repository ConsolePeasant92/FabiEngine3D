#include "script_interpreter.hpp"

#include <algorithm>

using std::clamp;

using SVT = ScriptValueType;

const vector<ScriptValue> ScriptInterpreter::_processMathFunctionCall(const string& scriptLine)
{
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

	if((openingParanthesisFound == scriptLine.end()) && (closingParanthesisFound == scriptLine.end()))
	{
		_throwScriptError("invalid '()' syntax!");
	}

	if(scriptLine.back() != ')')
	{
		_throwScriptError("function call must end with ')'!");
	}

	auto parenthesisIndex = static_cast<unsigned int>(distance(scriptLine.begin(), openingParanthesisFound));
	string argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1));
	argumentString.pop_back();
	auto args = _extractValuesFromListString(argumentString);

	if(_hasThrownError)
	{
		return {};
	}

	auto functionName = scriptLine.substr(0, parenthesisIndex);

	if(functionName == "math:tan")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			float angle = Math::convertToRadians(args[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, tan(angle)));
		}
	}
	else if(functionName == "math:sin")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			float angle = Math::convertToRadians(args[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, sin(angle)));
		}
	}
	else if(functionName == "math:cos")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			float angle = Math::convertToRadians(args[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, cos(angle)));
		}
	}
	else if(functionName == "math:atan")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto angle = atan(args[0].getDecimal());
			auto result = Math::convertToDegrees(angle);
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:asin")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto angle = asin(args[0].getDecimal());
			auto result = Math::convertToDegrees(angle);
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:acos")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto angle = acos(args[0].getDecimal());
			auto result = Math::convertToDegrees(angle);
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:atan2")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto angle = atan2(args[0].getDecimal(), args[1].getDecimal());
			auto result = Math::convertToDegrees(angle);
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:pow")
	{
		if(_validateArgumentCount(args, 2))
		{
			if(args[0].getType() == SVT::INTEGER && args[1].getType() == SVT::INTEGER)
			{
				auto result = static_cast<int>(pow(args[0].getInteger(), args[1].getInteger()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
			else if(args[0].getType() == SVT::DECIMAL && args[1].getType() == SVT::INTEGER)
			{
				auto result = static_cast<float>(pow(args[0].getDecimal(), args[1].getInteger()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("wrong argument type(s)!");
			}
		}
	}
	else if(functionName == "math:min")
	{
		if(_validateArgumentCount(args, 2))
		{
			if(args[0].getType() == SVT::INTEGER && args[1].getType() == SVT::INTEGER)
			{
				auto result = min(args[0].getInteger(), args[1].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
			else if(args[0].getType() == SVT::DECIMAL && args[1].getType() == SVT::DECIMAL)
			{
				auto result = min(args[0].getDecimal(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("wrong argument type(s)!");
			}
		}
	}
	else if(functionName == "math:max")
	{
		if(_validateArgumentCount(args, 2))
		{
			if(args[0].getType() == SVT::INTEGER && args[1].getType() == SVT::INTEGER)
			{
				auto result = max(args[0].getInteger(), args[1].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
			else if(args[0].getType() == SVT::DECIMAL && args[1].getType() == SVT::DECIMAL)
			{
				auto result = max(args[0].getDecimal(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("wrong argument type(s)!");
			}
		}
	}
	else if(functionName == "math:round")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, round(args[0].getDecimal())));
		}
	}
	else if(functionName == "math:floor")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, floor(args[0].getDecimal())));
		}
	}
	else if(functionName == "math:ceil")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, ceil(args[0].getDecimal())));
		}
	}
	else if(functionName == "math:clamp")
	{
		if(_validateArgumentCount(args, 3))
		{
			if(args[0].getType() == SVT::INTEGER && args[2].getType() == SVT::INTEGER && args[3].getType() == SVT::INTEGER)
			{
				auto result = clamp(args[0].getInteger(), args[1].getInteger(), args[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
			else if(args[0].getType() == SVT::DECIMAL && args[1].getType() == SVT::DECIMAL && args[2].getType() == SVT::DECIMAL)
			{
				auto result = clamp(args[0].getDecimal(), args[1].getDecimal(), args[2].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
			else
			{
				_throwScriptError("wrong argument type(s)!");
			}
		}
	}
	else if(functionName == "math:sqrt")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, sqrtf(args[0].getDecimal())));
		}
	}
	else if(functionName == "math:abs")
	{
		if(_validateArgumentCount(args, 1))
		{
			// Determine type of value
			if(args[0].getType() == SVT::INTEGER)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, abs(args[0].getInteger())));
			}
			else if(args[0].getType() == SVT::DECIMAL)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, fabsf(args[0].getDecimal())));
			}
			else
			{
				_throwScriptError("wrong argument type(s)!");
			}
		}
	}
	else if(functionName == "math:pi")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = Math::getPI();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:is_even")
	{
		auto types = {SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto result = (args[0].getInteger() % 2) == 0;
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "math:angle_difference")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto result = Math::calculateAngleDifference(args[0].getDecimal(), args[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:reference_angle")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto result = Math::calculateReferenceAngle(args[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "math:vector_distance")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			auto first = fvec3(args[0].getDecimal(), args[1].getDecimal(), args[2].getDecimal());
			auto second = fvec3(args[3].getDecimal(), args[4].getDecimal(), args[5].getDecimal());
			auto result = Math::calculateDistance(first, second);
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else
	{
		_throwScriptError("math function not existing!");
	}

	return returnValues;
}