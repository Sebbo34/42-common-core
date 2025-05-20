/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:32:55 by sbo               #+#    #+#             */
/*   Updated: 2024/07/19 14:49:39 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("Presidential PardonForm", 25 , 5), target(target)
{
	std::cout << "PresidentialPardonForm constructor called " << std::endl;
	return ;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	std::cout << "PresidentialPardonForm destructor called " << std::endl;
	return ;
}
PresidentialPardonForm::PresidentialPardonForm (const PresidentialPardonForm & src) : AForm("Presidential PardonForm", 25 , 5)
{
	std::cout << "Copy constructor Called" << std::endl;
	*this = src;
	return ;
}

PresidentialPardonForm & PresidentialPardonForm::operator=(PresidentialPardonForm const & form)
{
	if (this != &form)
	{
		this->target = form.getTarget();
	}
	return *this;
}

std::string PresidentialPardonForm::getTarget(void) const
{
	return (this->target);
}

void	PresidentialPardonForm::execute(Bureaucrat const & executor)
{
	if (this->isSigned() && executor.getGrade() <= this->getGradeForEx())
		std::cout << this->getTarget() << " has been pardoned by Zaphod Beeblebrox" << std::endl;
	else if (!this->isSigned())
		throw AForm::IsNotSigned();
	else
		throw AForm::GradeTooLowException();
}