/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_rect_outside.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:11 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:55:35 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <math.h>
#include <stdio.h>

// Horizontal distance to vertical band
float	hor_dist_vert_band(t_ray ray, int width)
{
	if (ray.direction_x > 0 && ray.start_x < 0)
		return (-ray.start_x);
	if (ray.direction_x < 0 && ray.start_x >= width)
		return ((width - ray.start_x));
	return (INFINITY);
}

// Vertical distance to horizontal band
float	vert_dist_hor_band(t_ray ray, int height)
{
	if (ray.direction_y > 0 && ray.start_y < 0)
		return (-ray.start_y);
	if (ray.direction_y < 0 && ray.start_y >= height)
		return ((height - ray.start_y));
	return (INFINITY);
}

enum e_hit_type	ray_hit_rect_outside(
	t_ray ray, int width, int height, float *dist
) {
	float	vert_dist;
	float	hor_dist;

	hor_dist = hor_dist_vert_band(ray, width)
		* (ray.direction_y / ray.direction_x) + ray.start_y;
	if (0 <= hor_dist && hor_dist < height)
		return (*dist = hor_dist_vert_band(ray, width)
			/ ray.direction_x, HIT_WE);
	vert_dist = vert_dist_hor_band(ray, height)
		* (ray.direction_x / ray.direction_y) + ray.start_x;
	if (0 <= vert_dist && vert_dist < width)
		return (*dist = vert_dist_hor_band(ray, height)
			/ ray.direction_y, HIT_NS);
	return (*dist = INFINITY, HIT_NONE);
}
