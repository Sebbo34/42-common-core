/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:30:41 by seb               #+#    #+#             */
/*   Updated: 2024/06/01 16:58:29 by sbo              ###   ########.fr       */
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

void randomChump( std::string name );
Zombie* newZombie( std::string name );
#endif