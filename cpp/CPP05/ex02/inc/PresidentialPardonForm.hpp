/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:32:49 by sbo               #+#    #+#             */
/*   Updated: 2024/05/28 13:26:30 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
private:
		std::string target;
	public:
		PresidentialPardonForm(std::string target);
		~PresidentialPardonForm();

		std::string getTarget(void) const;
		PresidentialPardonForm & operator=(PresidentialPardonForm const & form);
		PresidentialPardonForm (const PresidentialPardonForm & src);
		void	execute(Bureaucrat const & executor);

};

#endif
