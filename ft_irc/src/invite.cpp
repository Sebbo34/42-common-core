/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 02:13:14 by sbo               #+#    #+#             */
/*   Updated: 2024/08/14 11:41:33 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void Server::invite(int i, protocol *prot)
{
	if ((prot->cmd.size() < 3) || _users[i].getIsConnected().size() != 5)
	{
		if (prot->cmd.size() < 3)
			response(ERR_NEEDMOREPARAMS( _users[i].getNickName(), prot->cmd[0]), _users[i].getSocket());
		return;
	}
	try 
	{
		_channels.at(prot->cmd[2]);
		if (isNickIn(_channels[prot->cmd[2]].getOperators(), _users[i].getNickName()))
		{
			if (isNickIn(_users, prot->cmd[1]))
			{
				if (!isNickIn(_channels[prot->cmd[2]].getUsers(), prot->cmd[1]) && !isNickIn(_channels[prot->cmd[2]].getOperators(), prot->cmd[1]))
				{
					int indUTK = getIndUserByNN(_users, prot->cmd[1]);
					response(RPL_INV(addPrefix(_users[i]), prot->cmd[1], prot->cmd[2]), _users[indUTK].getSocket());
					_channels[prot->cmd[2]].pushInvitation(prot->cmd[1]);
					sendRPL(_channels[prot->cmd[2]], RPL_PING_INV(prot->cmd[2], _users[i].getNickName() , prot->cmd[1]));
				}
				else
				{
					response(RPL_USERONCHANNEL(_users[i].getNickName(), prot->cmd[1], prot->cmd[2]), _users[i].getSocket());
				}
			}
			else 
				sendError(_users[i], "401", prot->cmd[1], "No such nick/channel");
		}
		else 
			sendError(_users[i], "482", prot->cmd[2], "You're not channel operator");
	}
	catch (std::exception const &e)
	{
		sendError(_users[i], "403", prot->cmd[2], "No such channel");
	}
}
