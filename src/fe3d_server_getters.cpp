#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::server_isRunning() const
{
	return _core->_networkServerAPI.isRunning();
}

const bool FabiEngine3D::server_isClientConnected(const string& username) const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to get client connection status: not running!");
		return false;
	}

	return _core->_networkServerAPI.isClientConnected(username);
}

const string FabiEngine3D::server_getNewClientIP() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to get new client IP: not running!");
		return "";
	}

	return _core->_networkServerAPI.getNewClientIP();
}

const string FabiEngine3D::server_getNewClientUsername() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to get new client username: not running!");
		return "";
	}

	return _core->_networkServerAPI.getNewClientUsername();
}

const string FabiEngine3D::server_getOldClientIP() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to get old client IP: not running!");
		return "";
	}

	return _core->_networkServerAPI.getOldClientIP();
}

const string FabiEngine3D::server_getOldClientUsername() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to get old client username: not running!");
		return "";
	}

	return _core->_networkServerAPI.getOldClientUsername();
}

const vector<NetworkClientMessage> FabiEngine3D::server_getPendingMessages() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to get pending messages: not running!");
		return {};
	}

	return _core->_networkServerAPI.getPendingMessages();
}

const vector<string> FabiEngine3D::server_getClientIPs() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to get client IPs: not running!");
		return {};
	}

	return _core->_networkServerAPI.getClientIPs();
}

const vector<string> FabiEngine3D::server_getClientUsernames() const
{
	if(!_core->_networkServerAPI.isRunning())
	{
		Logger::throwWarning("Networking server tried to get client usernames: not running!");
		return {};
	}

	return _core->_networkServerAPI.getClientUsernames();
}