#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dClientGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:client_is_valid_server_ip")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto result = _fe3d.client_isValidServerIP(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:client_is_running")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.client_isRunning();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:client_is_connecting")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.client_isConnecting();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:client_is_connected")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.client_isConnected();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:client_is_accepted")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.client_isAccepted();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:client_get_pending_protocols")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto messages = _fe3d.client_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, string((message.getProtocol() == NetworkProtocol::TCP) ? "TCP" : "UDP")));
			}
		}
	}
	else if(functionName == "fe3d:client_get_pending_contents")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto messages = _fe3d.client_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, message.getContent()));
			}
		}
	}
	else if(functionName == "fe3d:client_get_ping_latency")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.client_getPingLatency();
			returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
		}
	}
	else if(functionName == "fe3d:client_get_server_ip")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.client_getServerIP();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:client_get_username")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.client_getUsername();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:client` functionality as networking server!");
	}

	return true;
}