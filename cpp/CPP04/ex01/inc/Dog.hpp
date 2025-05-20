/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:00:04 by sbo               #+#    #+#             */
/*   Updated: 2024/07/16 18:51:06 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain *Brain;
	public:
		Dog();
		~Dog();
		Dog(const Dog &src);
		Dog	&operator=(Dog const & Dog);
	
		void	makeSound() const;
		void	setIdea(std::string idea, int i);
		void	printIdeas();
};

#endif