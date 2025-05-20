/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:26:04 by seb               #+#    #+#             */
/*   Updated: 2024/05/31 10:41:51 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) :  name(name), weapon(weapon)
{
    std::cout << "Constructor called" << std::endl;
    return ;
}

HumanA::~HumanA()
{
     std::cout << "Destructor called" << std::endl;
    return ;
}

void    HumanA::attack(void)
{
    const std::string &str = this->weapon.getType();
    std::cout << this->name << " attacks with their " << str << std::endl;
    return ;
}