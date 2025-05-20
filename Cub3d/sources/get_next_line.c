/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:58:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:42:58 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool	str_append(t_str *str, char *suffix, int len)
{
	char	*tmp;

	tmp = malloc(str->len + len + 1);
	if (!tmp)
		return (false);
	ft_memcpy(tmp, str->str, str->len);
	ft_memcpy(tmp + str->len, suffix, len);
	tmp[str->len + len] = '\0';
	free(str->str);
	str->str = tmp;
	str->len += len;
	return (true);
}

enum e_read_status	get_next_line(int fd, t_str *line)
{
	static t_buffer	buf;
	int				newline_pos;

	*line = (t_str){NULL, 0};
	while (true)
	{
		if (ft_strnchr(&buf.buffer[buf.pos],
				buf.len - buf.pos, '\n', &newline_pos))
		{
			if (!str_append(line, &buf.buffer[buf.pos], newline_pos))
				return (free(line->str), printf(MEM_ERROR_MESSAGE), READ_ERROR);
			buf.pos += newline_pos + 1;
			return (READ_OK);
		}
		if (!str_append(line, &buf.buffer[buf.pos], buf.len - buf.pos))
			return (free(line->str), printf(MEM_ERROR_MESSAGE), READ_ERROR);
		buf.pos = 0;
		buf.len = read(fd, buf.buffer, BUFFER_SIZE);
		if (buf.len < 0)
			return (free(line->str), printf(READ_ERROR_MESSAGE), READ_ERROR);
		if (buf.len == 0 && !line->len)
			return (free(line->str), READ_END);
		if (buf.len == 0)
			return (READ_OK);
	}
}

bool	get_nonempty_line(int fd, t_str *line)
{
	while (get_next_line(fd, line) == READ_OK)
	{
		if (line->len != 0)
			return (true);
		free(line->str);
	}
	return (false);
}
