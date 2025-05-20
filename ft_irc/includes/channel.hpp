/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:10:51 by sbo               #+#    #+#             */
/*   Updated: 2024/08/13 17:17:08 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include "user.hpp"
class channel
{
	private :
		std::string					_name;
		std::vector<std::string>	_topic;
		std::vector<user>			_users;
		std::vector<user>			_operators;
		std::vector<std::string>	_invitation;
		std::string					_pswd;
		int							_limit;
		int							_usersNb;
		bool						_invitOnly;
		bool						_optionT;
		
	public:
		void						setPass(std::string const pass);
		void						setLimit(int lim);
		void						setuserNb(int nb);
		void						setInviteOnly(bool n);
		void						setOptionT(bool n);
		std::string					&getName() ;
		std::vector<user>			&getUsers() ;
		std::vector<user>			&getOperators() ;
		std::vector<std::string>	&getInvitation() ;
		std::vector<std::string>	&getTopic()  ;
		std::string					getPass() const;
		std::string					getChannelName() const;
		int							getLimit() const;
		int							getuserNb() const;
		bool						getInviteOnly();
		bool						getOptionT();

		void						incementUserNb();
		void						decementUserNb();

		channel						&operator=(channel const & channel);
		void						setName(const std::string &newName);
		void						pushUsers(user &newUser);
		void						pushOperators(user &newOperator);
		void						pushInvitation(std::string userToInvite);
		void						clearInvitation(std::string userToDelete);
		void						removeUser(user userToRemove);
		void						pushTopic(std::string name, std::string subject, std::string time);
		void						clearTopic();

};

#endif