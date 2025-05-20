/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 02:13:19 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 12:51:00 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

bool    isNickInAll(std::vector<user> users, std::string newNickName)
{
	std::vector<user>::iterator it;
	for (it = users.begin(); it != users.end(); it++)
	{
		if ((*it).getNickName().compare(newNickName) == 0)
			return (true);
	}
	return (false);
}

void send_newNick(std::map<std::string, channel> &channels, user user1, std::string newNick)
{
	std::vector<std::string>::iterator chanOfUser;
	std::vector<user>::iterator usersInChan;
	for (chanOfUser = user1.getChannels().begin(); chanOfUser != user1.getChannels().end(); chanOfUser++)
	{
		for (usersInChan = channels[*chanOfUser].getUsers().begin(); usersInChan != channels[*chanOfUser].getUsers().end(); usersInChan++)
		{
			if ((*usersInChan).getSocket() != user1.getSocket())
				ft_send((*usersInChan).getSocket(), RPL_NEWNICK((*chanOfUser), user1.getNickName(),newNick));
			else
				(*usersInChan).setNickName(newNick);
		};
		for (usersInChan = channels[*chanOfUser].getOperators().begin(); usersInChan != channels[*chanOfUser].getOperators().end(); usersInChan++)
		{
			if ((*usersInChan).getSocket() != user1.getSocket())
				ft_send((*usersInChan).getSocket(), RPL_NEWNICK((*chanOfUser), user1.getNickName(),newNick));
			else
				(*usersInChan).setNickName(newNick);
		};
	};
}

void Server::nick(int i, std::string nickname)
{
	if (!isNickInAll(_users, nickname) && nickname.length() < 32 && !nickname.empty() && nickname[0] != '#' && !isdigit(nickname[0]))
	{
		if (_users[i].getIsConnected().size() == 5)
		{
			ft_send(_users[i].getSocket(), RPL_NICK(_users[i].getNickName(), nickname));
			send_newNick(_channels, _users[i], nickname);
			_users[i].setNickName(nickname);
		}
		else 
		{
			_users[i].setNickName(nickname);
			if (_users[i].getIsConnected().find("N") == std::string::npos)
				_users[i].setIsConnected(_users[i].getIsConnected() + "N");
		}
	}
	else if (nickname.length() > 31 && !isNickInAll(_users, nickname))
		nick(i, nickname.substr(0, 31));
	else if (isNickInAll(_users, nickname))
	{
		if (_users[i].getIsConnected().size() != 5)
		{
			if (nickname.length() < 31)
				nick(i, nickname + "-");
			else 
			{
				std::cout << "Error nickname is too long and can't be truncate" << std::endl;
			}
		}
		else if (!isNickIn(_users, nickname) && _users[i].getIsConnected().size() == 5)
		{
			int ind;
			ind = getIndUserByNN(_users, nickname);
			if (ind > 0)
			{
				while (isNickInAll(_users, _users[ind].getNickName()))
					_users[ind].setNickName(nickname + "-");
			}
			ft_send(_users[i].getSocket(), RPL_NICK(_users[i].getNickName(), nickname));
			send_newNick(_channels, _users[i], nickname);
			_users[i].setNickName(nickname);
		}
		else
			ft_send(_users[i].getSocket(), RPL_ERR_NICKNAMEINUSE(nickname));
	}
	else 
	{
		if (_users[i].getIsConnected().size() == 5)
			ft_send(_users[i].getSocket(),RPL_ERRONEUSNICKNAME(_users[i].getNickName(), nickname));
	}
}
