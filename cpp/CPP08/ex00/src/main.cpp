/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:03:17 by sbo               #+#    #+#             */
/*   Updated: 2024/11/08 11:58:56 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "easyfind.hpp"
#include<deque>

int main()
{
    std::deque<int> d(5,7);
    int i = 0;
    for(std::deque<int>::iterator it = d.begin(); it!=d.end(); ++it)
    {
		i++;
        if (i == 4)
            *it = 7878;
        else
            *it = i;
        std::cout << *it << std::endl;
    }
    try
    {
        std::deque<int>::iterator it = easyfind(d,3);
        std::cout << (*it) << std::endl;
        it++;
        std::cout << (*it) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    try
    {
        std::deque<int>::iterator it = easyfind(d,-5);
        std::cout << (*it) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Number not found" << std::endl;
    }

    
    return 0;
}