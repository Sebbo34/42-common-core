/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:44:45 by sbo               #+#    #+#             */
/*   Updated: 2024/01/26 19:56:48 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

void	ft_here_doc(t_main main, int *tube)
{
	char	*chaine;
	char	*temp;

	temp = ft_strjoin(main.argv[2], "\n");
	if (!temp)
		exit(1);
	while (1)
	{
		chaine = get_next_line(0);
		if (!chaine)
		{
			write (2, "here-document delimited by EOF wanted ", 38);
			write (2, temp, ft_strlen(temp));
		}
		if (!chaine || ft_strcmp(chaine, temp) == 0)
		{
			free(chaine);
			break ;
		}
		write(tube[1], chaine, ft_strlen(chaine));
		free(chaine);
	}
	close(tube[1]);
	free(temp);
}

void	pipex_rec(int fd, t_main main, int i)
{
	pid_t	pid;
	int		tube[2];

	if (i < main.argc - 1)
	{
		if (pipe(tube))
			return (perror("pipe"), exit(1));
		pid = fork();
		if (pid == -1)
			return (perror("fork"), exit(1));
		else if (pid == 0)
		{
			close(tube[0]);
			if (ft_strcmp(main.argv[1], "/dev/stdin") == 1 || i != 2)
			{
				if (dup2(fd, 0) == -1)
					exit(1);
			}
			job(i, main, tube);
		}
		else
			job_parent(fd, tube, &i, main);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_main	arg_main;
	int		fd;
	int		tube[2];

	if (argc < 5)
		(write(2, "Il n'y a pas assez d'argument\n", 31), exit(1));
	arg_main.argc = argc;
	arg_main.argv = argv;
	arg_main.env = env;
	if (ft_strcmp (argv[1], "here_doc") == 0)
	{
		if (pipe(tube))
			return (perror("pipe"), exit(1), 1);
		ft_here_doc(arg_main, tube);
		pipex_rec(tube[0], arg_main, 3);
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			perror("fd");
		pipex_rec(fd, arg_main, 2);
	}
}
