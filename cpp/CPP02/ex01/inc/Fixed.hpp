/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:46:12 by seb               #+#    #+#             */
/*   Updated: 2024/05/09 13:43:46 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP 
#define FIXED_HPP 

#include <iostream>
#include <math.h>

class Fixed 
{
    private :
        static const int n = 8;
        int             fixed_nbr;
    public :
        Fixed(int const n);
        Fixed(float const f);
        Fixed(void);
        ~Fixed(void);
        Fixed (Fixed const & src);
        Fixed &operator=(Fixed const & fixed);

        int     getRawBits( void ) const;
        void    setRawBits( int const raw );
        int     toInt( void ) const;
        float   toFloat( void ) const;
        
};

std::ostream & operator<<(std::ostream & o, Fixed const & fixed_number);

#endif