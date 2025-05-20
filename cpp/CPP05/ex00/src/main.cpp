/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:28:02 by sbo               #+#    #+#             */
/*   Updated: 2024/07/19 14:58:44 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(void)
{
	try
	{
		Bureaucrat f("Victor", 151);
		std::cout << f << std::endl;
		f.demote();
		std::cout << f << std::endl;
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		Bureaucrat f("Victor", 1);
		std::cout << f << std::endl;
		f.demote();
		std::cout << f << std::endl;
		f.promote();
		std::cout << f << std::endl;
		f.promote();
		std::cout << f << std::endl;
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		Bureaucrat f("Victor", -15);
		std::cout << f << std::endl;
		f.promote();
		std::cout << f << std::endl;
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
	}
}