/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:46:16 by seb               #+#    #+#             */
/*   Updated: 2024/07/06 14:15:32 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void)
{
	this->fixed_nbr = 0;
	std::cout << "Constructor Called" << std::endl;
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
	this->fixed_nbr = roundf (f * (1 << this->n )); // arrondi???
	std::cout << "Float constructor Called" << std::endl;
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
	if (this != &fixed)
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

bool	 Fixed::operator>(Fixed const & fixed)
{
	if (this->fixed_nbr > fixed.getRawBits())
		return (true);
	return (false);
}
bool	 Fixed::operator<(Fixed const & fixed)
{
	if (this->fixed_nbr < fixed.getRawBits())
		return (true);
	return (false);
}
bool	Fixed::operator>=(Fixed const & fixed)
{
	if (this->fixed_nbr >= fixed.getRawBits())
		return (true);
	return (false);
}
bool	Fixed::operator<=(Fixed const & fixed)
{
		if (this->fixed_nbr <= fixed.getRawBits())
		return (true);
	return (false);
}
bool	Fixed::operator==(Fixed const & fixed)
{
	if (this->fixed_nbr == fixed.getRawBits())
		return (true);
	return (false);
}
bool	Fixed::operator!=(Fixed const & fixed)
{
	if (this->fixed_nbr != fixed.getRawBits())
		return (true);
	return (false);
}

float 	Fixed::operator+(Fixed const & fixed)
{
	return (this->toFloat() + fixed.toFloat());
}
float 	Fixed::operator-(Fixed const & fixed)
{
	return (this->toFloat() - fixed.toFloat());
}

float 	Fixed::operator*(Fixed const & fixed)
{
	return (this->toFloat() * fixed.toFloat());
}

float 	Fixed::operator/(Fixed const & fixed)
{
	return (this->toFloat() / fixed.toFloat());
}

Fixed 	Fixed::operator++(int)
{
	this->fixed_nbr++;
	return (*this);
}

Fixed 	Fixed::operator++()
{
	++this->fixed_nbr;
	return (*this);
}

Fixed 	Fixed::operator--(int)
{
	this->fixed_nbr--;
	return (*this);
}

Fixed 	Fixed::operator--()
{
	--this->fixed_nbr;
	return (*this);
}

Fixed	Fixed::min(Fixed const &a, Fixed const &b)
{
	if (a.getRawBits() < b.getRawBits())
		return (a);
	return (b);
}

Fixed	Fixed::min(Fixed &a, Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

Fixed	Fixed::max(Fixed const &a, Fixed const &b)
{
	if (a.getRawBits() > b.getRawBits())
		return (a);
	return (b);
}

Fixed	Fixed::max(Fixed &a, Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}