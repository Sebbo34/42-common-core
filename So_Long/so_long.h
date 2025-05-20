/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:20:53 by seb               #+#    #+#             */
/*   Updated: 2024/01/24 13:42:17 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <time.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

typedef struct s_perso
{
	int	x;
	int	y;
	int	nbr_mouv;
	int	item;
}	t_perso;

typedef struct s_sorc
{
	int				x;
	int				y;
	struct s_sorc	*next;
}	t_sorc;

typedef struct s_maps
{
	int				y;
	char			*line;
	struct s_maps	*next;
}	t_maps;

typedef struct s_image
{
	void	*img[12];
	void	*num[11];	
	char	*chaine;
}	t_image;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	clock_t	start;
	t_image	*image;
	t_perso	*perso;
	t_maps	*maps;
	t_sorc	*sorc;
}	t_data;

t_maps	*ft_lstnew(void *content, int *y);
t_maps	*ft_lstlast(t_maps *lst);
void	ft_lstadd_back(t_maps **lst, t_maps *new);
void	ft_lstclear(t_maps **lst);
int		ft_strlen(const char *str);
t_maps	*creat_struc(int fd);
int		ft_cmd(int key, t_data *data);
void	creat_maps(t_data *data);
int		ft_cmd(int key, t_data *data);
void	push_image(t_data *data, char c, int x, int y);
void	ft_move(t_data *data, t_maps *maps, t_perso *perso, char c);
void	find_perso(t_data *data);
void	open_the_door(t_data *data);
int		anim_sorc(t_data *data, t_sorc *tmp);
void	generate_image(t_data	*data);
int		move_sorc(t_data *data);
void	find_sorc(t_data *data);
void	ft_putnbr_img(int n, t_data *data, int x);
void	generate_number(t_data *data);
int		checkpath(t_maps *maps);
char	ctrl(t_maps *maps, t_sorc *sorc, char c);
char	*ft_cpyline(char *src);
int		check_item(t_maps *maps);
int		check_all(t_maps *maps);
t_maps	*cpy_struc(t_maps *src);
void	modif_maps(t_data *data, int x, int y, char c);
char	ctrl_struc(t_maps *maps, t_perso *perso, char c);
void	push_perso(t_data *data, t_perso *perso, int x, int y);
int		end_prog(t_data *data);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_xpm_to_image(t_data *data, char *xpm, int ind);
void	ft_destroy(t_data *data, int check);
void	findpathrec(t_maps *maps, t_sorc *coor);
void	find_path(t_maps *maps, t_sorc *coor);
void	print_msg(int i);

#endif