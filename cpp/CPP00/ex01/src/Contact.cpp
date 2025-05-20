/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:20:19 by sbo               #+#    #+#             */
/*   Updated: 2024/07/03 12:45:32 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

int isprintable(std::string line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!isprint(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	Contact::setFirstName(void)
{
	std::string line;
	while (1)
	{
		std::cout << "First name : ";
		getline(std::cin, line);
		if (std::cin.eof())
		{
			std::cin.clear();
			clearerr(stdin);
			std::cout << std::endl;
		}
		else if (!line.empty())
		{	
			if (isprintable(line) == 1)
			{
				this->firstName = line;
				break;
			}
		}	
	}
}
void	Contact::setNickName(void)
{
	std::string line;
	while (1)
	{
		std::cout << "Nick name : ";
		getline(std::cin, line);
		if (std::cin.eof())
		{
			std::cin.clear();
			clearerr(stdin);
			std::cout << std::endl;
		}
		else if (!line.empty())
		{	
			if (isprintable(line) == 1)
			{
				this->nickName = line;
				break;
			}
		}	
	}
}
void	Contact::setLastName(void)
{
		std::string line;
	while (1)
	{
		std::cout << "Last name : ";
		getline(std::cin, line);
		if (std::cin.eof())
		{
			std::cin.clear();
			clearerr(stdin);
			std::cout << std::endl;
		}
		else if (!line.empty())
		{	
			if (isprintable(line) == 1)
			{
				this->lastName = line;
				break;
			}
		}	
	}
}
void	Contact::setPhoneNumber(void)
{
		std::string line;
	while (1)
	{
		std::cout << "Phone Number: ";
		getline(std::cin, line);
		if (std::cin.eof())
		{
			std::cin.clear();
			clearerr(stdin);
			std::cout << std::endl;
		}
		else if (!line.empty())
		{	
			if (isprintable(line) == 1)
			{
				this->phoneNumber = line;
				break;
			}
		}	
	}
}
void	Contact::setDarkestSecret(void)
{
		std::string line;
	while (1)
	{
		std::cout << "Darkest Secret : ";
		getline(std::cin, line);
		if (std::cin.eof())
		{
			std::cin.clear();
			clearerr(stdin);
			std::cout << std::endl;
		}
		else if (!line.empty())
		{	
			if (isprintable(line) == 1)
			{
				this->darkestSecret = line;
				break;
			}
		}	
	}
}

void	Contact::setContact(void)
{
	this->setFirstName();
	this->setNickName();
	this->setLastName();
	this->setPhoneNumber();
	this->setDarkestSecret();
}

void	print_10(std::string str)
{
	int len;
	int i;
	
	i = 0;
	len = str.length();
	while(len < 10)
	{
		std::cout << " ";
		len++;
		i++;
	}
	len = i;
	i = 0;
	while (len + i < 10)
	{
		if (str[i + 1] && len + i == 9)
			std::cout << ".";
		else
			std::cout << str[i];
		i++;
	}
}

void	Contact::PrintName(void)
{
	print_10(this->firstName);
	std::cout << "|" ;
	print_10(this->nickName );
	std::cout << "|" ;
	print_10(this->lastName );
	std::cout << std::endl;
}

void	Contact::PrintContact(void)
{
	std::cout << "First Name:" << this->firstName << std::endl;
	std::cout << "Last Name:" << this->lastName << std::endl;
	std::cout << "Nick Name:" << this->nickName << std::endl;
	std::cout << "Phone Number:" << this->phoneNumber << std::endl;
	std::cout << "Darkest Secret:" << this->darkestSecret << std::endl;
}