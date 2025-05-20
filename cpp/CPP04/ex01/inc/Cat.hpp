/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:59:56 by sbo               #+#    #+#             */
/*   Updated: 2024/07/16 18:25:53 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain *Brain;
	public:
		Cat();
		~Cat();
		Cat(const Cat &src);
		Cat	&operator=(Cat const & Cat);
	
		void	makeSound() const;
		std::string	getType(void) const;
		void	setIdea(std::string idea, int i);
		void	printIdeas();
};

#endif
