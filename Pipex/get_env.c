/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:46:28 by sbo               #+#    #+#             */
/*   Updated: 2024/01/27 14:17:49 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_exec(char *cmd)
{
	char	**r_split;

	r_split = ft_split(cmd, ' ');
	if (access(r_split[0], F_OK) == 0)
	{
		if (access(r_split[0], X_OK) == 0)
			return (r_split);
	}
	write(2, "no such file or directory: ", 27);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	free_split(r_split);
	return (NULL);
}

void	free_split(char **r_split)
{
	int	j;

	j = 0;
	while (r_split[j])
	{
		free(r_split[j]);
		j++;
	}
	free(r_split);
}

char	**ft_get_env(char **env)
{
	int		i;
	char	**r_split;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			r_split = ft_split(&env[i][5], ':');
			if (!r_split)
				return (NULL);
			return (r_split);
		}
		i++;
	}
	return (NULL);
}

char	**ft_join_cmd(char *path, char *cmd)
{
	char	*chaine;
	char	*path_cmd;
	char	**r_split;

	chaine = ft_strjoin(path, "/");
	if (!chaine)
		exit(1);
	path_cmd = ft_strjoin(chaine, cmd);
	if (!path_cmd)
		exit(1);
	free(chaine);
	r_split = ft_split(path_cmd, ' ');
	free(path_cmd);
	if (!r_split)
		exit(1);
	return (r_split);
}

char	**check_cmd(char **env, char *cmd)
{
	char	**r_split;
	char	**path;
	int		i;

	if (ft_strcmp(cmd, "") == 0)
		return (write(2, "Permission denied\n", 18), NULL);
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
		return (ft_exec(cmd));
	path = ft_get_env(env);
	i = 0;
	while (path[i])
	{
		r_split = ft_join_cmd(path[i], cmd);
		if (access(r_split[0], F_OK) == 0)
		{
			if (access(r_split[0], X_OK) == 0)
				return (free_split(path), r_split);
		}
		free_split(r_split);
		i++;
	}
	free_split(path);
	write (2, cmd, ft_strlen(cmd));
	write (2, " : Command not found\n", 21);
	return (NULL);
}

/* int main (int argc, char *argv[], char *env[])
{
	char **chaine;
	int i = 0;
	int j;
	
	while (i < argc)
	{
		j = 0;
		chaine = check_cmd(env,argv[i]);
		if (chaine)
			printf("chaine %s\n", chaine[0]);
		i++;
	}
}
 */