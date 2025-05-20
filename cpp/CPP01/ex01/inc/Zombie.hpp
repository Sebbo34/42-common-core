/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:30:41 by seb               #+#    #+#             */
/*   Updated: 2024/06/01 17:10:21 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>

class Zombie
{
    private :
        std::string name;
    public :
        Zombie();
        ~Zombie();
        void    announce(void);
        void    setName(std::string name);
};

Zombie*    zombieHorde( int N, std::string name );

#endif