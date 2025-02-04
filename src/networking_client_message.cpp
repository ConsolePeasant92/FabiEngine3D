#include "networking_client_message.hpp"

NetworkingClientMessage::NetworkingClientMessage(const string & username, const string & content, const NetworkingProtocolType protocol)
	:
	_username(username),
	_content(content),
	_protocol(protocol)
{

}

const string & NetworkingClientMessage::getUsername() const
{
	return _username;
}

const string & NetworkingClientMessage::getContent() const
{
	return _content;
}

const NetworkingProtocolType NetworkingClientMessage::getProtocol() const
{
	return _protocol;
}