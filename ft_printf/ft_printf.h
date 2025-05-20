/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:42:03 by sbo               #+#    #+#             */
/*   Updated: 2023/11/22 12:50:10 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

char	*ft_itoa(long n);
int		ft_affiche_hexa(unsigned int nbr, char *base);
int		ft_printf(const char *format, ...);
size_t	ft_strlen(const char *str);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putnbr_fd(int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_uputnbr(unsigned int nbr);
int		aff_p( unsigned long long nbr, char *base);

#endif 
