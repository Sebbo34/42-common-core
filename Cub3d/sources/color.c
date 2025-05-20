/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:47:19 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 15:09:16 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include "parsing.h"
#include <stdio.h>

bool	parse_intensity(uint8_t *intensity, char **line)
{
	uint8_t	digit;
	uint8_t	value;

	if (!ft_str_match_digit(line, &value))
		return (false);
	if (!ft_str_match_digit(line, &digit))
		return (*intensity = value, true);
	value = value * 10 + digit;
	if (!ft_str_match_digit(line, &digit))
		return (*intensity = value, true);
	if (value > (255 - digit) / 10)
		return (false);
	*intensity = value * 10 + digit;
	return (true);
}

bool	parse_color(t_color *color, char *line)
{
	char *const	color_save = line;

	if (
		!parse_intensity(&color->r, &line)
		|| (skip_spaces(&line), 0)
		|| !ft_str_match(&line, ",")
		|| (skip_spaces(&line), 0)
		|| !parse_intensity(&color->g, &line)
		|| (skip_spaces(&line), 0)
		|| !ft_str_match(&line, ",")
		|| (skip_spaces(&line), 0)
		|| !parse_intensity(&color->b, &line)
		|| !*line == '\0'
	)
		return (printf("Error\n%s: Invalid color\n", color_save), false);
	return (true);
}
