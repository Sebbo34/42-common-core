/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 09:31:15 by sbo               #+#    #+#             */
/*   Updated: 2024/07/19 14:13:04 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include "Form.hpp"

#include <iostream>
#include <exception>

class Form;

class Bureaucrat
{
private:
	const	std::string	name;
	int					grade;
public:
	Bureaucrat(std::string inst_name, int inst_grade);
	~Bureaucrat();
	Bureaucrat(const Bureaucrat &src);
	Bureaucrat &operator=(Bureaucrat const &bureaucrat);

	std::string	getName() const;
	int			getGrade() const;
	void		promote();
	void		demote();
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
	void		signForm(Form &form);
	
};

std::ostream & operator<<(std::ostream & o, Bureaucrat const & bureaucrat);

#endif