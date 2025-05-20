/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:32 by seb               #+#    #+#             */
/*   Updated: 2024/07/11 21:56:33 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_H
#define SCAVTRAP_H

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
	public :
		ScavTrap (std::string name);
		~ScavTrap(void);
		ScavTrap (ScavTrap const & src);
		ScavTrap &operator=(ScavTrap const & Scav);

		void attack(const std::string& target);
		void guardGate(void);
};

#endif