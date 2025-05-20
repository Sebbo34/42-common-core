/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiu <lchiu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:19:33 by sbo               #+#    #+#             */
/*   Updated: 2024/08/08 16:54:42 by lchiu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/channel.hpp"

channel & channel::operator=(channel const & channel)
{
	if (this != &channel)
	{
		_name = channel._name;
		_users = channel._users;
		_operators = channel._operators;
		_topic = channel._topic;
	}
	return *this;
}

void	channel::removeUser(user userToRemove)
{
	std::vector<user>::iterator userInChan;
	for (userInChan = _users.begin(); userInChan != _users.end(); userInChan++)
	{
		if ((*userInChan).getSocket() == userToRemove.getSocket())
		{
			_users.erase(userInChan);
			break;
		}
	};
	for (userInChan = _operators.begin(); userInChan != _operators.end(); userInChan++)
	{
		if ((*userInChan).getSocket() == userToRemove.getSocket())
		{
			_operators.erase(userInChan);
			break;
		}
	};
}

// Setters
void channel::setName(const std::string &newName) {
	_name = newName;
}

void	channel::setLimit(int lim)
{
    _limit = lim;
}

void		channel::setPass(std::string const pass)
{
    _pswd = pass;
}

void			channel::setuserNb(int nb)
{
	_usersNb = nb;
}

void    channel::setInviteOnly(bool n)
{
    _invitOnly = n;
}

void    channel::setOptionT(bool n)
{
    _optionT = n;
}

// Getters
std::string &channel::getName() {
	return _name;
}

std::vector<user> &channel::getUsers() {
	return _users;
}

std::vector<user> &channel::getOperators() {
	return _operators;
}

std::vector<std::string> &channel::getInvitation() {
	return _invitation;
}

std::vector<std::string> &channel::getTopic() {
	return _topic;
}

std::string	channel::getPass() const
{
    return _pswd;
}

std::string	channel::getChannelName() const
{
    return _pswd;
}

int     channel::getLimit() const
{
    return _limit;
}

int		channel::getuserNb() const
{
	return _usersNb;
}

bool    channel::getInviteOnly()
{
    return _invitOnly;
}

bool    channel::getOptionT()
{
    return _optionT;
}

void channel::pushUsers(user &newUser) 
{
	_users.push_back(newUser);
}

void channel::pushOperators(user &newOperator) 
{
	_operators.push_back(newOperator);
}

void channel::pushInvitation(std::string userToInvite) {
	_invitation.push_back(userToInvite);
}

void channel::clearInvitation(std::string userToDelete) 
{
	std::vector<std::string>::iterator userInvited;
	for (userInvited = _invitation.begin(); userInvited != _invitation.end(); userInvited++)
	{
		if ((*userInvited).compare(userToDelete) == 0)
		{
			_invitation.erase(userInvited);
			break;
		}
	};}

void channel::pushTopic(std::string name, std::string subject, std::string time) 
{
	_topic.push_back(name);
	_topic.push_back(subject);
	_topic.push_back(time);
}

void channel::clearTopic() 
{
	_topic.clear();
}

void	channel::incementUserNb()
{
	_usersNb++;
}

void	channel::decementUserNb()
{
	if (_usersNb != 0)
		_usersNb--;
}
