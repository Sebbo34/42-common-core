/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:21:35 by seb               #+#    #+#             */
/*   Updated: 2024/07/09 04:13:36 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
    FragTrap Frag("Frag");

    Frag.attack("target");
    Frag.takeDamage(3);
    FragTrap test = Frag;
    std::cout << Frag.getHitPoint() << std::endl;
    Frag.beRepaired(54);
    std::cout <<Frag.getHitPoint() << std::endl;
    std::cout << test.getName() << " " << test.getHitPoint() << std::endl;
    Frag.highFivesGuys();
}