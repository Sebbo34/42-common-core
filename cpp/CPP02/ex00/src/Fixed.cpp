/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:46:16 by seb               #+#    #+#             */
/*   Updated: 2024/05/03 02:44:12 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void)
{
    this->fixed_nbr = 0;
    std::cout << "Constructor Called" << std::endl;
    return ;
}

Fixed::~Fixed(void)
{
    std::cout << "Destructor Called" << std::endl;
    return ;
}

Fixed::Fixed (Fixed const & src)
{
    std::cout << "Copy constructor Called" << std::endl;
    *this = src;
    return ;
}

Fixed & Fixed::operator=(Fixed const & fixed)
{
    if ( this != &fixed)
        this->fixed_nbr = fixed.getRawBits();
    return *this;
}

int Fixed::getRawBits( void ) const
{
    std::cout << "getRawbits function Called" << std::endl;
    return (this->fixed_nbr);
}

void Fixed::setRawBits( int const raw )
{
    this->fixed_nbr = raw;
    return ;
}