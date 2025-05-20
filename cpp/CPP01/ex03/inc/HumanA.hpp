/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:26:07 by seb               #+#    #+#             */
/*   Updated: 2024/05/02 02:14:08 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include "Weapon.hpp"

class HumanA
{
private:
    std::string name;
    Weapon      &weapon;
public:
    HumanA(std::string name, Weapon &weapon);
    ~HumanA(void);
    void    attack(void);
};

#endif