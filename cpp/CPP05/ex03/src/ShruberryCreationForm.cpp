/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShruberryCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:32:39 by sbo               #+#    #+#             */
/*   Updated: 2024/07/19 14:50:45 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShruberryCreationForm.hpp"
#include <fstream>

ShruberryCreationForm::ShruberryCreationForm(std::string target) : Form("Shruberry Creation", 145 , 137), target(target)
{
	std::cout << "ShruberryCreationForm constructor called " << std::endl;
	return ;
}

ShruberryCreationForm::~ShruberryCreationForm()
{
	std::cout << "ShruberryCreationForm destructor called " << std::endl;
	return ;
}
ShruberryCreationForm::ShruberryCreationForm (const ShruberryCreationForm & src) : Form("Shruberry Creation", 145 , 137)
{
	std::cout << "Copy constructor Called" << std::endl;
	*this = src;
	return ;
}

ShruberryCreationForm & ShruberryCreationForm::operator=(ShruberryCreationForm const & form)
{
	if (this != &form)
	{
		this->target = form.getTarget();
	}
	return *this;
}

std::string ShruberryCreationForm::getTarget(void) const
{
	return (this->target);
}

void	ShruberryCreationForm::execute(Bureaucrat const & executor) //flag
{
	std::string filename;
	if (this->isSigned() && executor.getGrade() <= this->getGradeForEx())
	{
		filename = target + "_shruberry";
		std::ofstream fichier(filename.c_str());
		if (!fichier)
		{
			std::cout << "Error in " << filename << std::endl;
			return ;
		}
		std::cout << "          ccee88oo" << std::endl;
		std::cout << "   C8O8O8Q8PoOb o8oo" << std::endl;
		std::cout << " dOB69QO8PdUOpugoO9bD" << std::endl;
		std::cout << "CgggbU8OU qOp qOdoUOdcb" << std::endl;
		std::cout << "    6OuU  /p u gcoUodpP" << std::endl;
		std::cout << "      \\\\\\//  /douUP" << std::endl;
		std::cout << "        \\\\\\////" << std::endl;
		std::cout << "         |||/\\" << std::endl;
		std::cout << "         |||\\/" << std::endl;
		std::cout << "         |||||" << std::endl;
		std::cout << "   .....//||||\\...." << std::endl;
	}
	else if (!this->isSigned())
		throw Form::IsNotSigned();
	else
		throw Form::GradeTooLowException();
}