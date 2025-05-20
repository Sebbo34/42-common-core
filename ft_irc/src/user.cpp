/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 00:07:59 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 17:15:10 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"


user & user::operator=(user const & user)
{
	if (this != &user)
	{
		_nickName = user._nickName;
		_hostName = user._hostName;
		_userName = user._userName;
		_serverName = user._serverName;
		_socket = user._socket;
		_channels = user._channels;
		_buffer = user._buffer;
		_isConnected = user._isConnected;
	}
	return *this;
}

void	user::removeChannel(std::string channel)
{
	std::vector<std::string>::iterator it;
	for (it = _channels.begin(); it != _channels.end(); it++)
	{
		if ((*it).compare(channel) == 0)
		{
			_channels.erase(it);
			break;
		}
	};
}

std::vector<std::string> &user::getChannels() {
	return _channels;
}

std::string user::getNickName() const {
	return _nickName;
}

std::string user::getUserName() const {
	return _userName;
}

std::string user::getHostName() const {
	return _hostName;
}

std::string user::getServerName() const {
	return _serverName;
}

int user::getSocket() const {
	return _socket;
}

std::string user::getIsConnected() const {
	return _isConnected;
}

std::string &user::getBuffer() {
	return _buffer;
}

void user::pushChannel(std::string chan) {
	_channels.push_back(chan);
}

void user::setNickName(const std::string &newNickName) {
	_nickName = newNickName;
}

void user::setUserName(const std::string &newUserName) {
	_userName = newUserName;
}

void user::setHostName(const std::string &newHostName) {
	_hostName = newHostName;
}

void user::setServerName(const std::string &newServerName) {
	_serverName = newServerName;
}

void user::setSocket(int newSocket) {
	_socket = newSocket;
}

void user::setIsConnected(std::string var) {
	_isConnected = var;
}

void user::setBuffer(std::string buffer) {
	if (buffer.empty())
		buffer = "";
	else
		_buffer = buffer;
}

void user::clearBuffer() 
{
	unsigned int i;
	for (i = 0; i < _buffer.size(); i++)
	{
		if (_buffer.substr(i, _buffer.size()).find("\r\n") == std::string::npos)
			break;
	}
	i++;
	_buffer = _buffer.substr(i, _buffer.size());
}
