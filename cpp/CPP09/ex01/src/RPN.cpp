/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 00:17:08 by sbo               #+#    #+#             */
/*   Updated: 2024/11/11 17:09:12 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

//attention boucle for
// faire avec une stack

bool	ft_isdigit(std::string elem)
{
	if (elem.size() != 1)
		return (false);
	if (!isdigit(elem[0]))
		return (false);
	return (true);
}

bool	isoperator(std::string op) 
{
	if (op.size() != 1)
		return (false);
	if (op[0] == '+')
		return true;
	if (op[0] == '-')
		return true;
	if (op[0] == '/')
		return true;
	if (op[0] == '*')
		return true;
	return(false);
}

bool calcul(int a, int b, char c, int &result)
{
	if (c == '+')
	{
		if (b > 0 && a > 2147483647 - b)
		{
			std::cerr << "Overflow" << std::endl;
			return false;
		}
		if (b < 0 && a < -2147483648 - b)
		{
			std::cerr << "Underflow" << std::endl;
			return false;
		}
		result = a + b;
	}
	if (c == '-')
	{
		if (b < 0 && a > 2147483647 + b)
		{
			std::cerr << "Overflow"<<  std::endl;
			return false;
		}
		if (b > 0 && a < -2147483648 + b)
		{
			std::cerr << "Underflow" << std::endl;
			return false;
		}
		result = a - b;
	}	
	if (c == '/')
	{
		if ((a == -2147483648 && b == -1))
		{
			std::cerr << "Overflow" << std::endl;
			return false;
		}
		if (b == 0)
		{
			std::cerr << "Division par 0" << std::endl;
			return false;
		}
		result = a / b;
	}	
	if (c == '*')
	{
		if ( ((a > 0 && b > 0) || (a < 0 && b < 0))  && a > 2147483647 / b)
		{
			std::cerr << "Overflow" << std::endl;
			return false;
		}
		else if ( ((a < 0 && b > 0) || (a > 0 && b < 0))  && a < -2147483648 / b)
		{
			std::cerr << "Underflow" << std::endl;
			return false;
		}
		if ((a == -2147483648 && b == -1))
		{
			std::cerr << "Overflow" << std::endl;
			return false;
		}
		result = a * b;
	}
	return (true);
}

void	RPN(std::string args)
{
	std::stack<int> stack;
	unsigned long	end = 1;
	int tmp;
	if (args.find_first_of(" ") == args.npos)
	{
		std::cerr << "Error" << std::endl;
		return ;
	}
	while (end != args.npos)
	{
		if (args.size() == 0)
		{
			std::cerr << "Error" << std::endl;
			return;
		}
		end = args.find_first_of(" ");
		if (ft_isdigit(args.substr(0, end)))
			stack.push(atoi(args.substr(0, end).c_str()));
		else if (isoperator(args.substr(0, end)) && stack.size() >= 2)
		{
			int result;
			tmp = stack.top();
			stack.pop();
			if (!calcul(stack.top(), tmp,args[0], result))
				return ;
			stack.pop();
			stack.push(result);
		}
		else
		{
			std::cerr << "Error" << std::endl;
			return;
		}
		if (end != args.npos)
			args = args.erase(0, end + 1);
	}
	if (stack.size() == 1)
		std::cout << stack.top() << std::endl;
	else 
		std::cerr << "Error" << std::endl;
}

