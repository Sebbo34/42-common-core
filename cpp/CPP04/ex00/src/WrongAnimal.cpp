/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:01:03 by sbo               #+#    #+#             */
/*   Updated: 2024/07/15 07:54:20 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("WrongAnimal")
{
	std::cout << "WrongAnimal constructor called" << std::endl;
	return ;
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << "WrongAnimal destructor called" << std::endl;
	return ;
}

WrongAnimal::WrongAnimal (WrongAnimal const & src)
{
	std::cout << "Wrong Animal copy constructor called" << std::endl;
	*this = src;
	return ;
}

std::string	WrongAnimal::getType(void) const
{
	return (this->type);
}
void	WrongAnimal::makeSound()
{
	std::cout << "rrrrrow" << std::endl;
}


WrongAnimal & WrongAnimal::operator=(WrongAnimal const & wrongAnimal)
{
	if (this != &wrongAnimal)
	{
		this->type = wrongAnimal.getType();
	}
	return *this;
}