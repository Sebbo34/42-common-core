/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleClient.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiu <lchiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 02:13:12 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 17:52:13 by lchiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

bool Server::AddClient(int ClientSocket)
{
	user usertmp;

	usertmp.setBuffer("");
	usertmp.setIsConnected("");
	usertmp.setSocket(ClientSocket);
	_users.push_back(usertmp);
	return true;
}

void    Server::handleClientMessage(int i)
{
	if (!checkBuffer(i))
		return ;
	std::vector<protocol *> prot = parseClientRecv(_users[i].getBuffer());
	if (prot.empty())
	{
		response(RPL_UNKNOWCOMMAND(_users[i].getNickName(), _users[i].getBuffer().substr(0, _users[i].getBuffer().size() - 2)), _users[i].getSocket());
		_users[i].clearBuffer();
		return ;
	}
	std::vector<protocol *>::iterator cmdRecv;
	for (cmdRecv = prot.begin(); cmdRecv != prot.end(); cmdRecv++)
	{
		if ((*cmdRecv)->cmd.size() == 0)
			return ;  
		switch ((*cmdRecv)->type)
		{
			case NICK:
				if ((*cmdRecv)->cmd.size() >= 2)
					nick(i, (*cmdRecv)->cmd[1]);
				else 
					response(ERR_NEEDMOREPARAMS( _users[i].getNickName(), (*cmdRecv)->cmd[0]), _users[i].getSocket());
				break;
			case USERHOST:
					userhost(i, (*cmdRecv));
				break;
			case JOIN: 
				join(i, (*cmdRecv));
				break;
			case MODE:
				if (_users[i].getIsConnected().size() == 5)
					handleMode(i, _users[i].getBuffer());
				break;
			case TOPIC:
					topic(i, (*cmdRecv));
				break;
			case INVITE:
				invite(i, (*cmdRecv));
				break;
			case KICK:
					kick(i, (*cmdRecv));
				break;
			case PRIVMSG:
				privMsg(i, (*cmdRecv));
				break;
			case QUIT :
				break;
			case PART :
				part(i, (*cmdRecv));
				break;
			case PING :
				if (_users[i].getIsConnected().size() == 5 && (*cmdRecv)->cmd.size() >= 2)
					response(RPL_PONG(addPrefix(_users[i]) ,(*cmdRecv)->cmd[1]), _users[i].getSocket());
				break;
			case PONG :
				break ;
			case USER :
				if (_users[i].getIsConnected().size() != 5)
					setUser(i, (*cmdRecv));
				else
					userhost(i, (*cmdRecv));
				break ;
			case PASS :
				pass(i, (*cmdRecv));
				break ;
			case CAP_LS :
				CapLs(i, (*cmdRecv));
				break ;
			default:
				std::cout << "Command is UNKNOWN" << std::endl;
				break;
		}
		if (_users[i].getIsConnected().size() == 4)
			connectUser(i);
	}
	for (cmdRecv = prot.begin(); cmdRecv != prot.end(); cmdRecv++)
	{
		delete *cmdRecv;
	}
	std::cout << _users[i].getBuffer();
	_users[i].clearBuffer();
}
