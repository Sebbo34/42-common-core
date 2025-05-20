/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:49:44 by sbo               #+#    #+#             */
/*   Updated: 2023/12/12 18:08:44 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<stdlib.h>
# include<unistd.h>
# include<fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

char	*get_next_line(int fd);
int		check_line(char *chaine, int i, int j);
char	*join_gnl(char *chaine, char *buffer, int j, int *i);
char	*ft_strdup(char *chaine, int fin, int *i);
char	*ft_strdup_f(char *chaine, int fin);

#endif