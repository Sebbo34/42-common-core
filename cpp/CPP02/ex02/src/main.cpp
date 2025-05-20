/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:46:18 by seb               #+#    #+#             */
/*   Updated: 2024/07/06 14:06:45 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main( void ) 
{
	/* Fixed a;
	Fixed b( 10 ); Fixed const c( 42.42f ); Fixed const d( b );
	a = Fixed( 1234.4321f ); //probleme avec les const
	
	if (b < a)
		std::cout << "<" << std::endl;
	if (b <= a)
		std::cout << "<=" << std::endl;
	if (a >= b)
		std::cout << ">=" << std::endl;
	if (a > b)
		std::cout << ">" << std::endl;
	if (b == 10)
		std::cout << "==" << std::endl;
	if (a != b)
		std::cout << "!=" << std::endl;
	
	Fixed const f( Fixed( 5.05f ) * Fixed( 2 ) );
	a = a*b;
	std::cout << a << std::endl;
	std::cout << a + b << std::endl;
	std::cout << f << std::endl;
	std::cout << a / b << std::endl; */
	
	Fixed a;
	Fixed b( Fixed( 5.05f ) * Fixed( 2 ) );
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout <<  a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;
	std::cout << Fixed::min( a, b ) << std::endl;

	return 0; 
}