/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:47:50 by sbo               #+#    #+#             */
/*   Updated: 2024/01/24 13:33:41 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_xpm_to_image2(t_data *data, char *xpm, int ind)
{
	int		i;
	int		j;
	int		k;
	void	*img;

	i = 0;
	j = 0;
	k = -1;
	img = mlx_xpm_file_to_image(data->mlx_ptr, xpm, &i, &j);
	if (img == NULL)
	{
		while (k++ < 10)
			mlx_destroy_image (data->mlx_ptr, data->image->num[k]);
		k = -1;
		while (k++ < ind)
			mlx_destroy_image (data->mlx_ptr, data->image->img[k]);
		(ft_lstclear(&(data->maps)), free(data->image->chaine));
		free(data->image);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(1);
	}
	return (img);
}

void	generate_image(t_data	*data)
{
	data->image = malloc(sizeof(t_image));
	generate_number(data);
	data->image->chaine = ft_cpyline("01PECOUDTS23");
	if (!data->image->chaine)
		exit(1);
	data->image->img[0] = ft_xpm_to_image2(data, "sol.xpm", 0);
	data->image->img[1] = ft_xpm_to_image2(data, "wall.xpm", 1);
	data->image->img[2] = ft_xpm_to_image2(data, "perso.xpm", 2);
	data->image->img[3] = ft_xpm_to_image2(data, "exit.xpm", 3);
	data->image->img[4] = ft_xpm_to_image2(data, "item.xpm", 4);
	data->image->img[5] = ft_xpm_to_image2(data, "exit_open.xpm", 5);
	data->image->img[6] = ft_xpm_to_image2(data, "perso1.xpm", 6);
	data->image->img[7] = ft_xpm_to_image2(data, "perso2.xpm", 7);
	data->image->img[8] = ft_xpm_to_image2(data, "perso3.xpm", 8);
	data->image->img[9] = ft_xpm_to_image2(data, "sorcier.xpm", 9);
	data->image->img[10] = ft_xpm_to_image2(data, "sorcier1.xpm", 10);
	data->image->img[11] = ft_xpm_to_image2(data, "sorcier2.xpm", 11);
}	

void	push_image(t_data *data, char c, int x, int y)
{
	int	i;
	int	check;

	i = 0;
	while (data->image->chaine[i] != c)
		i++;
	check = mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->image->img[i], x, y);
	if (check < 0)
		end_prog(data);
}

void	open_the_door(t_data *data)
{
	int		i;
	t_maps	*temp;

	i = 0;
	temp = data->maps;
	while (temp->next)
	{
		i = 0;
		while (temp->line[i])
		{
			if (temp->line[i] == 'E')
				push_image(data, 'O', i * 32, 32 * temp->y + 16);
			i++;
		}
		temp = temp->next;
	}
}

void	creat_maps(t_data *data)
{
	int		i;
	int		x;
	int		y;
	t_maps	*temp;

	temp = data->maps;
	y = 16;
	ft_putnbr_img(0, data, (ft_strlen(temp->line) * 32) / 2);
	while (temp->next)
	{
		i = 0;
		x = 0;
		while (i < ft_strlen(temp->line))
		{
			push_image(data, temp->line[i], x, y);
			i++;
			x = x + 32;
		}
		temp = temp->next;
		y = y + 32;
	}
}
