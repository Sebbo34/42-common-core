/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiu <lchiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 02:13:22 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 18:15:18 by lchiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void Server::part(int i, protocol *prot)
{
	if ((prot->cmd.size() < 2) || _users[i].getIsConnected().size() != 5)
	{
		if (prot->cmd.size() < 2)
			response(ERR_NEEDMOREPARAMS( _users[i].getNickName(), prot->cmd[0]), _users[i].getSocket());
		return;
	}
	std::vector<std::string> vectChannel;
	std::vector<std::string>::iterator chanToLeave;
	std::string                         msg = "";
	vectChannel = parseChannelRecv(prot->cmd[1]);
	std::vector<std::string>::iterator it;
		
	for (chanToLeave = vectChannel.begin(); chanToLeave != vectChannel.end(); chanToLeave++)
	{
		try 
		{
			_channels.at(*chanToLeave);
			if (isStrInVect(_users[i].getChannels(), (*chanToLeave)))
			{
				if(prot->cmd.size() == 3 && prot->cmd[2].size() > 0 && prot->cmd[2][0] == ':')
					msg = prot->cmd[2];
				_channels.at(*chanToLeave).removeUser(_users[i]);
				_users[i].removeChannel((*chanToLeave));
				response(RPL_PART(addPrefix(_users[i]), (*chanToLeave), msg), _users[i].getSocket());
				sendRPL(_channels[*chanToLeave], RPL_PART(addPrefix(_users[i]), (*chanToLeave), msg));
				_channels[*chanToLeave].decementUserNb();
				empty_chanel(*chanToLeave);
			}
			else 
				sendError(_users[i], "442", (*chanToLeave), "You're not on that channel");
		}
		catch (std::exception const &e)
		{
			sendError(_users[i], "403", (*chanToLeave), "No such channel");
		}
	}
}
