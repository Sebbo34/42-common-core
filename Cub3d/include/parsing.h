/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:56:52 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:42:19 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <sys/types.h>
# include <stdbool.h>
# include <stdint.h>

//								8 KiB
# define BUFFER_SIZE			8192
# define MEM_ERROR_MESSAGE		"Error\nOut of memory\n"
# define READ_ERROR_MESSAGE		"Error\nFile is no longer valid\n"

typedef struct s_str
{
	char	*str;
	int		len;
}	t_str;

typedef struct s_str_array
{
	t_str	*strs;
	int		len;
}	t_str_array;

typedef struct s_buffer
{
	char	buffer[BUFFER_SIZE];
	int		pos;
	int		len;
}	t_buffer;

enum e_read_status
{
	READ_OK,
	READ_END,
	READ_ERROR,
};

enum e_read_status	get_next_line(int fd, t_str *line);
bool				get_nonempty_line(int fd, t_str *line);
void				ft_memcpy(void *dst, void *src, int size);
bool				ft_str_match(char **str, char *prefix);
void				skip_spaces(char **str);
bool				ft_str_match_digit(char **str, uint8_t *digit);
bool				ft_strnchr(char *str, int len, char c, int *pos);

bool				push_str(t_str_array *array, t_str str);
int					get_max_len(t_str_array *lines);
void				free_str_array(t_str_array array);

#endif