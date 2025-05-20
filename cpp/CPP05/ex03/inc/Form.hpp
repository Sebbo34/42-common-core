/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:31:45 by sbo               #+#    #+#             */
/*   Updated: 2024/05/29 09:24:58 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Form_HPP
#define Form_HPP

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
		virtual ~Form() = 0;
		Form(const Form &src);
		Form &operator=(Form const &Form);
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
		};		void	beSigned(Bureaucrat bureaucrat);
		virtual void	execute(Bureaucrat const & executor);
};

std::ostream & operator<<(std::ostream & o, Form const & Form);

#endif