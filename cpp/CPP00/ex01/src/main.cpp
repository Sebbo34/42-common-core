/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:47:25 by sbo               #+#    #+#             */
/*   Updated: 2024/07/03 12:54:51 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main()
{
	PhoneBook	PhoneBook;
	int			index;
	std::string input;
	int			n;

	index = -1;
	n = 0;
	std::cout << "Welcome to PhoneBook " << std::endl;
	std::cout << "Use ADD for add a new contact " << std::endl;
	std::cout << "Use SEARCH for search in the PhoneBook " << std::endl;
	std::cout << "Use EXIT for leave " << std::endl;
	while (1)
	{
		std::cout << "Type a command: ";
		getline(std::cin, input);
		if (std::cin.eof())
		{
			std::cin.clear();
			clearerr(stdin);
			std::cout << std::endl;
		}
		if (input.compare("ADD") == 0)
		{
			n++;
			if (n > 8)
				n = 8;
			index++;
			if (index == 8)
				index = 0;
			PhoneBook.ADD(index);
		}
		else if (input.compare("SEARCH") == 0 && n != 0)
		{
			PhoneBook.Search(n);
			PhoneBook.ChooseContact(n);
		}
		else if (input.compare("SEARCH") == 0 && n == 0)
			std::cout << "No Contact in this PhoneBook, please Add contact for use SEARCH" << std::endl;
		else if (input.compare("EXIT") == 0)
			break;
	}
}