/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:31:45 by sbo               #+#    #+#             */
/*   Updated: 2024/07/19 15:03:56 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"
#include <iostream>

class Bureaucrat;

class AForm
{
	private:
		const std::string	name;
		bool				sign;
		const int			gradeForSign;
		const int			gradeForEx;
	public:
		AForm(std::string name, int gradeForSign, int gradeForEx);
		virtual ~AForm();
		AForm(const AForm &src);
		AForm &operator=(AForm const &Aform);
		std::string	getName() const;
		int		getGradeForSign(void) const;
		int		getGradeForEx(void) const;
		bool	isSigned(void) const;
		class GradeTooLowException : public std::exception
		{
			public :
				virtual const char* what() const throw();
		};
		class GradeTooHighException : public std::exception
		{
			public :
				virtual const char* what() const throw();
		};
		class IsNotSigned: public std::exception
		{
			public :
				virtual const char* what() const throw();
		};
		void	beSigned(Bureaucrat bureaucrat);
		virtual void	execute(Bureaucrat const & executor) = 0;
};

std::ostream & operator<<(std::ostream & o, AForm const & Form);

#endif