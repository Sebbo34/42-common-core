/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:30:00 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:43:21 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <mlx.h>
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>

bool	create_window(t_window *window, int width, int height)
{
	window->mlx_context = mlx_init();
	if (!window->mlx_context)
		return (printf("Error\nWindow creation failed\n"), false);
	if (!create_image(window->mlx_context, &window->background, width, height))
	{
		mlx_destroy_display(window->mlx_context);
		free(window->mlx_context);
		return (false);
	}
	return (true);
}

bool	open_window(t_window *window, t_keys *keys)
{
	static t_key_event_context	key_context;

	window->window = mlx_new_window(window->mlx_context,
			window->background.width, window->background.height, "Cub3D");
	if (!window->window)
		return (printf("Error\nWindow creation failed\n"), false);
	mlx_hook(window->window, DestroyNotify, 1L << 0, cross_event, window);
	key_context.keys = keys;
	key_context.mlx_context = window->mlx_context;
	mlx_hook(window->window, KeyPress, KeyPressMask, key_press, &key_context);
	mlx_hook(window->window, KeyRelease, KeyReleaseMask, key_release,
		&key_context);
	return (true);
}

void	update_window(t_window window)
{
	mlx_put_image_to_window(window.mlx_context, window.window,
		window.background.mlx_image, 0, 0);
}

void	close_window(t_window window)
{
	mlx_destroy_window(window.mlx_context, window.window);
}

void	destroy_window(t_window window)
{
	destroy_image(window.mlx_context, window.background);
	mlx_destroy_display(window.mlx_context);
	free(window.mlx_context);
}
