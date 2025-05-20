/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:55:39 by sbo               #+#    #+#             */
/*   Updated: 2024/04/23 14:59:43 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"
#include <math.h>

t_rect	clamp_rect(t_rect rect, int width, int height)
{
	if (rect.start_x < 0)
	{
		rect.width -= fmin(-rect.start_x, rect.width);
		rect.start_x = 0;
	}
	if (rect.start_x >= width - rect.width)
		rect.width = width - rect.start_x;
	if (rect.start_y < 0)
	{
		rect.height -= fmin(-rect.start_y, rect.height);
		rect.start_y = 0;
	}
	if (rect.start_y >= height - rect.height)
		rect.height = height - rect.start_y;
	return (rect);
}

void	fill_rect(t_rect rect, t_image image, t_color color)
{
	int	i;
	int	j;

	rect = clamp_rect(rect, image.width, image.height);
	i = 0;
	while (i < rect.height)
	{
		j = 0;
		while (j < rect.width)
		{
			put_pixel(image, rect.start_x + j, rect.start_y + i, color);
			j++;
		}
		i++;
	}
}
