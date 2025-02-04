#define WIN32_LEAN_AND_MEAN

#include "networking_client.hpp"

#include <ws2tcpip.h>

using std::launch;

NetworkingClient::NetworkingClient()
{
	_tcpSocket = INVALID_SOCKET;
	_udpSocket = INVALID_SOCKET;
}

NetworkingClient::~NetworkingClient()
{
	if(_isRunning)
	{
		stop();
	}
}

void NetworkingClient::start(const string & username)
{
	if(_isRunning)
	{
		abort();
	}

	if(username.empty())
	{
		abort();
	}

	if(username.size() > NetworkingHelper::MAX_USERNAME_SIZE)
	{
		abort();
	}

	if(NetworkingHelper::_isMessageReserved(username))
	{
		abort();
	}

	if(find(username.begin(), username.end(), ';') != username.end())
	{
		abort();
	}

	_username = username;
	_isRunning = true;
}

void NetworkingClient::connectToServer(const string & ip)
{
	if(!_isRunning)
	{
		abort();
	}

	if(_isConnectedToServer)
	{
		abort();
	}

	if(_isConnectingToServer)
	{
		abort();
	}

	if(!isValidIp(ip))
	{
		abort();
	}

	if(!_setupTcp())
	{
		return;
	}

	if(!_setupUdp())
	{
		return;
	}

	_connectionThread = async(launch::async, &NetworkingClient::_connectToServer, this, _tcpSocket, ip);

	_serverIp = ip;
	_isConnectingToServer = true;
}

void NetworkingClient::disconnectFromServer(bool mustBeAccepted)
{
	if(!_isRunning)
	{
		abort();
	}

	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		abort();
	}

	if(_tcpSocket != INVALID_SOCKET)
	{
		closesocket(_tcpSocket);
	}

	if(_udpSocket != INVALID_SOCKET)
	{
		closesocket(_udpSocket);
	}

	_tcpSocket = INVALID_SOCKET;
	_udpSocket = INVALID_SOCKET;
	_pendingMessages.clear();
	_pingLatencies.clear();
	_lastMilliseconds = 0;
	_tcpMessageBuild = "";
	_serverIp = "";
	_isConnectedToServer = false;
	_isAcceptedByServer = false;
	_isWaitingForPing = false;
	_mustDisconnectFromServer = false;
}

void NetworkingClient::stop()
{
	if(!_isRunning)
	{
		abort();
	}

	if(_tcpSocket != INVALID_SOCKET)
	{
		closesocket(_tcpSocket);
	}

	if(_udpSocket != INVALID_SOCKET)
	{
		closesocket(_udpSocket);
	}

	_tcpSocket = INVALID_SOCKET;
	_udpSocket = INVALID_SOCKET;
	_pendingMessages.clear();
	_pingLatencies.clear();
	_lastMilliseconds = 0;
	_username = "";
	_tcpMessageBuild = "";
	_serverIp = "";
	_isConnectedToServer = false;
	_isConnectingToServer = false;
	_isAcceptedByServer = false;
	_isWaitingForPing = false;
	_mustDisconnectFromServer = false;
	_isRunning = false;
}