/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShruberryCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:33:08 by sbo               #+#    #+#             */
/*   Updated: 2024/07/17 21:32:18 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBERRYCREATIONFORM_HPP
#define SHRUBERRYCREATIONFORM_HPP

#include "Form.hpp"

class ShruberryCreationForm : public Form
{
	private:
		std::string target;
	public:
		ShruberryCreationForm(std::string target);
		~ShruberryCreationForm();
		ShruberryCreationForm & operator=(ShruberryCreationForm const & form);
		ShruberryCreationForm (const ShruberryCreationForm & src);

		std::string getTarget(void) const;
		void	execute(Bureaucrat const & executor);

};

#endif
