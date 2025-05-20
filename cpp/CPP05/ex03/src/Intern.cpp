/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:50:57 by sbo               #+#    #+#             */
/*   Updated: 2024/07/17 21:34:29 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern()
{
	std::cout << "Intern constructor Called" << std::endl;
}

Intern::~Intern()
{
	std::cout << "Intern destructor Called" << std::endl;
}

Intern::Intern (const Intern & src)

{
	std::cout << "Intern copy constructor Called" << std::endl;
	*this = src;
	return ;
}

Intern & Intern::operator=(Intern const & intern)
{
	if (this != &intern)
	{
	}
	return *this;
}

Form *newRR(std::string target)
{
	return new RobotomyRequestForm(target);
}

Form *newPP(std::string target)
{
	return new PresidentialPardonForm(target);
}

Form *newSC(std::string target)
{
	return new ShruberryCreationForm(target);
}

Form	*Intern::makeForm(std::string form, std::string target)
{
	std::string _form[3] = {"robotomy request", "presidential pardon", "shruberry creation"};
	Form*	(*ptr[3])(std::string) = { &newRR, &newPP , &newSC};

	for (int i = 0; i < 3 ; i++)
	{
		if (form.compare(_form[i]) == 0)
		{
			std::cout << "Interns creates " << form << std::endl;
			return ptr[i](target);
		}
	}
	std::cout << "Interns can't creates " << form << std::endl;
	return (NULL);
}