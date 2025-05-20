/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:49:56 by sbo               #+#    #+#             */
/*   Updated: 2024/01/26 19:56:22 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_main
{
	int		argc;
	char	**argv;
	char	**env;
}t_main;

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	**check_cmd(char **env, char *cmd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_split(char **r_split);
void	pipex_rec(int fd, t_main main, int i);
void	job(int i, t_main main, int *tube);
int		ft_open_fd2(t_main main);
void	job_parent(int fd, int *tube, int *i, t_main main);

#endif