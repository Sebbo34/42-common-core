/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:26:18 by seb               #+#    #+#             */
/*   Updated: 2024/07/03 15:28:01 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream>

class Weapon
{
    private:
        std::string type;
    public:
        Weapon(std::string type);
        Weapon();
        ~Weapon(void);
        Weapon &operator=(Weapon & weapon);
        const std::string   &getType(void);
        std::string   gettype(void);
        void                setType(std::string type);
};

#endif