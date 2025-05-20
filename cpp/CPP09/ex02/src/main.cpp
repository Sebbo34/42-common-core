/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 03:34:32 by sbo               #+#    #+#             */
/*   Updated: 2024/11/11 16:49:58 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    std::list<int> myList;
	std::vector<int> vect;
	if (argc < 2)
	{
		std::cerr << "Error : Invalid number of args" << std::endl;
		return (1);
	}	
	if (!creatList(myList, argv, argc))
		return 1;
	std::cout << "Before :   ";
	for (std::list<int >::iterator it =myList.begin(); it !=myList.end(); it++ ) {
        std::cout<< (*it) << " ";
    }
	std::cout << std::endl;
	clock_t debut = clock();
	myList = sortList(myList);
	clock_t fin = clock();
    double duree = double(fin - debut) / CLOCKS_PER_SEC;
	if (!creatVector(vect, argv, argc))
		return 1;
	debut = clock();
	vect = sortVector(vect);
	fin = clock();
    double duree2 = double(fin - debut) / CLOCKS_PER_SEC;
	std::cout << "After :    ";
	for (std::list<int >::iterator it =myList.begin(); it !=myList.end(); it++ ) {
		std::cout<< (*it) << " ";
    } 
	std::cout << std::endl;
	std::cout << "Time to process a range of " << myList.size() << " elements with std::list : " << duree << " s" <<std::endl;
	std::cout << "Time to process a range of " << vect.size() << " elements with std::vector : " << duree2 << " s" <<std::endl;
	return 0;
}
