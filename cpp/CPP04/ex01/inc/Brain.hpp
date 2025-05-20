/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:46:52 by sbo               #+#    #+#             */
/*   Updated: 2024/07/15 09:38:54 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

class Brain
{
private:
	std::string	ideas[100];
public:
	Brain();
	~Brain();
	Brain(const Brain &src);
	Brain	&operator=(Brain const & brain);

	void	getIdeas(std::string ideas[100]) const;
	void	setIdea(std::string idea, int i);
	void	printIdeas();
};

#endif