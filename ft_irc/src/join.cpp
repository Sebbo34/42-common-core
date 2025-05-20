/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:19:00 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 16:59:05 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include "../includes/channel.hpp"

int    Server::check_canal_access(protocol *prot, std::string channelName, int i)
{
    if (_channels.find(channelName) != _channels.end()) // Si le canal existe
    {
        std::vector<std::string>::iterator trouve = std::find(_channels[channelName].getInvitation().begin(), _channels[channelName].getInvitation().end(), _users[i].getNickName());

        // Si option i est active et tu as ete invite avec /INVITE
		if (_channels[channelName].getInviteOnly() == true && trouve == _channels[channelName].getInvitation().end())
        {
            response(ERR_INVITEONLYCHAN( _users[i].getNickName(), channelName), _users[i].getSocket());
            return (1);
        }
        // Vérifiez la limite d'utilisateurs du canal
        if (_channels[channelName].getLimit() > 0 && _channels[channelName].getuserNb() >= _channels[channelName].getLimit())
        {
            response(ERR_CHANNELISFULL( _users[i].getNickName(), channelName), _users[i].getSocket());
            return (1);
        }
        // Verifier le key du chanel
        if (_channels[channelName].getPass().compare("/0") != 0) // si mdp set
        {
            if (prot->cmd.size() < 3 || _channels[channelName].getPass().compare(prot->cmd[2]) != 0)
            {
                response(ERR_BADCHANNELKEY( _users[i].getNickName(), prot->cmd[1]), _users[i].getSocket());
                return (1);
            }
        }
    }
    return (0);
}

void    Server::join(int i, protocol *prot) 
{
	if ((prot->cmd.size() < 2) || _users[i].getIsConnected().size() != 5)
	{
		if (prot->cmd.size() < 2)
			response(ERR_NEEDMOREPARAMS( _users[i].getNickName(), prot->cmd[0]), _users[i].getSocket());
		return ;
	}
	std::vector<std::string> vectChannel;
	std::vector<std::string>::iterator chanToJoin;
	vectChannel = parseChannelRecv(prot->cmd[1]);
	
	for (chanToJoin = vectChannel.begin(); chanToJoin != vectChannel.end(); chanToJoin++)
	{
		if (check_canal_access(prot, *chanToJoin, i) == 1)
            continue ; // Passe au prochain canal sans essayer d'ajouter l'utilisateur
		if (isStrInVect(_users[i].getChannels(), (*chanToJoin)))
			continue;
		_users[i].pushChannel(*chanToJoin);
		try
		{
			_channels.at(*chanToJoin);
			if (_channels.at(*chanToJoin).getUsers().empty() && _channels.at(*chanToJoin).getOperators().empty())
				_channels.at(*chanToJoin).pushOperators(_users[i]);
			else
				_channels.at(*chanToJoin).pushUsers(_users[i]);
			if (_channels[*chanToJoin].getTopic().size() > 0)
				setTopicForNewUser(_users[i].getSocket(), _channels[*chanToJoin].getTopic(), (*chanToJoin));
			if(isStrInVect(_channels[*chanToJoin].getInvitation(), _users[i].getNickName()))
			{
				std::vector<std::string>::iterator it;
				for (it = _channels[*chanToJoin].getInvitation().begin(); it != _channels[*chanToJoin].getInvitation().end(); it++)
				{
					if (*it == _users[i].getNickName())
					{
						_channels[*chanToJoin].getInvitation().erase(it);
						break ;
					}
				};
			}
			std::string name = extractName(_channels[*chanToJoin]);
			sendRPL(_channels[*chanToJoin], RPL_JOIN(addPrefix(_users[i]), (*chanToJoin)) );
			if (_channels.at(*chanToJoin).getUsers().empty() && _channels.at(*chanToJoin).getOperators().empty())
				response (RPL_NAMREPLY (_users[i].getHostName(), _users[i].getNickName(), " = " + (*chanToJoin), " :@" + _users[i].getNickName()), _users[i].getSocket());
			else
				response (RPL_NAMREPLY (_users[i].getHostName(), _users[i].getNickName(), " @ " + (*chanToJoin), name), _users[i].getSocket());
			response (RPL_ENDOFNAMES(_users[i].getHostName(), _users[i].getNickName(), (*chanToJoin)), _users[i].getSocket());
			_channels[*chanToJoin].incementUserNb(); // Augmente le nombre d'utilisateurs
		}
		catch (std::exception const &e)
		{
			channel tmp;
			tmp.setName(*chanToJoin);
			tmp.pushOperators(_users[i]);
			_channels[*chanToJoin] = tmp;
			response(RPL_JOIN(addPrefix(_users[i]), (*chanToJoin)), _users[i].getSocket());
			response (RPL_NAMREPLY (_users[i].getHostName(), _users[i].getNickName(), " = " + (*chanToJoin), " :@" + _users[i].getNickName()), _users[i].getSocket());
			response (RPL_ENDOFNAMES(_users[i].getHostName(), _users[i].getNickName(), (*chanToJoin)), _users[i].getSocket());
			_channels[*chanToJoin].setuserNb(1);
            _channels[*chanToJoin].setPass("/0");
		}
	}
}
