/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:57:27 by seb               #+#    #+#             */
/*   Updated: 2024/11/08 11:50:34 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span()
{
}

Span::Span(unsigned int N)
{
    this->N = N;
}

Span::~Span()
{
}
Span::Span(Span const & src)
{
    *this = src;
}
Span & Span::operator=(Span const & src)
{
    if (this != &src)
	{
        container = src.container;
        N = src.N;
	}
	return *this;
}
void    Span::addNumber(int number)
{
    if (this->container.size() > N - 1)
        throw std::out_of_range("Out of range");
    this->container.push_back(number);
}

void    Span::range(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    for (std::vector<int>::iterator it = begin; it != end; it++)
    {
        this->addNumber(*it);
    }
}

int    Span::shortestSpan(void)
{
    std::vector<int>::iterator current;
    std::vector<int>::iterator next;
    int shortest;

    if (this->container.size() < 2)
        throw std::out_of_range ("Size too small");
    current = this->container.begin();
    next = current + 1;
    sort(this->container.begin(), this->container.end());
    shortest = *next - *current;
    while (next != this->container.end())
    {
        if (*next - *current < shortest)
            shortest = *next - *current;
        current++;
        next++;
    }
    return (shortest);
}

int     Span::longestSpan(void)
{
    if (this->container.size() < 2)
        throw std::out_of_range ("Size too small");
    sort(this->container.begin(), this->container.end());
    return (*(this->container.end() - 1) - *this->container.begin());
}
