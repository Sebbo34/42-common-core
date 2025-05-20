/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:57:25 by seb               #+#    #+#             */
/*   Updated: 2024/11/08 11:50:51 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <ctime>
#include <cstdlib>

int main(void) 
{
	Span sp(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	try 
	{
		sp.addNumber(45);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
	Span sp3(10000);

    std::srand(std::time(0));
    std::vector<int> random_numbers(10000);
    for (int i = 0; i < 10000; ++i) {
        random_numbers[i] = std::rand() % 100000 + 1;
    }
	try 
	{
		sp3.range(random_numbers.begin(),random_numbers.end());
		std::cout << sp3.shortestSpan() << std::endl;
		std::cout << sp3.longestSpan() << std::endl;
		sp3.addNumber(45);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	Span sp2(1);	
	try 
	{
		std::cout << sp2.shortestSpan() << std::endl;
		std::cout << sp2.longestSpan() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0; 
}
