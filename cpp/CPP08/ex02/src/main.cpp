/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:55:46 by sbo               #+#    #+#             */
/*   Updated: 2024/11/08 11:20:14 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <stack>

int main()
{
	MutantStack<int> mstack;
	mstack.push(14);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << "start" <<*it << std::endl;
		++it;
	}
	--it;
	ite = mstack.begin();
	while (it != ite)
	{
		std::cout << "reverse " << *it << std::endl;
		--it;
		if (ite == it)
		{
			std::cout << "reverse " << *it << std::endl;
		}
	}
	MutantStack<int>::reverse_iterator it2 = mstack.rbegin();
	while (it2 != mstack.rend())
	{
		std::cout << "reverse " << *it2 << std::endl;
		it2++;
	}
	return 0;
}