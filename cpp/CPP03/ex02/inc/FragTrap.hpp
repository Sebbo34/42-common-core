/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:32 by seb               #+#    #+#             */
/*   Updated: 2024/07/09 04:18:41 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_H
#define FRAGTRAP_H

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
	public :
		FragTrap (std::string name);
		~FragTrap(void);
		FragTrap (FragTrap const & src);
		FragTrap &operator=(FragTrap const & Frag);

		void highFivesGuys(void);
};

#endif