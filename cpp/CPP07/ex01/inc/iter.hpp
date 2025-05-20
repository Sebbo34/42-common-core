/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:57:09 by seb               #+#    #+#             */
/*   Updated: 2024/07/20 17:30:54 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template <typename T>
void print2(T &x)
{
    std::cout << x << std::endl;  
}

template <typename T>
void    iter(T *array, int lenght, void(*f)(T const &))
{
    int i;
    i = 0;
    while(i < lenght)
    {
        f(array[i]);
        i++;
    }
}

template <typename T>
void    iter(T *array, int lenght, void(*f)(T))
{
    int i;
    i = 0;
    while(i < lenght)
    {
        f(array[i]);
        i++;
    }
}

#endif