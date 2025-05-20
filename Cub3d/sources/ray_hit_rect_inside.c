/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_rect_inside.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:21:11 by sbo               #+#    #+#             */
/*   Updated: 2024/04/23 11:51:35 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <math.h>
#include <stdio.h>

float	ray_hit_vertical_lines(t_ray ray, int width)
{
	if (ray.direction_x == 0)
		return (INFINITY);
	if (ray.direction_x > 0)
		return ((width - ray.start_x) / ray.direction_x);
	else
		return (ray.start_x / -ray.direction_x);
}

float	ray_hit_horizontal_lines(t_ray ray, int height)
{
	if (ray.direction_y == 0)
		return (INFINITY);
	if (ray.direction_y > 0)
		return ((height - ray.start_y) / ray.direction_y);
	else
		return (ray.start_y / -ray.direction_y);
}

float	ray_hit_rect_inside(t_ray ray, int width, int height)
{
	return (
		fmin(
			ray_hit_vertical_lines(ray, width),
			ray_hit_horizontal_lines(ray, height)
		)
	);
}
