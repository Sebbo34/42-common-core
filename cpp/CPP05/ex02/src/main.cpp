/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:28:02 by sbo               #+#    #+#             */
/*   Updated: 2024/07/19 15:01:52 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShruberryCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

int main(void)
{
	try
	{
		Bureaucrat James("James", 150);
		Bureaucrat boss("James's boss", 1);

		ShruberryCreationForm SCF("James");
		James.executeForm(SCF);
		SCF.beSigned(boss);
		James.executeForm(SCF);
		RobotomyRequestForm RRF("James");
		RRF.beSigned(boss);
		James.executeForm(RRF);
		PresidentialPardonForm PPF("James");
		PPF.beSigned(boss);
		James.executeForm(PPF);
		
		boss.executeForm(PPF);
		boss.executeForm(SCF);
		boss.executeForm(RRF);

		SCF.execute(James);
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		Bureaucrat boss("James's boss", 1);

		ShruberryCreationForm SCF("James's boss");
		boss.executeForm(SCF);
		SCF.execute(boss);
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
	}
}