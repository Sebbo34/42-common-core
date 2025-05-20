/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:13:01 by seb               #+#    #+#             */
/*   Updated: 2024/05/09 22:12:19 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>

class ClapTrap 
{
	private :
		std::string name;
		int			HitPoint;
		int			EnergyPoint;
		int			AttackDamage;
	public :
		ClapTrap (std::string name);
		~ClapTrap(void);
		ClapTrap (ClapTrap const & src);
		ClapTrap &operator=(ClapTrap const & Clap);
		 
		std::string getName(void) const;
		int 		getHitPoint(void) const;

		void attack(const std::string& target);  
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

#endif