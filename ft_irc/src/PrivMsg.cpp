/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:17:46 by sbo               #+#    #+#             */
/*   Updated: 2024/08/14 11:42:47 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void Server::sendToChannel(int i, protocol *prot)
{
	std::vector<user>::iterator usersInChan;
	int op;

	op = 0;
	try
	{
		_channels.at(prot->cmd[1]);
		if (isStrInVect(_users[i].getChannels(), prot->cmd[1]))
		{
			if (prot->cmd[2].size() > 1 && prot->cmd[2][0] == ':')
			{
				if (isNickIn(_channels[prot->cmd[1]].getOperators(), _users[i].getNickName()))
					op = 1;
				for (usersInChan = _channels[prot->cmd[1]].getUsers().begin(); usersInChan != _channels[prot->cmd[1]].getUsers().end(); usersInChan++)
				{
					if ((*usersInChan).getSocket() != _users[i].getSocket())
						response (RPL_PRIVMSG(PrefixOp(_users[i], op), prot->cmd[1], prot->cmd[2]), (*usersInChan).getSocket());
				};
				for (usersInChan = _channels[prot->cmd[1]].getOperators().begin(); usersInChan != _channels[prot->cmd[1]].getOperators().end(); usersInChan++)
				{
					if ((*usersInChan).getSocket() != _users[i].getSocket())
						response(RPL_PRIVMSG(PrefixOp(_users[i], op), prot->cmd[1], prot->cmd[2]), (*usersInChan).getSocket());
				};
			}
			else 
				response(ERR_NOTEXTTOSEND(_users[i].getNickName()), _users[i].getSocket());
		}
		else
		{
			sendError(_users[i], "442", prot->cmd[1], "You're not on that channel");
		}
	}
	catch (std::exception const &e)
	{
		sendError(_users[i], "403", prot->cmd[1], "No such channel");
	}
}

void	Server::sendToUser(int i, protocol *prot)
{
	if (isNickIn(_users, prot->cmd[1]))
		{
			if (prot->cmd[2].size() > 1 && prot->cmd[2][0] == ':')
				response (RPL_PRIVMSG(addPrefix(_users[i]), prot->cmd[1], prot->cmd[2]), getSocketByNN(_users, prot->cmd[1]));
			else 
				response(ERR_NOTEXTTOSEND(_users[i].getNickName()), _users[i].getSocket());
		}
	else
		response(RPL_USER_NOT_FOUND(_users[i].getNickName(), prot->cmd[1]), _users[i].getSocket());
}

void	Server::privMsg(int i, protocol *prot)
{
	if (prot->cmd.size() >= 3 && _users[i].getIsConnected().size() == 5)
	{
		if (prot->cmd[1][0] == '#')
			sendToChannel(i, prot); 
		else
			sendToUser(i, prot); 
	}
	else if (prot->cmd.size() < 3)
		response(ERR_NEEDMOREPARAMS( _users[i].getNickName(), prot->cmd[0]), _users[i].getSocket());
}