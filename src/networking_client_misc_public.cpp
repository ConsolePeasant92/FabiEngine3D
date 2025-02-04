#define WIN32_LEAN_AND_MEAN

#include "networking_client.hpp"
#include "mathematics.hpp"

#include <ws2tcpip.h>

const bool NetworkingClient::isValidIp(const string & ip) const
{
	if(ip == "0.0.0.0")
	{
		return false;
	}

	sockaddr_in socketAddress = {};

	socketAddress.sin_family = AF_INET;

	return (InetPton(AF_INET, ip.c_str(), &socketAddress.sin_addr.s_addr) > 0);
}

const bool NetworkingClient::isRunning() const
{
	return _isRunning;
}

const bool NetworkingClient::isConnectingToServer() const
{
	return _isConnectingToServer;
}

const bool NetworkingClient::isConnectedToServer() const
{
	return _isConnectedToServer;
}

const bool NetworkingClient::isAcceptedByServer() const
{
	return _isAcceptedByServer;
}

const int NetworkingClient::getPingLatency() const
{
	if(_pingLatencies.empty())
	{
		return 0;
	}

	return Mathematics::calculateAverage(_pingLatencies);
}

const string & NetworkingClient::getUsername() const
{
	return _username;
}

const string & NetworkingClient::getServerIp() const
{
	return _serverIp;
}

const vector<NetworkingServerMessage> & NetworkingClient::getPendingMessages() const
{
	return _pendingMessages;
}

void NetworkingClient::sendTcpMessageToServer(const string & content)
{
	if(!_isRunning)
	{
		abort();
	}

	if(!_isConnectedToServer || !_isAcceptedByServer)
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

	_sendTcpMessageToServer(content, false, true);
}

void NetworkingClient::sendUdpMessageToServer(const string & content)
{
	if(!_isRunning)
	{
		abort();
	}

	if(!_isConnectedToServer || !_isAcceptedByServer)
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

	_sendUdpMessageToServer(content, false, true);
}