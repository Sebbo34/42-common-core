/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:46:32 by sbo               #+#    #+#             */
/*   Updated: 2024/07/15 08:49:37 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain Constructor Called" << std::endl;
	return ;
}

Brain::~Brain(void)
{
	std::cout << "Brain Destructor Called" << std::endl;
	return ;
}

Brain::Brain (Brain const & src)
{
	std::cout << "Brain copy constructor called" << std::endl;
	*this = src;
	return ;
}

void	Brain::getIdeas(std::string ideas[100]) const
{
	int	i;

	i = 0;
	while (i < 100 )
	{
		ideas[i] = this->ideas[i];
		i++;
	}
}

Brain & Brain::operator=(Brain const & Brain)
{
	if (this != &Brain)
	{
		Brain.getIdeas(this->ideas);
	}
	return *this;
}

void	Brain::setIdea(std::string idea, int i)
{
	this->ideas[i] = idea;
	return ;
}

void	Brain::printIdeas()
{
	int	i;

	i = 0;
	while (i < 100)
	{
		if (!this->ideas[i].empty())
			std::cout << this->ideas[i] << std::endl;
		i++;
	}
}


