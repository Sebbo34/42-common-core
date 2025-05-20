/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:50:59 by seb               #+#    #+#             */
/*   Updated: 2024/07/20 13:47:39 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>
#include <iostream>

struct Data
{
    int         data_number;
    std::string data_str;
};

class Serializer
{
    private :
        Serializer();
        Serializer(const Serializer &src);
		Serializer &operator=(Serializer const &conv);
    public :
        ~Serializer();
        static  uintptr_t serialize(Data* ptr);
        static  Data* deserialize(uintptr_t raw);
};

#endif