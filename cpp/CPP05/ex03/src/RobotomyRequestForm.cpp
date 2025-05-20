/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:33:00 by sbo               #+#    #+#             */
/*   Updated: 2024/07/19 14:50:37 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include<cstdlib>

RobotomyRequestForm::RobotomyRequestForm(std::string target) : Form("Robotomy Request", 72 , 45), target(target)
{
	std::cout << "RobotomyRequestForm constructor called " << std::endl;
	return ;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "RobotomyRequestForm destructor called " << std::endl;
	return ;
}
RobotomyRequestForm::RobotomyRequestForm (const RobotomyRequestForm & src) : Form("Robotomy Request", 72 , 45)
{
	std::cout << "Copy constructor Called" << std::endl;
	*this = src;
	return ;
}

RobotomyRequestForm & RobotomyRequestForm::operator=(RobotomyRequestForm const & form)
{
	if (this != &form)
	{
		this->target = form.getTarget();
	}
	return *this;
}

std::string RobotomyRequestForm::getTarget(void) const
{
	return (this->target);
}

void	RobotomyRequestForm::execute(Bureaucrat const & executor) //flag
{
	if (this->isSigned() && executor.getGrade() <= this->getGradeForEx())
	{
		std::cout << "** Make some drilling noises **" << std::endl;
		srand((unsigned) time(NULL));
		int tmp = rand() % 2;
		if (tmp)
			std::cout << this->getTarget() << " has been robotomized" << std::endl;
	}
	else if (!this->isSigned())
		throw Form::IsNotSigned();
	else
		throw Form::GradeTooLowException();
}