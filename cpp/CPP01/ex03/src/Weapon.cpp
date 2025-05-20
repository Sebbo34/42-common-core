/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:26:16 by seb               #+#    #+#             */
/*   Updated: 2024/07/03 15:44:37 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon()
{
    std::cout << "Constructor called" << std::endl;
    return ;
}

Weapon::Weapon(std::string arme) : type(arme)
{
    std::cout << "Constructor called" << std::endl;
    return ;
}

Weapon::~Weapon(void)
{
    std::cout << "Destructor called" << std::endl;
    return ;
}

const std::string &Weapon::getType(void)
{
    const std::string &ref = this->type;
    return (ref);
}
std::string Weapon::gettype(void)
{
    return (this->type);
}

void    Weapon:: setType(std::string type)
{
    this->type = type;
    return ;
}