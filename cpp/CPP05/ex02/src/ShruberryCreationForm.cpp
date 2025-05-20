/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShruberryCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:32:39 by sbo               #+#    #+#             */
/*   Updated: 2024/07/19 14:50:02 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShruberryCreationForm.hpp"
#include <fstream>

ShruberryCreationForm::ShruberryCreationForm(std::string target) : AForm("Shruberry Creation", 145 , 137), target(target)
{
	std::cout << "ShruberryCreationForm constructor called " << std::endl;
	return ;
}

ShruberryCreationForm::~ShruberryCreationForm()
{
	std::cout << "ShruberryCreationForm destructor called " << std::endl;
	return ;
}

ShruberryCreationForm::ShruberryCreationForm (const ShruberryCreationForm & src) : AForm("Shruberry Creation", 145 , 137)
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

void	ShruberryCreationForm::execute(Bureaucrat const & executor)
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
		fichier << "          ccee88oo" << std::endl;
		fichier << "   C8O8O8Q8PoOb o8oo" << std::endl;
		fichier << " dOB69QO8PdUOpugoO9bD" << std::endl;
		fichier << "CgggbU8OU qOp qOdoUOdcb" << std::endl;
		fichier << "    6OuU  /p u gcoUodpP" << std::endl;
		fichier << "      \\\\\\//  /douUP" << std::endl;
		fichier << "        \\\\\\////" << std::endl;
		fichier << "         |||/\\" << std::endl;
		fichier << "         |||\\/" << std::endl;
		fichier << "         |||||" << std::endl;
		fichier << "   .....//||||\\...." << std::endl;
	}
	else if (!this->isSigned())
		throw AForm::IsNotSigned();
	else
		throw AForm::GradeTooLowException();
}