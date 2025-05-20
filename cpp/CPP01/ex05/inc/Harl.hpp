/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:02:28 by seb               #+#    #+#             */
/*   Updated: 2024/06/01 18:25:20 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP 
# define HARL_HPP

#include <iostream>
class Harl
{ 
	private :
		void debug(void);
		void info(void);
		void warning(void);
		void error(void);
		
	public :
		Harl(void);
		~Harl(void);
		void    complain( std::string level );
};


#endif