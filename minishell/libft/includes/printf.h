/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:25:46 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/01/25 15:54:49 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

int				ft_digit_count_hexa(unsigned long long n, int base);
int				ft_digit_count(int n);
int				ft_printf_char(va_list args);
int				ft_printf_hexa(va_list args, char c);
int				ft_printf_int(va_list args);
int				ft_printf_ptr(va_list args, char flag);
int				ft_printf_str(va_list args);
int				ft_printf(const char *format, ...);
unsigned int	ft_printf_unsign(va_list args);
void			ft_putnbr_hexa(unsigned long long n, char c);
void			ft_putnbr_unsigned(unsigned int nb);
void			ft_putnbr(int n);
void			ft_putchar(char c);

#endif