/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:28:02 by sbo               #+#    #+#             */
/*   Updated: 2024/07/18 12:37:04 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "Intern.hpp"
#include "ShruberryCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

int main(void)
{
	try
	{
		Intern someRandomIntern;
		Form *rrf;
		Bureaucrat james("James", 1);
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		james.signForm(*rrf);
		james.executeForm(*rrf);
		delete rrf;
	}
	catch(std::bad_alloc const& e)
	{
		std::cerr << "Bad alloc " << std::endl;
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
	}
}