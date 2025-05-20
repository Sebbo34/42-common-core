/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:33:56 by sbo               #+#    #+#             */
/*   Updated: 2024/08/14 12:36:19 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void Server::quit(user user1)
{
	std::vector<std::string>::iterator it1;
	std::vector<user>::iterator it2;
	std::vector<std::string>::iterator it3;

	for (it1 = user1.getChannels().begin(); it1 != user1.getChannels().end(); it1++)
	{
		for (it2 = _channels[*it1].getUsers().begin(); it2 != _channels[*it1].getUsers().end(); it2++)
		{
			if ((*it2).getSocket() == user1.getSocket())
			{
				_channels[*it1].getUsers().erase(it2);
				empty_chanel(*it1);
				break;
			}
		};
		for (it2 = _channels[*it1].getOperators().begin(); it2 != _channels[*it1].getOperators().end(); it2++)
		{
			if ((*it2).getSocket() == user1.getSocket())
			{
				_channels[*it1].getOperators().erase(it2);
				empty_chanel(*it1);
				break;
			}
		};
		for (it3 = _channels[*it1].getInvitation().begin(); it3 != _channels[*it1].getInvitation().end(); it3++)
		{
			if ((*it3) == user1.getNickName())
			{
				_channels[*it1].getInvitation().erase(it3);
				empty_chanel(*it1);
				break ;
			}
		};
		sendRPL (_channels[*it1], RPL_QUIT(addPrefix(user1), (*it1), "Lost terminal"));
	}
	for (it2 = _users.begin(); it2 != _users.end(); it2++)
	{
		if ((*it2).getSocket() == user1.getSocket())
		{
			_users.erase(it2);
			break;
		}
	}
}