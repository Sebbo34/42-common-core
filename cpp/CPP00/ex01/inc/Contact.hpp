/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:25:13 by seb               #+#    #+#             */
/*   Updated: 2024/06/01 15:22:04 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <cstdio>

class Contact
{
	private :
		std::string	firstName;
		std::string	lastName;
		std::string	nickName;
		std::string	darkestSecret;
		std::string	phoneNumber;
	public :
		void	setFirstName(void);
		void	setNickName(void);
		void	setLastName(void);
		void	setPhoneNumber(void);
		void	setDarkestSecret(void);
		void	setContact(void);
		void	PrintName(void);
		void	PrintContact(void);
};

#endif