/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:31:08 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:50:47 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "parsing.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

bool	ft_str_equals(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i])
	{
		if (a[i] != b[i])
			return (false);
		i++;
	}
	return (true);
}

bool	load_scene(char *path, t_scene *scene, void *mlx_context)
{
	int		fd;
	int		path_len;

	path_len = ft_strlen(path);
	if (path_len <= 4 || !ft_str_equals(&path[path_len - 4], ".cub"))
		return (printf("Error\nInvalid map file\n"), false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nInvalid map file\n"), false);
	if (!parse_assets(fd, &scene->assets, mlx_context))
		return (close(fd), false);
	if (!parse_map(fd, &scene->map, &scene->player))
		return (destroy_assets(scene->assets, mlx_context), close(fd), false);
	close (fd);
	return (true);
}

void	destroy_scene(t_scene scene, void *mlx_context)
{
	destroy_assets(scene.assets, mlx_context);
	free(scene.map.tiles);
}
