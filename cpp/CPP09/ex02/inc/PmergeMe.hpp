/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 03:34:37 by sbo               #+#    #+#             */
/*   Updated: 2024/11/11 16:53:35 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib> 
#include <algorithm> 


// Fonctions pour les vecteurs
int									getMiddleVector(std::vector<int>::iterator start, std::vector<int>::iterator end);
std::vector<int>::iterator			binarySearchVector(std::vector<int> &result, std::vector<int>::iterator start, std::vector<int>::iterator end, int elem);
void								binarySearchInsertVector(std::pair<int, int> elem, std::vector<int> &result);
std::vector<std::pair<int, int> > 	organizePairsVector(std::vector<std::pair<int, int> > pairs, std::vector<int> result);
std::vector<int>					sortVector(std::vector<int> vector);

// Fonctions pour les listes
int									getMiddleList(std::list<int>::iterator start, std::list<int>::iterator end);
std::list<int>::iterator			binarySearchList(std::list<int> &result, std::list<int>::iterator start, std::list<int>::iterator end, int elem);
void								binarySearchInsertList(std::pair<int, int> elem, std::list<int> &result);
std::list<std::pair<int, int> >		organizePairsList(std::list<std::pair<int, int> > pairs, std::list<int> result);
std::list<int>						sortList(std::list<int> list);

// Fonctions utilitaires
bool 								ft_all_of_digit(std::string s);
bool 								isNumber(std::string s);
bool 								creatList(std::list<int> &l, char **args, int len);
bool 								creatVector(std::vector<int> &vect, char **args, int len);

#endif