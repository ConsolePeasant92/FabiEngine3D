#define WIN32_LEAN_AND_MEAN

#include "network_utils.hpp"
#include <iostream>

#include <ws2tcpip.h>

using std::to_string;

const sockaddr_in NetworkUtils::composeSocketAddress(const string& IP, const string& port)
{
	sockaddr_in socketAddress = sockaddr_in();
	socketAddress.sin_family = AF_INET;
	InetPton(AF_INET, IP.c_str(), &socketAddress.sin_addr.s_addr);
	socketAddress.sin_port = htons(static_cast<u_short>(stoi(port)));
	return socketAddress;
}

const string NetworkUtils::extractAddressIP(sockaddr_in* address)
{
	char IP[IPV4_ADDRESS_LENGTH];
	inet_ntop(AF_INET, &(address->sin_addr), IP, sizeof(IP));
	return string(IP);
}

const string NetworkUtils::extractAddressPort(sockaddr_in* address)
{
	return to_string(ntohs(address->sin_port));
}

const string NetworkUtils::extractSocketIP(SOCKET socket)
{
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getsockname(socket, (sockaddr*)&socketAddress, &socketAddressLength);
	return extractAddressIP(&socketAddress);
}

const string NetworkUtils::extractSocketPort(SOCKET socket)
{
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getsockname(socket, (sockaddr*)&socketAddress, &socketAddressLength);
	return extractAddressPort(&socketAddress);
}

const string NetworkUtils::extractPeerIP(SOCKET socket)
{
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getpeername(socket, (sockaddr*)&socketAddress, &socketAddressLength);
	return extractAddressIP(&socketAddress);
}

const string NetworkUtils::extractPeerPort(SOCKET socket)
{
	sockaddr_in socketAddress = sockaddr_in();
	int socketAddressLength = sizeof(socketAddress);
	auto peerResult = getpeername(socket, (sockaddr*)&socketAddress, &socketAddressLength);
	return extractAddressPort(&socketAddress);
}

const bool NetworkUtils::isValidIP(const string& IP)
{
	sockaddr_in socketAddress = sockaddr_in();
	socketAddress.sin_family = AF_INET;
	auto result = InetPton(AF_INET, IP.c_str(), &socketAddress.sin_addr.s_addr);
	return (result > 0);
}

const bool NetworkUtils::isUdpMessageReady(SOCKET socket)
{
	fd_set socketSet = fd_set();
	timeval timeInterval = { 0 , 1 }; // 1 microsecond
	FD_ZERO(&socketSet);
	FD_SET(socket, &socketSet);
	return (select(0, &socketSet, nullptr, nullptr, &timeInterval) > 0);
}

const bool NetworkUtils::isMessageReserved(const string& message)
{
	return
	(
		(message.substr(0, 7)  == "REQUEST")				||
		(message.substr(0, 6) == "ACCEPT")					||
		(message.substr(0, 4) == "PING")					||
		(message.substr(0, 14) == "SERVER_IS_FULL")			||
		(message.substr(0, 22) == "USER_ALREADY_CONNECTED") ||
		(message.substr(0, 22) == "DISCONNECTED_BY_SERVER")
	);
}