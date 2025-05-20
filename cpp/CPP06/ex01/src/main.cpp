/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:32:47 by seb               #+#    #+#             */
/*   Updated: 2024/07/20 13:58:07 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp" 
//#include "stdio.h"

int main()
{
    try 
    {
        Data *data = new Data;
        data->data_number = 45;
        data->data_str = "HEY";
        std::cout <<  data->data_str << " " << data->data_number << std::endl;
        uintptr_t s = Serializer::serialize(data);
        std::cout << s << std::endl;
        //printf("%lx\n", s);
        std::cout << data << std::endl;

        Data *newPtr = Serializer::deserialize(s);
        std::cout << newPtr << std::endl;
        std::cout <<  newPtr->data_str <<" " << newPtr->data_number << std::endl;
        delete data;
    }
    catch (std::bad_alloc const &e)
    {
        std::cerr << "bad alloc" << std::endl;
    }
}