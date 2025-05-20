/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:46:28 by sbo               #+#    #+#             */
/*   Updated: 2024/04/11 12:36:35 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_exec(t_lexbuf *prompt, char *cmd)
{
	int	check;

	check = 0;
	if (access(cmd, F_OK) == 0)
	{
		check = 1;
		if (access(cmd, X_OK) == 0 && is_directory(cmd) == 0)
			return (cmd);
	}
	if (check == 1)
	{
		prompt->input->exit_status = 126;
		write (2, cmd, ft_strlen(cmd));
		write (2, " : Permission denied\n", 22);
		return (NULL);
	}
	write(2, "no such file or directory: ", 27);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	prompt->input->exit_status = 127;
	return (NULL);
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

char	*check_cmd_in_path(char **env, char *cmd, int *check)
{
	char	*join;
	char	**path;
	int		i;

	path = ft_get_env(env);
	if (!path && check_path_in_env(env) == 1)
		return (NULL);
	i = 0;
	while (path[i])
	{
		join = ft_join_cmd(path[i], cmd);
		if (!join)
			return (free_split(path), NULL);
		if (access(join, F_OK) == 0)
		{
			*check = 1;
			if (access(join, X_OK) == 0)
				return (free_split(path), join);
		}
		free(join);
		i++;
	}
	free_split(path);
	return (NULL);
}

char	*check_cmd(t_lexbuf *prompt, char **env, char *cmd)
{
	char	*join;
	int		check;

	check = 0;
	if (ft_strcmp(cmd, "") == 0)
		return (write(2, " '' : Command not found\n", 25), NULL);
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
		return (ft_exec(prompt, cmd));
	if (access(cmd, X_OK) == 0
		&& is_directory(cmd) && ft_strchr2(cmd, '/') == 1)
		return (write_error(prompt, "Is a directory\n", NULL, 126), NULL);
	else if (access(cmd, X_OK) == 0 && cmd[0] == '/')
		return (ft_strdup(cmd));
	if (cmd[0] == '/' && access(cmd, F_OK) != 0)
		return (write_error(prompt, cmd,
				" : No such file or directory\n", 127), NULL);
	if (check_path_in_env(env) == 1)
		join = check_cmd_in_path(env, cmd, &check);
	if (check_path_in_env(env) == 1 && join)
		return (join);
	if (check == 1)
		return (write_error(prompt, cmd, "Permission denied\n", 126), NULL);
	if (access(cmd, F_OK) == 0 && ft_strchr2(cmd, '/') == 1)
		return (write_error(prompt, "Permission denied\n", NULL, 126), NULL);
	return (write_error(prompt, cmd, " : Command not found\n", 127), NULL);
}
