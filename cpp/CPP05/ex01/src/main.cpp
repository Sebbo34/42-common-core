/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:28:02 by sbo               #+#    #+#             */
/*   Updated: 2024/07/15 21:01:26 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
	try
	{
		Form formA("Form A", 1, 1);
		Form formB("Form B", 1, 5);
		Bureaucrat Victor("Victor", 1);
		Bureaucrat Bob("Bob", 9);
		std::cout << formA << std::endl;
		std::cout << formB << std::endl;

		Victor.signForm(formA);
		Bob.signForm(formB);
		std::cout << formA << std::endl;
		std::cout << formB << std::endl;
		formB.beSigned(Victor);
		std::cout << formB << std::endl;
		Form formC("Form C", 1, 1);
		formC.beSigned(Bob);
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
	}
}