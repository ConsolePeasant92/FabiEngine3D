#include "networking_server.hpp"

const bool NetworkingServer::isRunning() const
{
	return _isRunning;
}

const bool NetworkingServer::isClientConnected(const string & username) const
{
	for(int index = 0; index < static_cast<int>(_clientUsernames.size()); index++)
	{
		if(!_clientUsernames[index].empty())
		{
			if(username == _clientUsernames[index])
			{
				return true;
			}
		}
	}

	return false;
}

const string NetworkingServer::getNewClientIp() const
{
	return _newClientIp;
}

const string NetworkingServer::getNewClientUsername() const
{
	return _newClientUsername;
}

const string NetworkingServer::getOldClientIp() const
{
	if(_oldClientIps.empty())
	{
		return "";
	}
	else
	{
		return _oldClientIps[0];
	}
}

const string NetworkingServer::getOldClientUsername() const
{
	if(_oldClientUsernames.empty())
	{
		return "";
	}
	else
	{
		return _oldClientUsernames[0];
	}
}

const vector<NetworkingClientMessage> & NetworkingServer::getPendingMessages() const
{
	return _pendingMessages;
}

const vector<string> NetworkingServer::getClientIps() const
{
	vector<string> result = {};

	for(int index = 0; index < static_cast<int>(_clientIps.size()); index++)
	{
		if(!_clientUsernames[index].empty())
		{
			result.push_back(_clientIps[index]);
		}
	}

	return result;
}

const vector<string> NetworkingServer::getClientUsernames() const
{
	vector<string> clientUsernames = {};

	for(int index = 0; index < static_cast<int>(_clientUsernames.size()); index++)
	{
		if(!_clientUsernames[index].empty())
		{
			clientUsernames.push_back(_clientUsernames[index]);
		}
	}

	return clientUsernames;
}

void NetworkingServer::sendTcpMessageToClient(const string & username, const string & content)
{
	if(!_isRunning)
	{
		abort();
	}

	if(find(content.begin(), content.end(), ';') != content.end())
	{
		abort();
	}

	if(NetworkingHelper::_isMessageReserved(content))
	{
		abort();
	}

	if(content.size() > NetworkingHelper::MAX_MESSAGE_SIZE)
	{
		abort();
	}

	for(int index = 0; index < static_cast<int>(_clientUsernames.size()); index++)
	{
		if(!_clientUsernames[index].empty())
		{
			if(username == _clientUsernames[index])
			{
				_sendTcpMessageToClient(_clientSockets[index], content, false);

				return;
			}
		}
	}

	abort();
}

void NetworkingServer::sendUdpMessageToClient(const string & username, const string & content)
{
	if(!_isRunning)
	{
		abort();
	}

	if(find(content.begin(), content.end(), ';') != content.end())
	{
		abort();
	}

	if(NetworkingHelper::_isMessageReserved(content))
	{
		abort();
	}

	if(content.size() > NetworkingHelper::MAX_MESSAGE_SIZE)
	{
		abort();
	}

	for(int index = 0; index < static_cast<int>(_clientUsernames.size()); index++)
	{
		if(!_clientUsernames[index].empty())
		{
			if(username == _clientUsernames[index])
			{
				_sendUdpMessageToClient(_clientIps[index], _udpClientPorts[index], content, false);

				return;
			}
		}
	}

	abort();
}

void NetworkingServer::broadcastTcpMessageToClients(const string & content)
{
	if(!_isRunning)
	{
		abort();
	}

	if(find(content.begin(), content.end(), ';') != content.end())
	{
		abort();
	}

	if(NetworkingHelper::_isMessageReserved(content))
	{
		abort();
	}

	if(content.size() > NetworkingHelper::MAX_MESSAGE_SIZE)
	{
		abort();
	}

	for(int index = 0; index < static_cast<int>(_clientSockets.size()); index++)
	{
		if(!_clientUsernames[index].empty())
		{
			_sendTcpMessageToClient(_clientSockets[index], content, false);
		}
	}
}

void NetworkingServer::broadcastUdpMessageToClients(const string & content)
{
	if(!_isRunning)
	{
		abort();
	}

	if(find(content.begin(), content.end(), ';') != content.end())
	{
		abort();
	}

	if(NetworkingHelper::_isMessageReserved(content))
	{
		abort();
	}

	if(content.size() > NetworkingHelper::MAX_MESSAGE_SIZE)
	{
		abort();
	}

	for(int index = 0; index < static_cast<int>(_clientUsernames.size()); index++)
	{
		if(!_clientUsernames[index].empty())
		{
			_sendUdpMessageToClient(_clientIps[index], _udpClientPorts[index], content, false);
		}
	}
}

void NetworkingServer::disconnectClient(const string & username)
{
	if(!_isRunning)
	{
		abort();
	}

	for(int index = 0; index < static_cast<int>(_clientUsernames.size()); index++)
	{
		if(!_clientUsernames[index].empty())
		{
			if(username == _clientUsernames[index])
			{
				_sendTcpMessageToClient(_clientSockets[index], "DISCONNECTED", true);

				return;
			}
		}
	}

	abort();
}

void NetworkingServer::disconnectClients()
{
	if(!_isRunning)
	{
		abort();
	}

	for(int index = 0; index < static_cast<int>(_clientUsernames.size()); index++)
	{
		if(!_clientUsernames[index].empty())
		{
			_sendTcpMessageToClient(_clientSockets[index], "DISCONNECTED", true);

			return;
		}
	}
}