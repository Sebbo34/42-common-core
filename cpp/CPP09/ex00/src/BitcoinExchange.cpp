/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:40:13 by sbo               #+#    #+#             */
/*   Updated: 2024/11/11 17:16:23 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool skipSpace(std::string &line)
{
	if (line.size() == 0)
		return false;
	if (line[0] != ' ' && line[0] != '\t')
		return false;	
	while(line[0] == ' ' || line[0] == '\t')
		line.erase(0,1);
	return true;
}
void TruncNumberAndSpace(std::string &line, int &check)
{
	if (check >= 0)
	{
		while (isdigit(line[0]))
			line.erase(0,1);
		if (check == 2)
		{
			if (!skipSpace(line))
				check = 3;
		}
	}
	if (check == -1)
	{
		if (!skipSpace(line))
			check = 3;
		if (line.size() && line[0] == '-')
			check = 4;
		while (line.size() && isdigit(line[0]))
		{
			line.erase(0,1);
			if (line.size() && line[0] == '.')
				line.erase(0,1);
		}
		if (line[0] == 'f')
			line.erase(0,1);
		skipSpace(line);
	}
}


void	printResult(std::map<std::string , float> data, std::string date, std::string value)
{
	if (data.find(date) != data.end())
		std::cout << date << " => " << value << " = " << atof(value.c_str()) * data[date] << std::endl;
	else
	{
        while (date.size() && date[0] == '0')
			date.erase(0,1);
		if (date.size() > 10)
		{
			std::map<std::string , float>::iterator it = data.end();
			it--;
			std::cout << date << " => " << value << " = " << atof(value.c_str()) * it->second << std::endl;
			return ;
		}
		else if (date.size() < 10)
		{
            if (date.size() && date[0] == '-')
                std::cout << "0000" << date << " => " << " Bitcoin doesn't exist."<< std::endl;
            else 
			    std::cout << date  << " => " << " Bitcoin doesn't exist."<< std::endl;
			return ;
		}
		data[date] = 1;
		std::map<std::string , float>::iterator it = data.find(date);
		if (it != data.begin())
		{
			it--;
			std::cout << date << " => " << value << " = " << atof(value.c_str()) * it->second << std::endl;
			data.erase(date);
		}
		else
			std::cout << date  << " => " << " Bitcoin doesn't exist."<< std::endl;
	}
}

bool	checkFormat(std::string line)
{
	std::string tmp;
	tmp = line;
	int check = 0;
	skipSpace(line);
	while(line.size() > 0)
	{
		TruncNumberAndSpace(line, check);
		if (line.size() && line[0] == '-' && check < 2)
		{
			check++;
			line.erase(0,1);
		}
		else if (line.size() && line[0] == '|' && check == 2)
		{
			check = -1;
			line.erase(0,1);
			TruncNumberAndSpace(line, check);
			if (line.empty() && check == -1)
				return true;
			else if (check == 4)
			{
				std::cerr << "Error: not a positive number." << std::endl;
				return false;
			}
			else
			{
				std::cerr << "Error: bad input => " << tmp << std::endl;
				return false;
			}
		}
		else
			break;
	}
	std::cerr << "Error: bad input => " << tmp << std::endl;
	return false;
}

std::string extractDate(std::string line)
{
	skipSpace(line);
	return (line.substr(0, line.find_first_of(" ")));
}


std::string extractValue(std::string line)
{
	line.erase(0, line.find_first_of('|') + 1);
	skipSpace(line);
	return (line.substr(0, line.find_first_of(" ")));
}


int maxDay(int month, int year)
{
	if (month == 1 ||month == 3 || month == 5 ||month == 7 || month == 8 || month == 10 || month == 12)
		return (31);
	else if (month == 2 && year % 4 == 0)
		return (29);
	else if (month == 2)
		return (28);
	else
		return (30);
}


bool isValidDate(std::string date)
{
	int	year = atoi(date.substr(0, date.find_first_of("-")).c_str());
	date.erase(0, date.find_first_of("-") + 1);
	int	month = atoi(date.substr(0, date.find_first_of("-")).c_str());
	if (date.find_first_of("-") + 1 != 3)
	{
		std::cerr << "Error: Invalid format." << std::endl;
		return false;
	}
	date.erase(0, date.find_first_of("-") + 1);
	if (date.size() != 2)
	{
		std::cerr << "Error: Invalid format." << std::endl;
		return false;
	}
	int day = atoi(date.c_str());
	if (month > 12 || month < 1 || day > maxDay(month, year))
	{
		std::cerr << "Error: Invalid date." << std::endl;
		return false;
	}
	return true;
}


bool isValidValue(std::string value)
{
	if (value.find_first_of(".") == value.npos)
	{
		while (value.size() && value[0] == '0')
			value.erase(0,1);
		if (value.size() == 0)
			return true;
		if (value.size() > 4)
		{
			std::cerr << "Error: too large a number." << std::endl;
			return false;
		}
		int val = atoi(value.c_str());
		if (val > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			return false;
		}
	}
	else 
	{
		double val = atof(value.c_str());
		if (val > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			return false;
		}
	}
	return true;
}