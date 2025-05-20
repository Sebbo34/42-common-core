/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShruberryCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:33:08 by sbo               #+#    #+#             */
/*   Updated: 2024/07/19 14:56:21 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBERRYCREATIONFORM_HPP
#define SHRUBERRYCREATIONFORM_HPP

#include "AForm.hpp"

class ShruberryCreationForm : public AForm
{
	private:
		std::string target;
	public:
		ShruberryCreationForm(std::string target);
		~ShruberryCreationForm();

		std::string getTarget(void) const;
		ShruberryCreationForm & operator=(ShruberryCreationForm const & form);
		ShruberryCreationForm (const ShruberryCreationForm & src);
		void	execute(Bureaucrat const & executor);
};

#endif
