/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:29:10 by seb               #+#    #+#             */
/*   Updated: 2024/06/01 15:11:21 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <iostream>
#include "Contact.hpp"
class PhoneBook
{
	private:
		Contact rep[8];
	public :
		PhoneBook(void);
		~PhoneBook(void);
		void	ADD(int index);
		void	print(int index);
		void	Search(int index);
		void	ChooseContact(int n);
};

#endif