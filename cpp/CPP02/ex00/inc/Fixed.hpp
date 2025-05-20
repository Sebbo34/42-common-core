/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:46:12 by seb               #+#    #+#             */
/*   Updated: 2024/05/03 02:29:31 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP 
#define FIXED_HPP 

#include <iostream>

class Fixed 
{
    private :
        static const int n = 8;
        int             fixed_nbr;
    public :
        Fixed(void);
        ~Fixed(void);
        Fixed (Fixed const & src);
        Fixed &operator=(Fixed const & fixed);

        int getRawBits( void ) const;
        void setRawBits( int const raw );
};


#endif