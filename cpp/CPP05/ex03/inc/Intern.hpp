/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:44:22 by sbo               #+#    #+#             */
/*   Updated: 2024/07/15 22:39:07 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include "Form.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShruberryCreationForm.hpp"

class Intern
{
	public:
		Intern(/* args */);
		~Intern();
		Intern(const Intern &src);
		Intern &operator=(Intern const &intern);
		Form	*makeForm(std::string form, std::string target);
};

#endif