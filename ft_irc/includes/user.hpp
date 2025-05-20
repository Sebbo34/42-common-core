/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:10:57 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 17:13:52 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>

enum CommandType {
    NICK,
    USER,
    JOIN,
    MODE,
    TOPIC,
    INVITE,
    KICK,
    PRIVMSG,
    QUIT,
    PING,
    PONG,
    PART,
	USERHOST,
	PASS,
	CAP_LS,
    UNKNOWN
};

struct protocol
{
	std::string					prefix;
	std::vector<std::string>	cmd;
	CommandType					type;
};


class user
{
	private :
		std::vector <std::string>	_channels;
		std::string					_nickName;
		std::string					_userName;
		std::string					_hostName;
		std::string					_serverName;
		std::string					_buffer;
		int							_socket;
		std::string					_isConnected;

	public :
		user & operator=(user const & src);
		void	removeChannel(std::string channel);
	
		std::vector<std::string>		&getChannels() ;
		std::string						getNickName() const;
		std::string						getUserName() const;
		std::string						getHostName() const;
		std::string						getServerName() const;
		int								getSocket() const;
		std::string						getIsConnected() const;
		std::string						&getBuffer();

		void							pushChannel(std::string chan);
		void							setNickName(const std::string &newNickName);
		void							setUserName(const std::string &newUserName);
		void							setHostName(const std::string &newHostName);
		void							setServerName(const std::string &newServerName);
		void							setSocket(int newSocket);
		void							setIsConnected(std::string var);
		void							setBuffer(std::string buffer);
		void							clearBuffer();
};

std::vector<protocol *>		parseClientRecv(std::string recv);
std::vector<std::string>	ft_split(std::string input);
protocol					*parse_one_cmd(std::string input);

#endif