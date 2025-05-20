/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:18:45 by sbo               #+#    #+#             */
/*   Updated: 2024/08/14 12:29:35 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

int getSocketByNN(std::vector<user> users, std::string nickName)
{
	std::vector<user>::iterator it;
	for (it = users.begin(); it != users.end(); it++)
	{
		if ((*it).getNickName() == nickName)
			return ((*it).getSocket());
	}
	return (-1);
}

int getIndUserByNN(std::vector<user> users, std::string nickName)
{
	std::vector<user>::iterator it;
	int i;

	i = 0;
	for (it = users.begin(); it != users.end(); it++)
	{
		if ((*it).getNickName() == nickName && (*it).getIsConnected().size() == 5)
			return (i);
		i++;
	}
	return (-1);
}

std::string	extractName(channel chan)
{
	std::vector<user>::iterator it;
	std::string name = " :";
	for (it = chan.getUsers().begin(); it != chan.getUsers().end(); it++)
	{
		if (it == chan.getUsers().begin())
		name = name + (*it).getNickName();
		else 
			name = name + " " + (*it).getNickName();
	}
	for (it = chan.getOperators().begin(); it != chan.getOperators().end(); it++)
	{
		name = name + " @" + (*it).getNickName();
	}
	return (name);
}


std::string getWord(std::string str, int ind)
{
	int i;
	i = 0;
	while (i < ind)
	{
		str.erase(0, str.find("\n") + 1);
		i++;
	}
	return (str.substr(str.find(" ") + 1, str.find("\r") - str.find(" ") - 1));
}

bool	isNickIn(std::vector<user> users, std::string newNickName)
{
	std::vector<user>::iterator it;
	for (it = users.begin(); it != users.end(); it++)
	{
		if ((*it).getNickName().compare(newNickName) == 0 && (*it).getIsConnected().size() == 5)
			return (true);
	}
	return (false);
}

bool	isStrInVect(std::vector<std::string> vect, std::string str)
{
	std::vector<std::string>::iterator it;
	for (it = vect.begin(); it != vect.end(); it++)
	{
		if ((*it).compare(str) == 0)
			return (true);
	}
	return (false);
}

std::vector<std::string> parseChannelRecv(std::string channels)
{
	std::vector<std::string>	vectChannel;
	while (!channels.empty())
	{
		if (channels.find(",") == channels.npos)
			break;
		if (!channels.substr(0,channels.find(",")).empty())
			vectChannel.push_back(channels.substr(0,channels.find(",")));
		channels.erase(0, channels.find(",") + 1);
	}
	if (!channels.empty())
		vectChannel.push_back(channels);
	return (vectChannel);
}

std::string	to_str(time_t value)
{
	std::string str;
	char digit;
	while (value > 0)
	{
		digit = '0' +  value % 10;
		value = value / 10;
		str = digit + str;
	}
	return (str);
}
void	sendError(user target, std::string number, std::string channel, std::string msg)
{
	std::string tmpstr;
	tmpstr =  number + " " + target.getNickName() + " " + channel + " :" + msg + "\r\n";
	if (send(target.getSocket(), tmpstr.c_str(), tmpstr.length(), 0) == -1)
	{
		std::cerr << "Error: send() failed: " << strerror(errno) << std::endl;
		return ;
	}
	std::cout << channel << " " << msg << std::endl;		
}

void Server::sendRPL(channel chan, std::string RPL)
{
	std::vector<user>::iterator userInChan;
	for (userInChan = chan.getUsers().begin(); userInChan != chan.getUsers().end(); userInChan++)
		response(RPL, (*userInChan).getSocket());
	for (userInChan = chan.getOperators().begin(); userInChan != chan.getOperators().end(); userInChan++)
		response(RPL, (*userInChan).getSocket());
}

std::string addPrefix(user userNames)
{
	std::string prefix;
	prefix = ":" + userNames.getNickName() + "!" + userNames.getUserName() + "@" + userNames.getHostName() + " ";
	return (prefix);
}

std::string PrefixOp(user userNames, int i)
{
	std::string prefix;
	if (i == 1)
		prefix = ":@" + userNames.getNickName() + "!" + userNames.getUserName() + "@" + userNames.getHostName() + " ";
	else
		prefix = ":" + userNames.getNickName() + "!" + userNames.getUserName() + "@" + userNames.getHostName() + " ";
	return (prefix);
}

void	ft_send(int socket, std::string msg)
{
	if (send(socket, msg.c_str(), msg.length(), MSG_NOSIGNAL) == -1)
        std::cerr << "Error: send() failed: " << strerror(errno) << std::endl;
}

bool Server::checkBuffer(int i)
{
	_users[i].setBuffer(_users[i].getBuffer() + _buf);
	if (_users[i].getBuffer().find("\r\n") == std::string::npos)
		return false;
	if (_users[i].getBuffer().compare("\r\n") == 0)
	{
		_users[i].clearBuffer();
		return false;
	}
	return true;
}