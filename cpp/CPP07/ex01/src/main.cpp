/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 23:10:06 by seb               #+#    #+#             */
/*   Updated: 2024/10/18 14:07:15 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

void add_5(int i)
{
    std::cout << i + 5 << std::endl;
}
void print(std::string str)
{
    std::cout << str << std::endl;
}

int main()
{
    int Array[5] = {1, 2, 3, 4, 5};
    std::string SArray[5] = {"a", "b", "c", "d", "e"};
    try
    {
        iter(Array, 5, add_5);
        iter(Array, 5, print2);
        iter(SArray, 5, print2);
        iter(SArray, 5, print);
    }
    catch (std::bad_alloc const &e)
    {
        std::cout << "Out of range" << std::endl;
    }
}