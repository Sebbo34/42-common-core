/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:50:15 by seb               #+#    #+#             */
/*   Updated: 2024/06/01 17:10:56 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name)
{
    Zombie  *zombHorde = new Zombie[N];
    int     i;

    i = 0;

    while (i < N)
    {
        zombHorde[i].setName(name);
        i++; 
    }
    return (zombHorde);
}
