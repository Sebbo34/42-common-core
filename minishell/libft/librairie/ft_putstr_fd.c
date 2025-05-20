/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:02:09 by dliuzzo           #+#    #+#             */
/*   Updated: 2023/11/13 17:00:53 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/printf.h"

#include<unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
/*
int main() {
    // Test case 1: Print a string to standard output (stdout)
    char str1[] = "Hello, World!";
    ft_putstr_fd(str1, 1);  // 1 represents stdout
    write(1, "\n", 1);  // Print a newline for better formatting

    // Test case 2: Print a string to standard error (stderr)
    char str2[] = "This is an error message.";
    ft_putstr_fd(str2, 2);  // 2 represents stderr
    write(2, "\n", 1);  // Print a newline for better formatting

    // Test case 3: Print an empty string to standard output
    char str3[] = "";
    ft_putstr_fd(str3, 1);  // 1 represents stdout
    write(1, "\n", 1);  // Print a newline for better formatting

    return 0;
}
*/
