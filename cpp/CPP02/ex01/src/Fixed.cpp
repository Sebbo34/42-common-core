/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:46:16 by seb               #+#    #+#             */
/*   Updated: 2024/07/06 14:14:20 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void)
{
    this->fixed_nbr = 0;
    std::cout << "Default constructor called" << std::endl;
    return ;
}

Fixed::Fixed(int const i)
{
    this->fixed_nbr = i << this->n;
    std::cout << "Int constructor called" << std::endl;
    return ;
}

Fixed::Fixed(float const f)
{
    this->fixed_nbr = roundf (f * (1 << this->n ));
    std::cout << "Float constructor Called" << std::endl;
    return ;
}

Fixed::~Fixed(void)
{
    std::cout << "Destructor called" << std::endl;
    return ;
}

Fixed::Fixed (Fixed const & src)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
    return ;
}

Fixed & Fixed::operator=(Fixed const & fixed)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if ( this != &fixed)
        this->fixed_nbr = fixed.getRawBits();
    return *this;
}

int Fixed::getRawBits( void ) const
{
    return (this->fixed_nbr);
}

void Fixed::setRawBits( int const raw )
{
    this->fixed_nbr = raw;
    return ;
}

int     Fixed::toInt( void ) const
{
    return (this->fixed_nbr >> this->n);
}

int   pui(int n, int exp)
{
    int tmp;

    if (exp == 0)
        return (1); 
    tmp = n;
    while (exp > 1)
    {
        n = n * tmp;
        exp--;
    }
    return (n);
} 

float   Fixed::toFloat( void ) const
{
    float   dec;
    int     fixed_dec;
    int     ent;
    int     exp = this->n - 1;

    dec = 0;
    ent = this->toInt();
    fixed_dec = this->fixed_nbr - (ent << this->n);
    while (exp >= 0)
    {
        if (fixed_dec >= pui(2, exp))
        {
            dec = dec + 1.00f / pui(2, this->n - exp);
            fixed_dec = fixed_dec % pui(2, exp);
        }
        exp--;
    }
    return (ent + dec);
}

std::ostream & operator<<(std::ostream & o, Fixed const & fixed_number)
{
    o << fixed_number.toFloat();
    return o;
}