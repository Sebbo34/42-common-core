/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:21:35 by seb               #+#    #+#             */
/*   Updated: 2024/07/09 03:54:17 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main()
{
    ScavTrap scav("Scav");

    scav.attack("target");
    scav.takeDamage(3);
    ScavTrap test = scav;
    std::cout << scav.getHitPoint() << std::endl;
    scav.beRepaired(54);
    std::cout <<scav.getHitPoint() << std::endl;
    std::cout << test.getName() << " " << test.getHitPoint() << std::endl;
    scav.guardGate();
}