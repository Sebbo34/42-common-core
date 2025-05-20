/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 02:13:17 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 16:31:22 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void Server::kick(int i, protocol *prot)
{
	if ((prot->cmd.size() < 3) || _users[i].getIsConnected().size() != 5)
	{
		if (prot->cmd.size() < 3)
			response(ERR_NEEDMOREPARAMS( _users[i].getNickName(), prot->cmd[0]), _users[i].getSocket());
		return;
	}
	std::vector<std::string> vectChannel;
	std::vector<std::string>::iterator chanToKick;
	std::string msg = "";
	vectChannel = parseChannelRecv(prot->cmd[1]);
	if (prot->cmd.size() == 4 && prot->cmd[3].size() > 0 && prot->cmd[3][0] == ':')
		msg = " " + prot->cmd[3];
	for (chanToKick = vectChannel.begin(); chanToKick != vectChannel.end(); chanToKick++)
	{
		try 
		{
			_channels.at(*chanToKick);
			if (isNickIn(_channels[*chanToKick].getOperators(), _users[i].getNickName()))
			{
				if (isNickIn(_users, prot->cmd[2]) && (isNickIn(_channels[*chanToKick].getUsers(), prot->cmd[2]) || isNickIn(_channels[*chanToKick].getOperators(), prot->cmd[2])))
				{
					int indUTK = getIndUserByNN(_users, prot->cmd[2]);
					_channels.at(*chanToKick).removeUser(_users[indUTK]);
					_users[indUTK].removeChannel((*chanToKick));
					response(RPL_KICK(addPrefix(_users[i]), (*chanToKick), prot->cmd[2], msg), _users[indUTK].getSocket());
					sendRPL(_channels[*chanToKick], RPL_KICK(addPrefix(_users[i]), (*chanToKick), prot->cmd[2], msg));
					_channels[*chanToKick].decementUserNb();
				}
				else if (!isNickIn(_users, prot->cmd[2]))
					sendError(_users[i], "401", prot->cmd[2], "No such nick/channel");
				else
				{
					response(ERR_USERNOTINCHANNEL(_users[i].getNickName(), prot->cmd[2],prot->cmd[1]), _users[i].getSocket());
					std::cout << prot->cmd[2] << "They aren't on that channel" << std::endl;
				}
			}
			else 
				sendError(_users[i], "482", (*chanToKick), "You're not channel operator");
		}
		catch (std::exception const &e)
		{
			sendError(_users[i], "403", (*chanToKick), "No such channel");
		}
	}
}

