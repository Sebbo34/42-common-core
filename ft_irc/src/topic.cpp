/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 02:13:25 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 08:17:55 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include <ctime>
#include <sstream>
#include <string>

void Server::setTopicForNewUser(int socket, std::vector<std::string> topic, std::string ChannelName)
{
	response(RPL_TOPIC_SET(topic[0], ChannelName, topic[1]), socket);
	response(RPL_TOPICWHOTIME(topic[0], ChannelName, topic[2]), socket);
}

void	sendNewTopic(channel chan, user sender, protocol *prot)
{
	std::vector<user>::iterator usersInChan;
	for (usersInChan = chan.getUsers().begin(); usersInChan != chan.getUsers().end(); usersInChan++)
	{
		if ((*usersInChan).getSocket() != sender.getSocket())
			ft_send((*usersInChan).getSocket(), RPL_TOPIC(addPrefix(sender), prot->cmd[1], prot->cmd[2]));
	};
	for (usersInChan = chan.getOperators().begin(); usersInChan != chan.getOperators().end(); usersInChan++)
	{
		if ((*usersInChan).getSocket() != sender.getSocket())
			ft_send((*usersInChan).getSocket(), RPL_TOPIC(addPrefix(sender), prot->cmd[1], prot->cmd[2]));
	};
}

void Server::topic(int i, protocol *prot)
{
	if ((prot->cmd.size() < 2) || _users[i].getIsConnected().size() != 5)
	{
		if (prot->cmd.size() < 2)
			response(ERR_NEEDMOREPARAMS( _users[i].getNickName(), prot->cmd[0]), _users[i].getSocket());
		return;
	}
	try 
	{
		_channels.at(prot->cmd[1]);
		if(prot->cmd.size() >= 3 && prot->cmd[2].size() > 0 && prot->cmd[2][0] == ':')
		{
			if ((isNickIn(_channels[prot->cmd[1]].getUsers(), _users[i].getNickName()) || isNickIn(_channels[prot->cmd[1]].getOperators(), _users[i].getNickName()))) 
			{
				int user_is_op = getIndUserByNN(_channels[prot->cmd[1]].getOperators(), _users[i].getNickName());
				if (_channels[prot->cmd[1]].getOptionT() == false || (_channels[prot->cmd[1]].getOptionT() == true && user_is_op != -1))
				{
					if (_channels[prot->cmd[1]].getTopic().size() != 0)
						_channels[prot->cmd[1]].clearTopic();
					response(RPL_TOPIC(addPrefix(_users[i]), prot->cmd[1], prot->cmd[2]), _users[i].getSocket());
					sendNewTopic(_channels[prot->cmd[1]], _users[i], prot);
					if (prot->cmd.size() == 3)
						prot->cmd[2].erase(0,1);
					time_t timestamp = time(NULL);
					_channels[prot->cmd[1]].pushTopic(_users[i].getNickName(), prot->cmd[2], to_str(timestamp));
				}
				else
				{
					response(ERR_CHANOPRIVSNEEDED( _users[i].getNickName(), prot->cmd[1]), _users[i].getSocket());
					std::cout << " You're not channel operator" << std::endl;
				}
			}
			else if (!isNickIn(_channels[prot->cmd[1]].getUsers(), _users[i].getNickName()))
				sendError(_users[i], "442", prot->cmd[1], "You're not on that channel");
			else if (isNickIn(_channels[prot->cmd[1]].getOperators(), _users[i].getNickName()))
				sendError(_users[i], "482", prot->cmd[1], "You're not channel operator");
		}
		else if (prot->cmd.size() == 2)
		{
			if ((isNickIn(_channels[prot->cmd[1]].getUsers(), _users[i].getNickName()) || isNickIn(_channels[prot->cmd[1]].getOperators(), _users[i].getNickName())))
			{
				if (_channels[prot->cmd[1]].getTopic().size() == 3)
				{
					response(RPL_TOPIC_SET(_channels[prot->cmd[1]].getTopic()[0], prot->cmd[1],_channels[prot->cmd[1]].getTopic()[1]), _users[i].getSocket());
					response(RPL_TOPICWHOTIME(_channels[prot->cmd[1]].getTopic()[0], prot->cmd[1], _channels[prot->cmd[1]].getTopic()[2]), _users[i].getSocket());	
				}
				else
					response("No Topic is set\r\n", _users[i].getSocket());
			}
			else if (!isNickIn(_channels[prot->cmd[1]].getUsers(), _users[i].getNickName()))
				sendError(_users[i], "442", prot->cmd[1], "You're not on that channel");
		}
		else
		{
			response("Bad input\r\n", _users[i].getSocket());
			std::cout << "Bad input" << std::endl;
		}
	}
	catch (std::exception const &e)
	{
		sendError(_users[i], "403", prot->cmd[1], "No such channel");
	}
}