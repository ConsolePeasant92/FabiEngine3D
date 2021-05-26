#pragma once

#include "network_message.hpp"

#include <string>
#include <future>
#include <vector>
#include <memory>
#include <tuple>

using std::string;
using std::vector;
using std::future;
using std::shared_ptr;
using std::tuple;
using std::make_shared;
using std::make_tuple;

class NetworkServer final
{
public:
	NetworkServer();
	~NetworkServer();

	void start();
	void stop();
	void update();
	void loadNextMessage();

	bool isRunning();
	bool isMessagePending();

	const shared_ptr<NetworkMessage> getPendingMessage();

private:
	void _sendMessageToClient(SOCKET clientSocketID, const string& content);
	void _acceptClient(SOCKET clientSocketID);
	void _disconnectClient(const string& ipAddress);
	SOCKET _waitForClientConnection(SOCKET listenSocketID);
	tuple<int, string, int> _waitForClientMessage(SOCKET clientSocketID);

	static inline const string SERVER_PORT = "61205";
	static inline const unsigned int MAX_MESSAGE_BYTES = 512;
	static inline const unsigned int MAX_CLIENT_COUNT = 1;

	SOCKET _listenSocketID;

	future<SOCKET> _connectionThread;

	vector<SOCKET> _clientSocketIDs;
	vector<string> _clientIPs;
	vector<future<tuple<int, string, int>>> _clientMessageThreads;
	vector<shared_ptr<NetworkMessage>> _receivedMessageQueue;

	bool _isRunning = false;
};