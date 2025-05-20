/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:50:56 by seb               #+#    #+#             */
/*   Updated: 2024/07/19 20:44:52 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer()
{
	std::cout << "Serializer constructor called" << std::endl;
}

Serializer::~Serializer()
{
	std::cout << "Serializer destructor called" << std::endl;
}
Serializer::Serializer(const Serializer &src)
{
	std::cout << "Serializer copy constructor called" << std::endl;
	*this = src;
	return ;
}

Serializer & Serializer::operator=(Serializer const &conv)
{
	if (this != &conv)
	{
	}
	return *this;
}
uintptr_t Serializer::serialize(Data* ptr)
{
	uintptr_t r = reinterpret_cast<uintptr_t>(ptr);
	return r;
}

Data* Serializer::deserialize(uintptr_t raw)
{
	Data *restoredPtr = reinterpret_cast<Data *>(raw);
	return (restoredPtr);
}
