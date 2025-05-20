/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:02:09 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/13 13:30:59 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"

#include<unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
/*
#include <stdio.h>
#include <unistd.h>

void ft_putstr_fd(char *s, int fd);

int main()
{
    char testString[] = "Hello, World!";
    int fileDescriptor = 1;  // 1 est le descripteur de fichier
			     // pour la sortie standard (stdout)

    ft_putstr_fd(testString, fileDescriptor);

    return 0;
}
*/
