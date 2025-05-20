/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:31:39 by sbo               #+#    #+#             */
/*   Updated: 2024/07/19 14:52:02 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(std::string name, const int gradeForSign, const int gradeForEx) : name(name), sign(0), gradeForSign(gradeForSign), gradeForEx(gradeForEx)
{
	if (gradeForSign > 150 || gradeForEx > 150)
		throw AForm::GradeTooLowException();
	else if (gradeForSign < 1 || gradeForEx < 1)
		throw AForm::GradeTooHighException();
	std::cout << "AForm constructor called" << std::endl;
	return ;
}

AForm::~AForm()
{
	std::cout << "AForm destructor called" << std::endl;
	return ;
}


AForm::AForm (const AForm & src) : name(src.getName()), gradeForSign(src.getGradeForSign()), gradeForEx(src.getGradeForEx())
{
	std::cout << "Copy constructor Called" << std::endl;
	*this = src;
	return ;
}

std::string AForm::getName(void) const
{
	return (this->name);
}

int AForm::getGradeForSign(void) const
{
	return (this->gradeForSign);
}

int AForm::getGradeForEx(void) const
{
	return (this->gradeForEx);
}

bool AForm::isSigned(void) const
{
	return (this->sign);
}

AForm & AForm::operator=(AForm const & AForm)
{
	if (this != &AForm)
	{
		this->sign = AForm.isSigned();
	}
	return *this;
}

std::ostream &operator<<(std::ostream &o, AForm const & AForm)
{
	o << "Form " << AForm.getName() << " need a " << AForm.getGradeForEx() << " for exec and " << AForm.getGradeForSign() << " for sign";
	if (AForm.isSigned())
		o << " and is already signed";
	else
		o << " and need to be signed";
	return o;
}

typedef AForm::GradeTooLowException Low;
typedef AForm::GradeTooHighException High;
typedef AForm::IsNotSigned INS;



const char* High::what() const throw()
{
	return "Grade too high";
}

const char* Low::what() const throw()
{
	return "Grade too low";
}
const char* INS::what() const throw()
{
	return "Form is not signed";
}


void	AForm::beSigned(Bureaucrat bureaucrat)
{
	if (bureaucrat.getGrade() <= this->getGradeForSign())
		this->sign = true;
	else
		throw AForm::GradeTooLowException();
}
