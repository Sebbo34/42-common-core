/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:13:03 by seb               #+#    #+#             */
/*   Updated: 2024/07/09 04:14:53 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap (std::string name)
{
    this->name = name;
    this->HitPoint = 10;
	this->EnergyPoint = 10;
	this->AttackDamage = 0;
    std::cout << "Clap constructor called" << std::endl;
    return ;
}

ClapTrap::~ClapTrap(void)
{
    std::cout << "Clap destructor called" << std::endl;
    return ;
}

ClapTrap::ClapTrap (ClapTrap const & src)
{
    std::cout << "Clap copy constructor called" << std::endl;
	*this = src;
	return ;
}

std::string ClapTrap::getName(void) const
{
    return (this->name);
}

int ClapTrap::getHitPoint(void) const
{
    return (this->HitPoint);
}

int ClapTrap::getAttackDamage(void) const
{
    return (this->AttackDamage);
}
int ClapTrap::getEnergyPoint(void) const
{
    return (this->EnergyPoint);
}

ClapTrap & ClapTrap::operator=(ClapTrap const & Clap)
{
    if (this != &Clap)
    {
        this->name = Clap.getName();
        this->HitPoint = Clap.getHitPoint();
        this->AttackDamage = Clap.getAttackDamage();
        this->EnergyPoint = Clap.getEnergyPoint();
    }
	return *this;
}

void ClapTrap::attack(const std::string& target)
{
    if (this->HitPoint == 0)
    {
        std::cout << this->name << " is dead " << std::endl;
        return ;
    }
    if (this->EnergyPoint > 0)
    {   
        std::cout << this->name << " attacks " << target << ", causing " << this->AttackDamage << " points of damage!" << std::endl;
        this->EnergyPoint--;
    }
    else
        std::cout << this->name << " doesn't have enought energy to attack " << std::endl;
    return ;
}  

void ClapTrap::takeDamage(unsigned int amount)
{
    std::cout << this->name << " takes " << amount << " points of damage!" << std::endl;
    this->HitPoint -= amount;
    if (this->HitPoint < 0)
         this->HitPoint = 0;
    return ;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->HitPoint == 0)
    {
        std::cout << this->name << " is dead " << std::endl;
        return ;
    }
    if (this->EnergyPoint > 0)
    {
        std::cout << this->name << " heals " << amount << " HitPoint " << std::endl;
        this->HitPoint += amount;
        this->EnergyPoint--;
    }
    else
        std::cout << this->name << " doesn't have enought energy to heal " << std::endl;
    return ;
}

void    ClapTrap::setHitPoint(int value)
{
    this->HitPoint = value;
    return ;
}

void    ClapTrap::setEnergyPoint(int value)
{
    this->EnergyPoint = value;
    return ;
}
        
void    ClapTrap::setAttackDamage(int value)
{
    this->AttackDamage = value;
    return ;
}
void    ClapTrap::setName(std::string name)
{
    this->name = name;
    return ;
}