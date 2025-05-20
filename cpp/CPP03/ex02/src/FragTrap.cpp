/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:30 by seb               #+#    #+#             */
/*   Updated: 2024/07/11 21:59:08 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap (std::string name) : ClapTrap(name)
{
    HitPoint = 100;
    AttackDamage = 100;
    EnergyPoint = 30;
    std::cout << "FragTrap constructor called" << std::endl;

    return ;
}

FragTrap::~FragTrap(void)
{
    std::cout << "FragTrap destructor called" << std::endl;
    return ;
}

FragTrap & FragTrap::operator=(FragTrap const & Frag) 
{
    if (this != &Frag)
    {
        AttackDamage = Frag.AttackDamage;
        name = Frag.name;
        EnergyPoint = Frag.EnergyPoint;
        HitPoint = Frag.HitPoint;
    }
	return *this;
}

FragTrap::FragTrap (FragTrap const & src) : ClapTrap(src.getName())
{
    std::cout << "Fragtrap copy constructor Called" << std::endl;
	*this = src;
	return ;
}
  

void    FragTrap::highFivesGuys(void)
{
    std::cout << this->getName() << " get a high-fives" << std::endl;
    return;
}
