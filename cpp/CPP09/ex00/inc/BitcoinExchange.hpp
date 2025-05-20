/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:40:28 by sbo               #+#    #+#             */
/*   Updated: 2024/11/11 15:13:53 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib> 

bool            skipSpace(std::string &line);
void            TruncNumberAndSpace(std::string &line, int &check);
void            printResult(std::map<std::string , float> data, std::string date, std::string value);
bool            checkFormat(std::string line);
std::string     extractDate(std::string line);
std::string     extractValue(std::string line);
int             maxDay(int month, int year);
bool            isValidDate(std::string date);
bool            isValidValue(std::string value);

#endif