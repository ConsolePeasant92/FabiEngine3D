#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dServerGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:server_is_running")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.server_isRunning();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:server_is_client_connected")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			auto result = _fe3d.server_isClientConnected(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:server_get_new_ip")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto IP = _fe3d.server_getNewClientIP();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, IP));
		}
	}
	else if(functionName == "fe3d:server_get_new_username")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto username = _fe3d.server_getNewClientUsername();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, username));
		}
	}
	else if(functionName == "fe3d:server_get_old_ip")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto IP = _fe3d.server_getOldClientIP();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, IP));
		}
	}
	else if(functionName == "fe3d:server_get_old_username")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto username = _fe3d.server_getOldClientUsername();
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, username));
		}
	}
	else if(functionName == "fe3d:server_get_connected_ips")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto IPs = _fe3d.server_getClientIPs();
			for(const auto& IP : IPs)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, IP));
			}
		}
	}
	else if(functionName == "fe3d:server_get_connected_usernames")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto usernames = _fe3d.server_getClientUsernames();
			for(const auto& username : usernames)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, username));
			}
		}
	}
	else if(functionName == "fe3d:server_get_pending_protocols")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			const auto& messages = _fe3d.server_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, string((message.getProtocol() == NetworkProtocol::TCP) ? "TCP" : "UDP")));
			}
		}
	}
	else if(functionName == "fe3d:server_get_pending_usernames")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			const auto& messages = _fe3d.server_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, message.getUsername()));
			}
		}
	}
	else if(functionName == "fe3d:server_get_pending_contents")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			const auto& messages = _fe3d.server_getPendingMessages();
			for(const auto& message : messages)
			{
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, message.getContent()));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute server functionality when client is running
	if(_fe3d.client_isRunning())
	{
		_throwScriptError("cannot access `fe3d:server` functionality as networking client!");
	}

	return true;
}