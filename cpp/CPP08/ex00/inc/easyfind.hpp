/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:03:14 by sbo               #+#    #+#             */
/*   Updated: 2024/11/08 11:58:11 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include<deque>

template<typename T>
typename T::iterator	easyfind(T &container, int number)
{
	typename T::iterator it = container.begin();

	while (it != container.end())
	{
		if (*it == number)
			return (it);
		it++;
	}
    throw std::exception();
	return (it);
}

#endif