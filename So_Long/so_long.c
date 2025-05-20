/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:01:32 by seb               #+#    #+#             */
/*   Updated: 2024/01/24 14:05:08 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_cmd(int key, t_data *data)
{
	if (key == 65307)
		end_prog(data);
	if (key == 'w')
		ft_move(data, data->maps, data->perso, 'h');
	if (key == 'a')
		ft_move(data, data->maps, data->perso, 'g');
	if (key == 's')
		ft_move(data, data->maps, data->perso, 'b');
	if (key == 'd')
		ft_move(data, data->maps, data->perso, 'd');
	ft_putnbr_img(data->perso->nbr_mouv, data,
		(ft_strlen(data->maps->line) * 32) / 2);
	return (0);
}

void	ft_destroy(t_data *data, int check)
{
	int	i;

	i = -1;
	ft_lstclear(&(data->maps));
	while (i++ < 11)
		mlx_destroy_image (data->mlx_ptr, data->image->img[i]);
	i = -1;
	while (i++ < 9)
		mlx_destroy_image (data->mlx_ptr, data->image->num[i]);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	if (check == 1)
		free(data->perso);
	free(data->image->chaine);
	free(data->mlx_ptr);
	free(data->image);
	exit(1);
}

int	end_prog(t_data *data)
{
	int		i;
	t_sorc	*temp;

	i = -1;
	ft_lstclear(&(data->maps));
	while (i++ < 11)
		mlx_destroy_image (data->mlx_ptr, data->image->img[i]);
	i = -1;
	while (i++ < 9)
		mlx_destroy_image (data->mlx_ptr, data->image->num[i]);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	while (data->sorc)
	{
		temp = data->sorc;
		data->sorc = data->sorc->next;
		free(temp);
	}
	free(data->perso);
	free(data->image->chaine);
	free(data->mlx_ptr);
	free(data->image);
	exit(1);
	return (0);
}

int	test_ber(char *chaine)
{
	int	i;

	i = ft_strlen(chaine) - 4;
	if (chaine[i] == '.' && chaine[i + 1] == 'b'
		&& chaine[i + 2] == 'e' && chaine[i + 3] == 'r')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (argc != 2)
		return (print_msg(0), 0);
	if (test_ber(argv[1]) == 0)
		return (print_msg(6), 0);
	fd = open(argv[1], -O_RDONLY);
	if (fd == -1)
		return (print_msg(1), 0);
	data.start = clock();
	data.maps = creat_struc(fd);
	close(fd);
	if (check_all(data.maps) != 0)
		(print_msg(check_all(data.maps)), ft_lstclear(&(data.maps)), exit(1));
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			(ft_strlen(data.maps->line)) * 32,
			ft_lstlast(data.maps)->y * 32 + 16, "Hello world!");
	generate_image(&data);
	(find_perso(&data), find_sorc(&data), creat_maps(&data));
	mlx_key_hook(data.win_ptr, ft_cmd, &data);
	mlx_hook(data.win_ptr, 17, 0, &end_prog, &data);
	mlx_loop_hook(data.mlx_ptr, move_sorc, &data);
	mlx_loop(data.mlx_ptr);
}
