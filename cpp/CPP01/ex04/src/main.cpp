/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 04:19:36 by seb               #+#    #+#             */
/*   Updated: 2024/07/03 16:18:35 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>

int main(int argc, char **argv)
{
	size_t pos = 0;
	std::string newfile;
	std::string str;
	int len;
	int same;

	same = 0;
	if (argc != 4)
	{
		std::cout << "Invalid number of args" << std::endl; 
		return (1);
	}
	str = argv[2];
	if (str.compare(argv[3]) == 0)
		same = 1;
	len = str.length();
	std::ifstream fichier(argv[1]);
	if (!fichier)
	{
		std::cout << "No such file or directory" << std::endl;
		return (1);
	}
	newfile = argv[1];
	newfile.append(".replace");
	std::ofstream fichier2(newfile.c_str());
	if (!fichier2)
	{
		std::cout << "Error in " << newfile << std::endl;
		return (1);
	}
	while (getline(fichier, str))
	{
		pos = str.find(argv[2]);
		while ( pos != str.npos && same == 0)
		{
			str.erase(pos, len);
			str.insert(pos, argv[3]);
			pos = str.find(argv[2]);
		}
		fichier2 << str << std::endl;
	}
	return (0);
}