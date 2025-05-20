/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:07:18 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/25 15:52:28 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/printf.h"
#include<unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb >= 10)
		ft_putnbr_fd((nb / 10), fd);
	ft_putchar_fd(((nb % 10) + '0'), fd);
}

/*
#include <unistd.h>

void ft_putnbr_fd(int n, int fd);

int main(void)
{
    int fd = STDOUT_FILENO; // Replace with the desired file descriptor

    // Test with positive integers
    ft_putnbr_fd(123, fd);
    write(fd, "\n", 1);

    // Test with a negative integer
    ft_putnbr_fd(-456, fd);
    write(fd, "\n", 1);

    // Test with zero
    ft_putnbr_fd(0, fd);
    write(fd, "\n", 1);

    // Test with INT_MIN
    ft_putnbr_fd(-2147483648, fd);
    write(fd, "\n", 1);

    // Test with large positive integer
    ft_putnbr_fd(987654321, fd);
    write(fd, "\n", 1);

    return 0;
}
*/
