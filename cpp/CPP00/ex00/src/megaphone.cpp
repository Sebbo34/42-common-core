/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:31:56 by seb               #+#    #+#             */
/*   Updated: 2024/07/03 12:18:47 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <iostream>

int main(int argc, char **argv)
{
	int		i;
	char	c;
	int		j;

	i = 0;
	j = 1;
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		while (argv[j])
		{
			i = 0;
			while (argv[j][i])
			{
				if (argv[j][i] >= 'a' && argv[j][i] <= 'z')
					c = toupper(argv[j][i]);
				else
					c = argv[j][i];
				std::cout << c;
				i++;
			}
			j++;
		}
		std::cout << std::endl;
	}
}

