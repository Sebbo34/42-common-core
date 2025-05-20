/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:46:12 by seb               #+#    #+#             */
/*   Updated: 2024/05/26 11:16:35 by sbo              ###   ########.fr       */
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
		
		bool	operator>(Fixed const & fixed);
		bool	operator<(Fixed const & fixed);
		bool	operator>=(Fixed const & fixed);
		bool	operator<=(Fixed const & fixed);
		bool	operator==(Fixed const & fixed);
		bool	operator!=(Fixed const & fixed);
	
		float 	operator+(Fixed const & fixed);
		float 	operator-(Fixed const & fixed);
		float 	operator*(Fixed const & fixed);
		float 	operator/(Fixed const & fixed);

		Fixed 	operator++(int);
		Fixed 	operator++();
		Fixed 	operator--(int);
		Fixed 	operator--();

		int     getRawBits( void ) const;
		void    setRawBits( int const raw );
		int     toInt( void ) const;
		float   toFloat( void ) const;
		
		static Fixed	min(Fixed const &a, Fixed const &b);
		static Fixed	min(Fixed &a, Fixed &b);
		static Fixed	max(Fixed const &a, Fixed const &b);
		static Fixed	max(Fixed &a, Fixed &b);
};

std::ostream & operator<<(std::ostream & o, Fixed const & fixed_number);

#endif