/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:24:49 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:56:55 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <math.h>

void	draw_column(t_image_column dest, t_image_column src, float dest_height)
{
	const int	capped_dest_height = fmin(dest_height, dest.image.height);
	const int	src_offset = (dest_height - capped_dest_height) / 2;
	const int	dest_offset = (dest.image.height - capped_dest_height) / 2;
	const float	src_ratio = src.image.height / dest_height;
	int			i;

	i = 0;
	while (i < capped_dest_height)
	{
		put_pixel(dest.image, dest.index, i + dest_offset,
			get_pixel(src.image, src.index, (i + src_offset) * src_ratio));
		i++;
	}
}

float	get_wall_height(
	t_image background, t_player player, t_ray ray, float hit_dist
) {
	float	dist;

	dist = (player.direction_x * ray.direction_x
			+ player.direction_y * ray.direction_y) * hit_dist;
	return (background.height / (2 * tan(FOV * M_PI / 360)
			* background.height / background.width * dist));
}

t_image_column	get_src_column(
	t_assets assets, t_ray ray, float hit_type, float hit_dist
) {
	float	hit_x;
	float	hit_y;

	project_ray(ray, hit_dist, &hit_x, &hit_y);
	if (hit_type == HIT_WE && ray.direction_x > 0)
	{
		return ((t_image_column){assets.ea,
			(hit_y - (int)hit_y) * assets.ea.width});
	}
	else if (hit_type == HIT_WE && ray.direction_x < 0)
	{
		return ((t_image_column){assets.we,
			((int)hit_y + 1 - hit_y) * assets.we.width});
	}
	else if (hit_type == HIT_NS && ray.direction_y > 0)
	{
		return ((t_image_column){assets.so,
			((int)hit_x + 1 - hit_x) * assets.so.width});
	}
	else
	{
		return ((t_image_column){assets.no,
			(hit_x - (int)hit_x) * assets.no.width});
	}
}

void	display_column(t_scene scene, t_image background, int index)
{
	t_ray			ray;
	float			hit_dist;
	enum e_hit_type	hit_type;
	float			wall_height;
	t_image_column	src_column;

	ray = ray_from_view_column(scene.player, (float) index / background.width);
	hit_type = ray_hit_map(ray, scene.map, &hit_dist);
	wall_height = get_wall_height(background, scene.player, ray, hit_dist);
	if (hit_type == HIT_NS || hit_type == HIT_WE)
	{
		src_column = get_src_column(scene.assets, ray, hit_type, hit_dist);
		draw_column((t_image_column){background, index}, src_column,
			wall_height);
	}
}
