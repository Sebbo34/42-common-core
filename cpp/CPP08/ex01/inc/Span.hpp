/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:57:30 by seb               #+#    #+#             */
/*   Updated: 2024/11/08 11:28:33 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

class Span
{
	private:
		unsigned int    N;
		std::vector<int>     container;
		Span();
	public:
		Span(Span const & src);
		Span & operator=(Span const & src);
		Span(unsigned int N);
		~Span();
		void	addNumber(int number);
		int		shortestSpan(void);
		int		longestSpan(void);
		void	range(std::vector<int>::iterator begin, std::vector<int>::iterator end);
};

#endif