/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:11 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:49:59 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <math.h>

void	project_ray(t_ray ray, float dist, float *out_x, float *out_y)
{
	*out_x = ray.start_x + ray.direction_x * dist;
	*out_y = ray.start_y + ray.direction_y * dist;
}

t_ray	offset_ray(t_ray ray, float offset_x, float offset_y)
{
	return ((t_ray){
		ray.start_x - offset_x,
		ray.start_y - offset_y,
		ray.direction_x,
		ray.direction_y,
	});
}

enum e_hit_type	ray_hit_map(t_ray ray, t_map map, float *hit_dist)
{
	float			outside_dist;
	enum e_hit_type	outside_hit_type;
	enum e_hit_type	inside_hit_type;

	if (ray.start_x < 0 || map.width <= ray.start_x
		|| ray.start_y < 0 || map.height <= ray.start_y)
	{
		outside_hit_type = ray_hit_rect_outside(ray, map.width,
				map.height, &outside_dist);
		if (outside_hit_type == HIT_NONE)
			return (*hit_dist = INFINITY, HIT_NONE);
		project_ray(ray, outside_dist + 0.01f, &ray.start_x, &ray.start_y);
		if (ray.start_x < 0 || map.width <= ray.start_x
			|| ray.start_y < 0 || map.height <= ray.start_y)
			return (*hit_dist = INFINITY, HIT_NONE);
		*hit_dist = 0;
		inside_hit_type = ray_hit_walls(ray, map, hit_dist);
		*hit_dist += outside_dist;
		if (inside_hit_type == HIT_IN_WALL)
			return (outside_hit_type);
		return (inside_hit_type);
	}
	else
		return (ray_hit_walls(ray, map, hit_dist));
}
