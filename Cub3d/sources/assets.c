/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:12:09 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assets.h"
#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>

void	free_incomplete_assets(t_incomplete_assets tmp, void *mlx_context)
{
	if (tmp.is_found[0])
		destroy_image(mlx_context, tmp.images[0]);
	if (tmp.is_found[1])
		destroy_image(mlx_context, tmp.images[1]);
	if (tmp.is_found[2])
		destroy_image(mlx_context, tmp.images[2]);
	if (tmp.is_found[3])
		destroy_image(mlx_context, tmp.images[3]);
}

bool	match_identifier(char **line, int *index)
{
	char *const	identifier[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (ft_str_match(line, identifier[i]))
		{
			if (!ft_str_match(line, " "))
				return (false);
			skip_spaces(line);
			*index = i;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	parse_asset(t_str line, t_incomplete_assets *assets, void *mlx_context)
{
	char *const	id = line.str;
	int			id_len;
	int			i;

	ft_strnchr(line.str, line.len, ' ', &id_len);
	if (!match_identifier(&line.str, &i))
		return (printf("Error\n%.*s: Invalid asset identifier\n", id_len,
				id), false);
	if (assets->is_found[i])
		return (printf("Error\n%.*s: Duplicate asset\n", id_len, id), false);
	if (i < 4)
	{
		if (!load_image(mlx_context, &assets->images[i], line.str))
			return (false);
	}
	else
	{
		if (!parse_color(&assets->colors[i - 4], line.str))
			return (false);
	}
	assets->count++;
	assets->is_found[i] = true;
	return (true);
}

bool	parse_assets(int fd, t_assets *assets, void *mlx_context)
{
	t_incomplete_assets	tmp_assets;
	t_str				line;

	tmp_assets = (t_incomplete_assets){0};
	while (tmp_assets.count < 6)
	{
		if (!get_nonempty_line(fd, &line))
			return (free_incomplete_assets(tmp_assets, mlx_context), false);
		if (!parse_asset(line, &tmp_assets, mlx_context))
			return (free_incomplete_assets(tmp_assets, mlx_context),
				free(line.str), false);
		free(line.str);
	}
	ft_memcpy(assets, &tmp_assets, sizeof(t_assets));
	return (true);
}

void	destroy_assets(t_assets assets, void *mlx_context)
{
	destroy_image(mlx_context, assets.no);
	destroy_image(mlx_context, assets.so);
	destroy_image(mlx_context, assets.we);
	destroy_image(mlx_context, assets.ea);
}
