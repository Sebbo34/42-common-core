/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:18:26 by sbo               #+#    #+#             */
/*   Updated: 2024/03/30 19:04:09 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_home(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strcmp_equal(env[i], "HOME=") == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_home(char **env)
{
	char	*home;
	int		i;

	i = 0;
	while (env[i])
	{
		if (strcmp_equal(env[i], "HOME=") == 0)
		{
			home = ft_strdup(&env[i][5]);
			if (!home)
				return (NULL);
			return (home);
		}
		i++;
	}
	return (NULL);
}

char	**cd_noarg(t_lexbuf *prompt, char **env)
{
	char	*pwd;
	char	*home;

	home = get_home(env);
	if (!home && check_home(env) == 0)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return (env);
	}
	else if (!home && check_home(env) == 1)
		return (NULL);
	if (chdir(home) == -1)
		return (perror("minishell : cd: "), free(home), env);
	pwd = ft_strjoin("PWD=", home);
	if (!pwd)
		return (NULL);
	env = ft_export_cd(env, pwd);
	if (!env)
		return (free(pwd), free(home), NULL);
	free(home);
	prompt->input->exit_status = 0;
	return (env);
}

char	**cd_path(t_lexbuf *prompt, char **env, char *arg)
{
	char	*pwd;

	pwd = NULL;
	if (chdir(arg) == -1)
		return (perror("minishell : cd: "),
			change_exit_status(&prompt->input->exit_status, 1), env);
	pwd = getcwd(pwd, 0);
	if (!pwd && errno == ENOENT)
	{
		write (2, "cd: error retrieving current directory: ", 41);
		write (2, " getcwd: cannot access ", 24);
		write (2, "parent directories: No such file or directory\n", 47);
		return (env);
	}
	else if (!pwd)
		return (NULL);
	pwd = ft_strjoin2("PWD=", pwd, NULL, 2);
	if (!pwd)
		return (NULL);
	env = ft_export_cd(env, pwd);
	prompt->input->exit_status = 0;
	return (env);
}

char	**ft_cd(t_lexbuf *prompt, char **env)
{
	char	*arg;

	if (number_of_args(prompt) >= 2)
	{
		write(2, "cd: too many arguments\n", 24);
		prompt->input->exit_status = 1;
		return (env);
	}
	arg = extract_in_lexbuf(prompt, WORD, 2);
	if (number_of_args(prompt) == 0)
		return (cd_noarg(prompt, env));
	else
		return (cd_path(prompt, env, arg));
}
