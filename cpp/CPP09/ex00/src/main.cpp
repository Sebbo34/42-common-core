/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:33:27 by seb               #+#    #+#             */
/*   Updated: 2024/11/10 14:56:27 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	std::ifstream csv("data.csv");
	if (argc != 2)
	{
		std::cerr << "Invalid number of args" << std::endl;
		return (1);
	}
	std::ifstream input(argv[1]);
	if(csv && input)
	{
		int sep;
		std::map<std::string, float> data;
		std::string line;
		std::string date;
		std::string value;
		getline(csv, line);
		while (getline(csv, line))
		{
			sep = line.find_first_of(',');
			data[line.substr(0,sep)] = atof (line.substr(sep + 1, line.size() - sep).c_str());
		}
		int first = 0;
		std::string tmp = "date | value";
		while (getline(input, line))
		{
			if (((line.compare(tmp) != 0) || first == 1) && checkFormat(line))
			{
		 		date = extractDate(line);
				value = extractValue(line);
				if (isValidDate(date) && isValidValue(value))
					printResult(data, date, value);
			}
			first = 1;
		}	
	}
	else
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	return (0);
}