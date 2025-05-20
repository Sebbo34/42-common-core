/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:17:13 by sbo               #+#    #+#             */
/*   Updated: 2024/07/20 13:24:01 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int main(int argc, char **argv) 
{
    if (argc != 2)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return (1);
    }
    ScalarConverter::convert(argv[1]);
    return (0);
}
