/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:05:09 by sbo               #+#    #+#             */
/*   Updated: 2024/07/15 09:20:06 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"


int main(void)
{
	Animal animal;
	WrongCat		Wcat;
	Dog		dog;
	WrongAnimal *wrong = new WrongCat(); 
	
	std::cout << animal.getType() << std::endl; 
	animal.makeSound();

	std::cout << Wcat.getType() << std::endl; 
	Wcat.makeSound();

	std::cout << wrong->getType() << std::endl; 
	wrong->makeSound();
	delete wrong;
	std::cout << dog.getType() << std::endl; 
	dog.makeSound();

	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();
	delete i;
	delete j;
	delete meta;
}