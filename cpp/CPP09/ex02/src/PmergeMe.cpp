/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 03:34:35 by sbo               #+#    #+#             */
/*   Updated: 2024/11/11 17:05:26 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int getMiddleVector(std::vector<int >::iterator start, std::vector<int >::iterator end)
{
	std::vector<int> tmp(start, end);
	if (tmp.size() > 1)
		return (tmp.size() / 2);
	return (1);
}

std::vector<int >::iterator binarySearchVector(std::vector<int> &result, std::vector<int >::iterator start, std::vector<int >::iterator end, int elem)
{
	std::vector<int >::iterator it = start;
	int middle;
	if (start == result.end() || end == result.end())
	{
		return (start);
	}
 	if (start >= end)
	{
 		if (elem <= *start)
			return (start);
		else
			return (++start);
	}
	middle = getMiddleVector(start, end);
	it = it + middle;
	if (elem < *it)
	{
		it--;
		return binarySearchVector(result, start, it, elem);
	}
	else
	{
		it++;
		return binarySearchVector(result, it, end, elem);
	}
}

void binarySearchInsertVector(std::pair<int, int> elem, std::vector<int> &result)
{
	std::vector<int >::iterator save;

	if (elem.second == -1)
	{
		save = result.end();
		save--;
		if (elem.first > *save)
			result.push_back(elem.first);
		else if((elem.first < *result.begin()))
			result.insert(result.begin(),elem.first);
		else
			result.insert(binarySearchVector(result, result.begin(), save, elem.first), elem.first);
		return;	
	}
	for ( std::vector<int >::iterator it = result.begin() ;it != result.end(); it++ )
	{
		if (*it == elem.second)
		{
			save = it;	
			break;
		}
    }
	result.insert(binarySearchVector(result, result.begin(), save, elem.first), elem.first);
}

std::vector<std::pair<int, int> > organizePairsVector(std::vector<std::pair<int, int> > pairs, std::vector<int> result)
{
	std::vector<std::pair<int, int> > orgPair;
	std::vector<std::pair<int, int> >::iterator tmp;
	for (std::vector<int >::iterator it = result.begin(); it != result.end(); it++ ) 
	{
		for (std::vector<std::pair<int, int> >::iterator it2 = pairs.begin(); it2 != pairs.end(); it2++ ) 
		{
			if ((*it2).second == (*it))
			{
				orgPair.push_back(*it2);
				tmp = it2;
				break;
			}
    	}
		pairs.erase(tmp);
	}
	return (orgPair);
}

std::vector<int> sortVector(std::vector<int> vector)
{
	int tmp = -1;
	std::vector<std::pair<int, int> > pairs;
	std::vector<int> result;
	std::pair<int, int> odd = std::make_pair(tmp, -1);;
	if (vector.size() == 1)
	{
		return (vector);
	}
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++)
	{
		tmp = *it;
		it++;
		if (it == vector.end())
		{
			odd.first = tmp; 
			break;
		}
		if (tmp < *it)
		{
			pairs.push_back(std::make_pair(tmp, *it));
			result.push_back(*it);
		}
		else
		{
			pairs.push_back(std::make_pair(*it, tmp));
			result.push_back(tmp);
		}
	}
	result = sortVector(result);
	pairs = organizePairsVector(pairs, result);
	result.insert(result.begin(),pairs[0].first);
	std::pair<int, int> first;
	std::vector<std::pair<int, int> >::iterator it2 = pairs.begin();
	it2++;
	for (std::vector<std::pair<int, int> >::iterator it = it2; it != pairs.end(); it++)
	{
		first = (*it);
		it++;
		if (it != pairs.end())
		{
			binarySearchInsertVector((*it), result);
		}
		binarySearchInsertVector(first, result);
		if (it == pairs.end())
			break;
	}
	if (odd.first != -1)
		binarySearchInsertVector(odd, result);
	return result;
}

// LIST 

int getMiddleList(std::list<int>::iterator start, std::list<int>::iterator end) 
{
    int slow = 0;
    std::list<int>::iterator fast = start;
	std::list<int>::iterator tmp = fast;
	tmp ++;
    while (fast != end && tmp != end)
	{
        ++slow;
        std::advance(fast, 2);
		tmp = fast;
		if (tmp != end)
			tmp++;
    }
    return slow;
}

std::list<int >::iterator binarySearchList(std::list<int> &result, std::list<int >::iterator start, std::list<int >::iterator end, int elem)
{
	std::list<int >::iterator it = start;
	int middle;
	if (start == result.end() || end == result.end())
		return (start);
	if (*start >= *end)
	{
		if (elem <= *start)
			return (start);
		else
			return (++start);
	}
	middle = getMiddleList(start, end);
    std::advance(it, middle);
	if (elem <= *it)
	{
		it--;
		return binarySearchList(result, start, it, elem);
	}
	else
	{
		it++;
		return binarySearchList(result, it, end, elem);
	}
}

void binarySearchInsertList(std::pair<int, int> elem, std::list<int> &result)
{
	std::list<int >::iterator save;
	if (elem.second == -1)
	{
		save = result.end();
		save--;
		if (elem.first > *save)
			result.push_back(elem.first);
		else if((elem.first < *result.begin()))
			result.insert(result.begin(),elem.first);
		else
			result.insert(binarySearchList(result, result.begin(),save, elem.first), elem.first);
		return;	
	}
	for ( std::list<int >::iterator it = result.begin() ;it != result.end(); it++ )
	{
		if (*it == elem.second)
		{
			save = it;	
			break;
		}
    }
	result.insert(binarySearchList(result, result.begin(), save, elem.first), elem.first);
}

std::list<std::pair<int, int> > organizePairsList(std::list<std::pair<int, int> > pairs, std::list<int> result)
{
	std::list<std::pair<int, int> > orgPair;
	std::list<std::pair<int, int> >::iterator save;

	for (std::list<int >::iterator it = result.begin(); it != result.end(); it++ ) 
	{
		for (std::list<std::pair<int, int> >::iterator it2 = pairs.begin(); it2 != pairs.end(); it2++ ) 
		{
			if ((*it2).second == (*it))
			{
				orgPair.push_back(*it2);
				save = it2;
				break;
			}
    	}
		pairs.erase(save);
	}
	return (orgPair);
}

bool ft_all_of_digit(std::string s)
{
	for (std::string::iterator it = s.begin(); it != s.end(); it++ )
	{
		if (!isdigit(*it))
			return false;
	}
	return true;
}

std::list<int> sortList(std::list<int> list)
{
	int tmp = -1;
	std::list<std::pair<int, int> > pairs;
	std::list<int> result;
	std::pair<int, int> odd = std::make_pair(-1, -1);;
	if (list.size() == 1)
		return (list);
	for (std::list<int>::iterator it = list.begin(); it != list.end(); it++)
	{
		tmp = *it;
		it++;
		if (it == list.end())
		{
			odd.first = tmp ;
			break;
		}
		if (tmp < *it)
		{
			pairs.push_back(std::make_pair(tmp, *it));
			result.push_back(*it);
		}
		else
		{
			pairs.push_back(std::make_pair(*it, tmp));
			result.push_back(tmp);
		}
	}
	result = sortList(result);
	pairs = organizePairsList(pairs, result);
	result.push_front(pairs.front().first);
	std::pair<int, int> first;
	std::list<std::pair<int, int> >::iterator it2 = pairs.begin();
	it2++;
	for (std::list<std::pair<int, int> >::iterator it = it2; it != pairs.end(); it++)
	{
		first = (*it);
		it++;
		if (it != pairs.end())
		{
			binarySearchInsertList((*it), result);
		}
		binarySearchInsertList(first, result);
		if (it == pairs.end())
			break;
	}
	if (odd.first != -1)
		binarySearchInsertList(odd, result);
	return result;
}

bool isNumber(std::string s)
{
	if (s.size() > 10 && ft_all_of_digit(s))
	{
		std::cerr << "Error : Overflow" << std::endl;
		return false;
	}
	if ( !s.empty() && ft_all_of_digit(s))
		return true;
	else if (!s.empty() && s[0] == '-' && ft_all_of_digit(s.substr(1)))
	{
		std::cerr << "Error : Non positive value" << std::endl;
		return false;
	}
	else 
	{
		std::cerr << "Error : Invalid input" << std::endl;
		return false;
	}
}

bool creatList(std::list<int> &l, char **args, int len)
{
	int i = 1;
	float	value;
	while (i < len)
	{
		if (!isNumber(args[i]))	
		{
			return false;
		}
		value = atof(args[i]);
		if (value < 0 || value > 2147483647.0f)
		{
			std::cerr << "Error : Overflow" << std::endl;
			return false;
		}
		l.push_back(value);
		i++;
	}
	return true;
}

bool creatVector(std::vector<int> &vect, char **args, int len)
{
	int i = 1;
	float	value;
	while (i < len)
	{
		if (!isNumber(args[i]))	
		{
			return false;
		}
		value = atof(args[i]);
		if (value < 0 || value > 2147483647.0f)
		{
			std::cerr << "Error : Overflow" << std::endl;
			return false;
		}
		vect.push_back(value);
		i++;
	}
	return true;
}

