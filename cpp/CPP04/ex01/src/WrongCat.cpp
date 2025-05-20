/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:00:04 by sbo               #+#    #+#             */
/*   Updated: 2024/07/16 18:53:24 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal()
{
	type = "WrongCat";
	std::cout << "WrongCat constructor called" << std::endl;
	return ;
}

WrongCat::~WrongCat(void)
{
	std::cout << "WrongCat destructor called" << std::endl;
	return ;
}

WrongCat & WrongCat::operator=(WrongCat const & wrongCat)
{
	if (this != &wrongCat)
	{
		this->type = wrongCat.getType();
	}
	return *this;
}

WrongCat::WrongCat (WrongCat const & src)
{
	std::cout << "Wrong Cat copy constructor called" << std::endl;
	*this = src;
	return ;
}

void	WrongCat::makeSound() const
{
	std::cout << "miauwww" << std::endl;
}
