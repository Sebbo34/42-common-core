/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:40:50 by seb               #+#    #+#             */
/*   Updated: 2024/10/18 13:19:57 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

#include <iostream>

template <typename T>
T min(const T &x, const T &y)
{
    if (x < y)
        return (x);
    return (y);
}

template <typename T>
T max(const T &x, const T &y)
{
    if (x > y)
        return (x);
    return (y);
}

template <typename T>
void swap(T &x, T &y)
{
    T tmp;
    tmp = x;
    x = y;
    y = tmp;
}

#endif