#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::future_status;
using std::launch;
using std::chrono::system_clock;
using std::get;

void NetworkClientAPI::update()
{
	// Must be running
	if(!_isRunning)
	{
		return;
	}

	// Check if client must disconnect
	if(_mustDisconnectFromServer)
	{
		disconnectFromServer(false);
		return;
	}

	// Clear all received messages from last tick
	_pendingMessages.clear();

	// Handle server connection
	if(_isConnectingToServer)
	{
		// Check if connection thread is finished
		if(_connectionThread.wait_until(system_clock::time_point::min()) == future_status::ready)
		{
			// Retrieve error code
			auto connectionErrorCode = _connectionThread.get();

			if(connectionErrorCode == 0) // Successfully connected with server
			{
				// Not connecting anymore
				_isConnectingToServer = false;
				_isConnectedToServer = true;

				// Send username to server
				if(!_sendTcpMessage(("USERNAME" + _username), true, false))
				{
					return;
				}

				// Start a thread to wait for TCP messages
				_tcpMessageThread = async(launch::async, &NetworkClientAPI::_waitForTcpMessage, this, _connectionSocketID);
			}
			else if((connectionErrorCode == WSAECONNREFUSED) || (connectionErrorCode == WSAETIMEDOUT)) // Cannot connect with server
			{
				_isConnectingToServer = false;
			}
			else // Something really bad happened
			{
				Logger::throwError("NetworkClientAPI::update::1 ---> ", connectionErrorCode);
			}
		}
		else
		{
			return; // Wait until client is connected to server
		}
	}

	// Must be connected
	if(!_isConnectedToServer)
	{
		return;
	}

	// Update server pinging
	if(_isAcceptedByServer && !_isWaitingForPing)
	{
		// Send ping
		if(!_sendTcpMessage("PING", true, true))
		{
			return;
		}

		// Start measuring latency
		_isWaitingForPing = true;
		_lastMilliseconds = Tools::getTimeSinceEpochMS();
	}

	// Receive incoming TCP messages
	if(_tcpMessageThread.wait_until(system_clock::time_point::min()) == future_status::ready)
	{
		// Temporary values
		const auto& messageResult = _tcpMessageThread.get();
		const auto& messageStatusCode = get<0>(messageResult);
		const auto& messageErrorCode = get<1>(messageResult);
		const auto& messageTimestamp = get<2>(messageResult);
		const auto& messageContent = get<3>(messageResult);

		if(messageStatusCode > 0) // Message is received correctly
		{
			// Loop through received message(s)
			for(const auto& character : messageContent)
			{
				if(character == ';') // End of current message
				{
					if(_tcpMessageBuild == "ACCEPTED") // Handle ACCEPTED message
					{
						_isAcceptedByServer = true;
						_tcpMessageBuild = "";
					}
					else if(_tcpMessageBuild == "SERVER_FULL") // Handle SERVER_FULL message
					{
						// Disconnect next tick
						_pendingMessages.push_back(NetworkServerMessage(_tcpMessageBuild, NetworkProtocol::TCP));
						_tcpMessageBuild = "";
						_mustDisconnectFromServer = true;

						// Prevent processing more messages
						break;
					}
					else if(_tcpMessageBuild == "USER_ALREADY_CONNECTED") // Handle USER_ALREADY_CONNECTED message
					{
						// Disconnect next tick
						_pendingMessages.push_back(NetworkServerMessage(_tcpMessageBuild, NetworkProtocol::TCP));
						_tcpMessageBuild = "";
						_mustDisconnectFromServer = true;

						// Prevent processing more messages
						break;
					}
					else if(_tcpMessageBuild == "DISCONNECTED_BY_SERVER") // Handle DISCONNECTED_BY_SERVER message
					{
						// Disconnect next tick
						_pendingMessages.push_back(NetworkServerMessage(_tcpMessageBuild, NetworkProtocol::TCP));
						_tcpMessageBuild = "";
						_mustDisconnectFromServer = true;

						// Prevent processing more messages
						break;
					}
					else if(_tcpMessageBuild.substr(0, 4) == "PING") // Handle PING message
					{
						// Calculate ping latency
						auto latency = (Tools::getTimeSinceEpochMS() - _lastMilliseconds);

						// Subtract the server & client processing delays
						auto serverReceiveDelay = stoll(_tcpMessageBuild.substr(4));
						auto clientReceiveDelay = (Tools::getTimeSinceEpochMS() - messageTimestamp);
						latency -= serverReceiveDelay;
						latency -= clientReceiveDelay;

						// Register server latency
						if(_pingLatencies.size() == NetworkUtils::MAX_PING_COUNT)
						{
							_pingLatencies.erase(_pingLatencies.begin());
						}
						_pingLatencies.push_back(static_cast<unsigned int>(llabs(latency)));
						_isWaitingForPing = false;
						_tcpMessageBuild = "";
					}
					else // Handle other message
					{
						_pendingMessages.push_back(NetworkServerMessage(_tcpMessageBuild, NetworkProtocol::TCP));
						_tcpMessageBuild = "";
					}
				}
				else // Add to current message build
				{
					_tcpMessageBuild += character;
				}
			}
		}
		else if(messageStatusCode == 0) // Server closed socket connection
		{
			disconnectFromServer(false);
			return;
		}
		else // Receive failed
		{
			auto code = messageErrorCode;
			if((code == WSAECONNRESET) || (code == WSAECONNABORTED) || (code == WSAETIMEDOUT)) // Server lost socket connection
			{
				disconnectFromServer(false);
				return;
			}
			else // Something really bad happened
			{
				Logger::throwError("NetworkClientAPI::update::2 ---> ", code);
			}
		}

		// Spawn new TCP message thread
		_tcpMessageThread = async(launch::async, &NetworkClientAPI::_waitForTcpMessage, this, _connectionSocketID);
	}

	// Receive incoming UDP messages
	while(NetworkUtils::isUdpMessageReady(_udpMessageSocketID))
	{
		// Message data
		const auto& messageResult = _receiveUdpMessage(_udpMessageSocketID);
		const auto& messageStatusCode = get<0>(messageResult);
		const auto& messageErrorCode = get<1>(messageResult);
		const auto& messageContent = get<2>(messageResult);
		const auto& messageIP = get<3>(messageResult);
		const auto& messagePort = get<4>(messageResult);

		if(messageStatusCode > 0) // Message is received correctly
		{
			if((messageIP == _serverIP) && (messagePort == _serverPort)) // Message must come from server
			{
				_pendingMessages.push_back(NetworkServerMessage(messageContent, NetworkProtocol::UDP));
			}
		}
		else if
			(
			(messageStatusCode == 0) ||
			(messageErrorCode == WSAECONNRESET) ||
			(messageErrorCode == WSAECONNABORTED) ||
			(messageErrorCode == WSAEMSGSIZE)
			)
		{
			// Wrong packet, do nothing
		}
		else // Something really bad happened
		{
			Logger::throwError("NetworkClientAPI::update::3 ---> ", messageErrorCode);
		}
	}
}