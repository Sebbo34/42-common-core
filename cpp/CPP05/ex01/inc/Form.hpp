/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:31:45 by sbo               #+#    #+#             */
/*   Updated: 2024/07/19 14:12:23 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"
#include <iostream>

class Bureaucrat;

class Form
{
	private:
		const std::string	name;
		bool				sign;
		const int			gradeForSign;
		const int			gradeForEx;
	public:
		Form(std::string name, int gradeForSign, int gradeForEx);
		~Form();
		Form(const Form &src);
		Form &operator=(Form const &form);
		
		std::string	getName() const;
		int getGradeForSign(void) const;
		int getGradeForEx(void) const;
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
		void	beSigned(Bureaucrat const &bureaucrat);
};

std::ostream & operator<<(std::ostream & o, Form const & Form);

#endif