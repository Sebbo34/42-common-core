/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:57:34 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 11:42:39 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include<vector>
#include "../includes/user.hpp"

CommandType toCmdType(int command) {
    switch (command) {
        case 0: return NICK;
        case 1: return USERHOST;
        case 2: return JOIN;
        case 3: return MODE;
        case 4: return TOPIC;
        case 5: return INVITE;
        case 6: return KICK;
        case 7: return PRIVMSG;
		case 8: return QUIT;
        case 9: return PING;
        case 10: return PONG;
		case 11: return PART;
		case 12: return CAP_LS;
		case 13: return PASS;
		case 14: return USER;
        default: return UNKNOWN;
    }
}

CommandType is_cmd(std::string cmd)
{
	std::string existing_cmd[15] = {"NICK", "userhost", "JOIN", "MODE", "TOPIC", "INVITE", "KICK", "PRIVMSG", "QUIT", "PING", "PONG", "PART", "CAP", "PASS", "USER"};
	for (int i = 0; i < 15 ; i++)
	{
		if (cmd.compare(existing_cmd[i]) == 0)
		{
			return toCmdType(i);
		}
	}
	return (UNKNOWN);
}

std::vector<std::string> ft_split(std::string input)
{
	std::vector<std::string> split;

	while (!input.empty())
	{
		if (input.find(" ") == input.npos)
			break;
		if (!input.substr(0, input.find(" ")).empty())
		{
			split.push_back(input.substr(0, input.find(" ")));
		}
		input.erase(0, input.find(" ") + 1);
		if (input[0] == ':')
			break;
	}
	if (!input.empty())
	{
		if (input.find("\r\n") != input.npos)
			input.erase(input.find("\r"), 2);
		split.push_back(input.substr(0, input.size()));
	}
	return (split);
}

protocol *parse_one_cmd(std::string input)
{
	protocol *prot = new protocol;
	std::vector<std::string> split;
	if (input.empty())
		return (prot);
	split = ft_split(input);
	if (input[0] == ':')
	{
		prot->prefix = split[0];
		split.erase(split.begin());
	}
	else
		prot->prefix = "";
	prot->type = is_cmd(split[0]);
	if (prot->type != UNKNOWN)
		prot->cmd = split;
	else
	{
		std::cout << "Command not found " << std::endl;
		delete prot;
		return (NULL);
	}
	return prot;
}

std::vector<protocol *> parseClientRecv(std::string recv)
{
	std::vector<protocol *>	inputClient;
	protocol				*prot;
	while (!recv.empty())
	{
		if (recv.find("\r\n") == recv.npos)
			break;
		if (recv.find("\r\n") == std::string::npos)
			prot = NULL;
		else
			prot = parse_one_cmd(recv.substr(0,recv.find("\r\n")));
		if (prot)
			inputClient.push_back(prot);
		recv.erase(0, recv.find("\r\n")+2);
	}
	return (inputClient);
}
