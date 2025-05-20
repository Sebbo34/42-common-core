/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:54:48 by sbo               #+#    #+#             */
/*   Updated: 2024/01/26 19:56:42 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	job_parent(int fd, int *tube, int *i, t_main main)
{
	int	check;

	check = close(tube[1]);
	if (check == -1)
		exit(1);
	check = close(fd);
	if (check == -1)
		exit(1);
	*i = *i + 1;
	pipex_rec(tube[0], main, *i);
	wait(NULL);
}

int	ft_open_fd2(t_main main)
{
	int	fd2;

	fd2 = open(main.argv[main.argc - 1], O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd2 == -1)
	{
		if (access(main.argv[main.argc - 1], W_OK) == 0)
		{
			if (ft_strcmp(main.argv[1], "here_doc") == 0)
				fd2 = open(main.argv[main.argc - 1], O_RDWR | O_APPEND);
			else
				fd2 = open(main.argv[main.argc - 1], O_RDWR | O_TRUNC);
		}
		else
		{
			write(2, "Permission denied: ", 19);
			write(2, main.argv[main.argc - 1],
				ft_strlen(main.argv[main.argc - 1]));
			write(2, "\n", 1);
		}
	}
	if (fd2 < 0)
		exit(2);
	return (fd2);
}

void	job(int i, t_main main, int *tube)
{
	int		fd2;
	char	**split;
	int		check;

	split = check_cmd(main.env, main.argv[i]);
	if (!split)
		exit(1);
	if (i == main.argc - 2)
	{
		fd2 = ft_open_fd2(main);
		check = dup2(fd2, 1);
		close(fd2);
	}
	else
	{
		check = dup2(tube[1], 1);
		close(tube[1]);
	}
	if (check == -1)
		(free_split(split), exit(1));
	execve(split[0], split, main.env);
	free_split(split);
	exit(1);
}
