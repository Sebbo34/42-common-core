/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:24:49 by sbo               #+#    #+#             */
/*   Updated: 2024/04/24 13:54:11 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "player.h"
#include <mlx.h>
#include <stdio.h>

void	fill_background(
	t_player player, t_map map, t_image background, t_assets assets
) {
	if (0 <= player.x && player.x < map.width
		&& 0 <= player.y && player.y < map.height
		&& map.tiles[(int) player.y * map.width + (int) player.x] == TILE_FLOOR)
	{
		fill_rect((t_rect){0, 0, background.width, background.height / 2},
			background, assets.ceiling);
		fill_rect((t_rect){0, background.height / 2, background.width,
			background.height / 2}, background, assets.floor);
	}
	else
	{
		fill_rect((t_rect){0, 0, background.width, background.height},
			background, (t_color){0});
	}
}

int	game_loop(t_loop_context *context)
{
	t_image		background;
	int			index;

	background = context->window.background;
	move_player(*context->keys, &context->scene->player);
	fill_background(context->scene->player, context->scene->map, background,
		context->scene->assets);
	index = 0;
	while (index < background.width)
	{
		display_column(*context->scene, background, index);
		index++;
	}
	update_window(context->window);
	return (0);
}

int	main(int argc, char **argv)
{
	t_window		window;
	t_scene			scene;
	t_keys			keys;

	keys = (t_keys){0};
	if (argc != 2)
		return (printf("Error\n%s expects a map argument\n", argv[0]), 1);
	if (!create_window(&window, WINDOW_WIDTH, WINDOW_HEIGHT))
		return (1);
	if (argc != 2 || !load_scene(argv[1], &scene, window.mlx_context))
		return (destroy_window(window), 1);
	if (!open_window(&window, &keys))
		return (destroy_window(window), 1);
	mlx_loop_hook(window.mlx_context, game_loop, &(t_loop_context){
		window, &scene, &keys});
	mlx_loop(window.mlx_context);
	close_window(window);
	destroy_scene(scene, window.mlx_context);
	destroy_window(window);
}
