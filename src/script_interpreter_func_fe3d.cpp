#include "script_interpreter.hpp"

const vector<ScriptValue> ScriptInterpreter::_processEngineFunctionCall(const string& scriptLine)
{
	// Temporary values
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = find(scriptLine.begin(), scriptLine.end(), ')');

	// Check if function call has no opening & closing parentheses
	if((openingParanthesisFound == scriptLine.end()) && (closingParanthesisFound == scriptLine.end()))
	{
		_throwScriptError("invalid '()' syntax!");
	}

	// Check if function call does not end with a paranthesis
	if(scriptLine.back() != ')')
	{
		_throwScriptError("function call must end with ')'!");
	}

	// Extract arguments from argument string
	auto parenthesisIndex = static_cast<unsigned int>(distance(scriptLine.begin(), openingParanthesisFound));
	string argumentString = scriptLine.substr(static_cast<size_t>(parenthesisIndex + 1));
	argumentString.pop_back();
	auto arguments = _extractValuesFromListString(argumentString);

	// Check if argument extraction went well
	if(!_hasThrownError)
	{
		// Temporary values
		auto functionName = scriptLine.substr(0, parenthesisIndex);
		bool isExecuted = false;

		// Possibly execute FE3D function
		isExecuted = (isExecuted || _executeFe3dSkySetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSkyGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dTerrainSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dTerrainGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dWaterSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dWaterGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dModelSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dModelGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dBillboardSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dBillboardGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dAabbSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dAabbGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dPointlightSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dPointlightGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSpotlightSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSpotlightGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dReflectionSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dReflectionGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dImageSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dImageGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dTextSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dTextGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSoundSetterFunction2D(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSoundGetterFunction2D(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSoundSetterFunction3D(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dSoundGetterFunction3D(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dMusicSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dMusicGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dInputGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dCameraSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dCameraGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dCollisionSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dCollisionGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dRaycastSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dRaycastGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dGraphicsSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dGraphicsGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dLightingSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dLightingGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dServerSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dServerGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dClientSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dClientGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dFilesystemSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dFilesystemGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dWorldSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dWorldGetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dMiscSetterFunction(functionName, arguments, returnValues));
		isExecuted = (isExecuted || _executeFe3dMiscGetterFunction(functionName, arguments, returnValues));

		// Check if function call not existing
		if(!isExecuted)
		{
			_throwScriptError("fe3d function not existing!");

		}

		// Increase function calls
		_engineFunctionCallCount++;
	}

	return returnValues;
}