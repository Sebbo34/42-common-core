/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   authentification.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:22:25 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 09:06:07 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void	Server::pass(int i, protocol *prot)
{
	if (prot->cmd.size() == 2 && _users[i].getIsConnected().find("P") == std::string::npos)
	{
		if (prot->cmd[1].compare(_pwd) == 0)
			_users[i].setIsConnected(_users[i].getIsConnected() + "P");
		else
			response(":server 464 : Password incorrect\r\n", _users[i].getSocket());
	}
}

void	Server::CapLs(int i, protocol *prot)
{
	if (prot->cmd.size() == 2 && _users[i].getIsConnected().size() != 5)
	{
		if (prot->cmd[1].compare("LS") == 0 &&  _users[i].getIsConnected().find("C") == std::string::npos)
			_users[i].setIsConnected(_users[i].getIsConnected() + "C");
	}
}

void	Server::connectUser(int i)
{
	std::string strusertmp = "001 " + _users[i].getNickName() + " :Bienvenue sur Ft_IRC\r\n"; 
	send(_users[i].getSocket(), strusertmp.c_str(), strusertmp.length(), 0);
	_users[i].setIsConnected(_users[i].getIsConnected() + "1");
}