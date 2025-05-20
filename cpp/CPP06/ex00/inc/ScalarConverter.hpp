/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:18:15 by sbo               #+#    #+#             */
/*   Updated: 2024/07/20 13:10:34 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCOVERTER_HPP
#define SCALARCOVERTER_HPP

#include <iostream>

class ScalarConverter
{
	private :
		ScalarConverter();
		ScalarConverter(const ScalarConverter &src);
		ScalarConverter &operator=(ScalarConverter const &conv);
	public:
		~ScalarConverter();
		static void	convert(std::string src);
};

#endif