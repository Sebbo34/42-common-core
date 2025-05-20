/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:55:43 by sbo               #+#    #+#             */
/*   Updated: 2024/11/08 11:16:53 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>
#include <iostream>



template<typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T,Container>
{
	public :
		MutantStack() : MutantStack<T,Container>::stack() {};
		MutantStack(const MutantStack<T,Container> &cpy) : MutantStack<T,Container>::stack(cpy) {};

		MutantStack<T, Container>& operator=(const MutantStack<T, Container>& src)
		{
			if (this != &src)
				this->MutantStack<T, Container>::stack::operator = (src);
			return *this;
		}
		virtual ~MutantStack() {};
		typedef typename Container::iterator iterator;
		typedef typename Container::reverse_iterator reverse_iterator;
		typedef typename Container::const_iterator const_iterator;
		typedef typename Container::const_reverse_iterator const_reverse_iterator;


 		iterator begin() { return this->c.begin(); }
		iterator end() { return this->c.end(); }
		const_iterator begin() const { return this->c.begin(); }
		const_iterator end() const { return this->c.end(); }

		reverse_iterator rbegin() { return this->c.rbegin(); }
		reverse_iterator rend() { return this->c.rend(); }
		const_reverse_iterator rbegin() const { return this->c.rbegin(); }
		const_reverse_iterator rend() const { return this->c.rend(); }
};

	
		


#endif
