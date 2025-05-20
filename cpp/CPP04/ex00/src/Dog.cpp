/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:00:00 by sbo               #+#    #+#             */
/*   Updated: 2024/07/16 18:30:48 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal()
{
	type = "Dog";
	std::cout << "Dog constructor called" << std::endl;
	return ;
}

Dog::~Dog(void)
{
	std::cout << "Dog destructor called" << std::endl;
	return ;
}

void	Dog::makeSound() const
{
	std::cout << "OUAF" << std::endl;
}

Dog & Dog::operator=(Dog const & dog)
{
	if (this != &dog)
	{
		this->type = dog.type;
	}
	return *this;
}

Dog::Dog (Dog const & src)
{
	std::cout << "Dog copy constructor called" << std::endl;
	*this = src;
	return ;
}