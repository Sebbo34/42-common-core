/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:51:13 by seb               #+#    #+#             */
/*   Updated: 2024/07/03 12:26:45 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PhoneBook.hpp"

PhoneBook::PhoneBook(void)
{
	std::cout << "Contructor called" << std::endl;
	return ;
}

PhoneBook::~PhoneBook(void)
{
	std::cout << "Destructor called" << std::endl;
	return ;
}

void PhoneBook::ADD(int index)
{
	this->rep[index].setContact();
	return ;
}

void PhoneBook::Search(int index)
{
	int	i;
	i = 0;
	while (i < index && i < 8)
	{
		std::cout << "         " << i + 1 << "|";
		this->rep[i].PrintName();
		i++;
	}
}

void PhoneBook::print(int index)
{
	this->rep[index].PrintContact();
}

void	PhoneBook::ChooseContact(int n)
{
	int ind;
	ind = 0;
	std::string str;
	while (1)
	{
		std::cout << "Which contact : ";
		getline(std::cin, str);
		if (std::cin.eof())
		{
			std::cin.clear();
			clearerr(stdin);
			std::cout << std::endl;
		}
		else if (!str.empty())
		{	
			ind = str[0] - '0';
			if (str.length() != 1 || ind > n || ind <= 0)
				std::cout << "Bad Index please retry " << std::endl;
			else
			{
				this->print(ind - 1);
				break;
			}
		}	
	}
}
