/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:18:20 by sbo               #+#    #+#             */
/*   Updated: 2024/07/20 13:43:43 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iomanip>

ScalarConverter::ScalarConverter()
{
	std::cout << "Scalar Converter constructor called" << std::endl;
}

ScalarConverter::~ScalarConverter()
{
	std::cout << "Scalar Converter destructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &src)
{
	std::cout << "Scalar Converter copy constructor called" << std::endl;
	*this = src;
	return ;
}

ScalarConverter & ScalarConverter::operator=(ScalarConverter const &conv)
{
	if (this != &conv)
	{
	}
	return *this;
}

int   pui(float n, int exp)
{
	float tmp;

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
int	ft_atoi(std::string nptr, int *overflow)
{
	int		i;
	int		j;
	long	nbr;

	i = 0;
	nbr = 0;
	j = 0;
	if (nptr[0] == '-' || nptr[0] == '+')
		i++;
	while(nptr[i] == '0')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9' )
	{
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
		j++;
	}
	if (nbr == 2147483648)
		return (-2147483648);
	if (nbr > 2147483647 || j > 11)
		*overflow = 1;
	return (static_cast<int>(nbr));
}

double	ft_atoi_double(std::string nptr)
{
	int		i;
	double	nbr;
	int		j;

	i = 0;
	nbr = 0;
	if (nptr[0] == '-' || nptr[0] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9' )
	{
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	i++;
	j = 1;
	while (nptr[i] >= '0' && nptr[i] <= '9' )
	{
		nbr = nbr +  static_cast<double>(nptr[i] - '0') / pui(10, j);
		j++;
		i++;
	}
	return (nbr);
}

float	ft_atoi_float(std::string nptr)
{
	int		i;
	float	nbr;
	int		j;

	i = 0;
	nbr = 0;
	if (nptr[0] == '-' || nptr[0] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9' )
	{
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	i++;
	j = 1;
	while (nptr[i] >= '0' && nptr[i] <= '9' )
	{
		nbr = nbr + static_cast<float>(nptr[i] - '0') / pui(10, j);
		j++;
		i++;
	}
	return (nbr);
}

int	which_type(std::string src, int *negatif)
{
	int type;
	int	i;
	i = 0;
	type = 0;
	if ((src[0] < '0' || src[0] > '9') && src[0] != '-' && src[0] != '+')
	{
		if ( src.length() == 3 && src[0] == '\'' && src[2] == '\'')
		{
			type = 1;
		}
		else if (src.length() != 1)
			std::cout << "Error please try a correct litteral" << std::endl;
		else 
			type = 1;
	}
	else
	{
		if (src[0] == '-' || src[0] == '+')
		{
			if (src[0] == '-')
				*negatif = -1;
			i++;
		}
		while (src[i] && (src[i] >= '0' && src[i] <= '9'))
			i++;
		if (!src[i])
			type = 2;
		else if (src[i] == '.' && src[i + 1])
		{
			i++;
			while (src[i] && (src[i] >= '0' && src[i] <= '9'))
				i++;
			if (!src[i])
				type = 4;
			else if (src[i] == 'f' && !src[i + 1])
				type = 3;
			else
				std::cout << "Error please try a correct litteral" << std::endl;
		}
		else
			std::cout << "Error please try a correct litteral" << std::endl;
	}
	return type;
}

bool handle_special_lit(std::string src)
{
	if (src.compare("nan") == 0 || src.compare("-inf") == 0 || src.compare("+inf") == 0 || src.compare("inf") == 0)
	{
		std::cout << "char: " << "impossible" <<std::endl;
		std::cout << "int: " << "impossible" <<std::endl;
		std::cout << "float: " << src << "f" <<std::endl;
		std::cout << "double: " << src <<std::endl;
		return true;
	}
	if (src.compare("nanf") == 0 || src.compare("-inff") == 0 || src.compare("+inff") == 0 || src.compare("inff") == 0)
	{
		std::cout << "char: " << "impossible" <<std::endl;
		std::cout << "int: " << "impossible" <<std::endl;
		std::cout << "float: " << src <<std::endl;
		src.resize(src.size() - 1);
		std::cout << "double: " << src <<std::endl;
		return true;
	}
	return (false);
}

void	ScalarConverter::convert(std::string src)
{
	int type;
	int negatif;
	double	dbl;
	float	flt;
	int		integers;
	char	c;
	int		overflow;

	type = 0;
	dbl = 0;
	overflow = 0;
	negatif = 1;

	if (handle_special_lit(src))
		return ;
	type = which_type(src, &negatif);
	if (type == 0)
		return ;
	switch (type)
	{
		case 1 :
			if (src[0] == '\'')
				c = src[1];
			else 
				c = src[0];
			std::cout << "char: " << c <<std::endl;
			std::cout << "int: " << static_cast<int>(c) <<std::endl;
			std::cout << "float: " << static_cast<float>(c) << ".0f" <<std::endl;
			std::cout << "double: " << static_cast<double>(c) << ".0" <<std::endl;
			break;
		case 2 :
			if (ft_atoi(src,&overflow) == -2147483648 && negatif == -1)
				integers = -2147483648;
			else if (ft_atoi(src,&overflow) == -2147483648 && negatif == 1)
				overflow = 1;
			else
				integers = ft_atoi(src, &overflow) * negatif;
			if (overflow == 1)
			{
				std::cout << "char: " << "Overflow" <<std::endl;
				std::cout << "int: " << " Overflow" <<std::endl;
				std::cout << "float: " << "can't be cast" <<std::endl;
				std::cout << "double: " << "can't be cast" <<std::endl;
			}
			else 
			{
				if (integers >= -128 && integers <= 127)
				{
					if (std::isprint(integers) != 0)
						std::cout << "char: " << static_cast<char>(integers) <<std::endl;
					else
						std::cout << "char: " << "Non displayable" <<std::endl;
				}
				else
					std::cout << "char: " << "Overflow" <<std::endl;
				std::cout << "int: " << integers <<std::endl;
				if (integers > 1000000 || integers < -1000000)
				{
					std::cout << "float: " << static_cast<float>(integers) << "f" <<std::endl;
					std::cout << "double: " << static_cast<double>(integers) << std::endl;
				}
				else
				{
					std::cout << "float: " << static_cast<float>(integers) << ".0f" <<std::endl;
					std::cout << "double: " << static_cast<double>(integers) << ".0" << std::endl;
				}
			}
			break;
		case 3 :
			flt = ft_atoi_float(src) * negatif;
			if (flt > 2147483647.0f || flt < -21474836478.0f)
			{
				std::cout << "char: " << "Overflow" <<std::endl;
				std::cout << "int: " << " Overflow" <<std::endl;
			}
			else if (flt >= -128.0f && flt <= 127.0f)
			{
				if (std::isprint(static_cast<int>(flt)) != 0)
					std::cout << "char: " << static_cast<char>(flt) <<std::endl;
				else
					std::cout << "char: " << "Non displayable" <<std::endl;
				std::cout << "int: " << static_cast<int>(flt) <<std::endl;
			}
			else
			{
				std::cout << "char: " << "Overflow" <<std::endl;
				std::cout << "int: " << static_cast<int>(flt) <<std::endl;
			}
			std::cout << "float: " << flt << "f" <<std::endl;
			std::cout << "double: " << static_cast<double>(flt) <<std::endl;
			break;
		case 4 :
			dbl = ft_atoi_double(src) * negatif;
			if (dbl > 2147483647.0 || dbl < -21474836478.0)
			{
				std::cout << "char: " << "Overflow" <<std::endl;
				std::cout << "int: " << " Overflow" <<std::endl;
			}
			else if (dbl >= -128 && dbl <= 127)
			{
				if (std::isprint(static_cast<int>(dbl)) != 0)
					std::cout << "char: " << static_cast<char>(dbl) <<std::endl;
				else
					std::cout << "char: " << "Non displayable" <<std::endl;
				std::cout << "int: " << static_cast<int>(dbl) <<std::endl;
			}
			else
			{
				std::cout << "char: " << "Overflow" <<std::endl;
				std::cout << "int: " << static_cast<int>(dbl) <<std::endl;
			}
			std::cout << "float: " << static_cast<float>(dbl) << "f" <<std::endl;
			std::cout << "double: " << dbl <<std::endl;
			break;
	}
}
