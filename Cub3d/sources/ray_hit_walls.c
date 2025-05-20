/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:57:22 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 14:28:06 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <math.h>
#include <stdio.h>

bool	check_wall_ns(t_ray ray, float dist, t_map map)
{
	float	check_x;
	float	check_y;

	project_ray(ray, dist + 0.0001f, &check_x, &check_y);
	if (ray.direction_y > 0)
		check_y += 0.5f;
	else
		check_y -= 0.5f;
	return (map.tiles[(int) check_y * map.width + (int) check_x] == TILE_WALL);
}

bool	check_wall_we(t_ray ray, float dist, t_map map)
{
	float	check_x;
	float	check_y;

	project_ray(ray, dist + 0.0001f, &check_x, &check_y);
	if (ray.direction_x > 0)
		check_x += 0.5f;
	else
		check_x -= 0.5f;
	return (map.tiles[(int) check_y * map.width + (int) check_x] == TILE_WALL);
}

// V1 (3 whiles)
// V2 (2 whiles)
// V3 (1 whiles)

// V2
enum e_hit_type	ray_hit_ns_quadrants(
	t_ray ray, t_ray_progress progress, t_map map, float *hit_dist
) {
	while (true)
	{
		while (progress.hor_dist < progress.max_dist - 0.01f
			&& progress.hor_dist < progress.vert_dist)
		{
			if (check_wall_ns(ray, progress.hor_dist, map))
				return (*hit_dist = progress.hor_dist, HIT_NS);
			progress.hor_dist += 1 / fabs(ray.direction_y);
		}
		if (progress.vert_dist >= progress.max_dist - 0.01f)
			break ;
		if (check_wall_we(ray, progress.vert_dist, map))
			return (*hit_dist = progress.vert_dist, HIT_WE);
		progress.vert_dist += 1 / fabs(ray.direction_x);
	}
	return (*hit_dist = INFINITY, HIT_NONE);
}

enum e_hit_type	ray_hit_we_quadrants(
	t_ray ray, t_ray_progress progress, t_map map, float *hit_dist
) {
	while (true)
	{
		while (progress.vert_dist < progress.max_dist - 0.01f
			&& progress.vert_dist < progress.hor_dist)
		{
			if (check_wall_we(ray, progress.vert_dist, map))
				return (*hit_dist = progress.vert_dist, HIT_WE);
			progress.vert_dist += 1 / fabs(ray.direction_x);
		}
		if (progress.hor_dist >= progress.max_dist - 0.01f)
			break ;
		if (check_wall_ns(ray, progress.hor_dist, map))
			return (*hit_dist = progress.hor_dist, HIT_NS);
		progress.hor_dist += 1 / fabs(ray.direction_y);
	}
	return (*hit_dist = INFINITY, HIT_NONE);
}

enum e_hit_type	ray_hit_walls(t_ray ray, t_map map, float *hit_dist)
{
	t_ray_progress	progress;

	if (map.tiles[(int) ray.start_y * map.width + (int) ray.start_x]
		== TILE_WALL)
		return (*hit_dist = 0, HIT_IN_WALL);
	progress.max_dist = ray_hit_rect_inside(ray, map.width, map.height);
	progress.vert_dist = ray_hit_vertical_lines(
			offset_ray(ray, (int) ray.start_x, (int) ray.start_y), 1);
	progress.hor_dist = ray_hit_horizontal_lines(
			offset_ray(ray, (int) ray.start_x, (int) ray.start_y), 1);
	if (fabs(ray.direction_y) > fabs(ray.direction_x))
		return (ray_hit_ns_quadrants(ray, progress, map, hit_dist));
	else
		return (ray_hit_we_quadrants(ray, progress, map, hit_dist));
}
