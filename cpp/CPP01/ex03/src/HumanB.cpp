/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:26:09 by seb               #+#    #+#             */
/*   Updated: 2024/07/03 15:42:45 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : name(name)
{
    std::cout << "Constructor called" << std::endl;
    return ;
}

HumanB::~HumanB()
{
	std::cout << "Destructor called" << std::endl;
    return ;
}

void    HumanB::setWeapon(Weapon &weapon)
{
	this->weapon = &weapon;
	return ;
}

void    HumanB::attack(void)
{
    if (this->weapon)
    {
        std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
    }
    else
        std::cout << this->name << " can't attack without weapon " << std::endl;
    return ;
}