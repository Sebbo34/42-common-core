/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userhost.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:27:25 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 08:48:52 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void	Server::userhost(int i, protocol *prot)
{
	if (_users[i].getIsConnected().size() != 5)
		return;
	if (prot->cmd.size() < 5)
		response(RPL_NEEDMOREPARAMS(_users[i].getNickName(), prot->cmd[0]), _users[i].getSocket());
	else if (prot->cmd.size() >= 5 && prot->cmd[4][0] == ':')
		response(RPL_ALREADYREGISTERED(_users[i].getNickName()), _users[i].getSocket());
	else if (prot->cmd.size() == 5 && prot->cmd[4][0] != ':')
	{
		response("Bad input\r\n", _users[i].getSocket());
		std::cout << "Bad Input" << std::endl;	
	}
	else
		std::cout << "Too many argument" << std::endl;
}

void	Server::setUser(int i, protocol *prot)
{
	if (prot->cmd.size() == 5 && _users[i].getIsConnected().size() != 5 && _users[i].getIsConnected().find("U") == std::string::npos && prot->cmd[4].size() > 1 && prot->cmd[4][0] == ':')
	{
		_users[i].setUserName(prot->cmd[1]);
		_users[i].setHostName(prot->cmd[2]);
		_users[i].setServerName(prot->cmd[3]);
		_users[i].setIsConnected(_users[i].getIsConnected() + "U");
	}
		else if (prot->cmd.size() == 5 && prot->cmd[4][0] != ':')
	{
		response("Bad input\r\n", _users[i].getSocket());
		std::cout << "Bad Input" << std::endl;	
	}
}