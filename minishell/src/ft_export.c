/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:27:04 by sbo               #+#    #+#             */
/*   Updated: 2024/04/11 13:23:19 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_noarg(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			if (nbr_inf(env, env[j]) == i)
				break ;
			j++;
		}
		printf("declare -x %s\n", env[j]);
		i++;
	}
}

char	**creat_new_env(char **env, char **args, int *tab_nbr)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	new_env = malloc((tab_nbr[0] + 1) * sizeof(char *));
	if (!new_env)
		return (free(args), free(tab_nbr), NULL);
	while (env[i])
	{
		j = args_is_in_env(env[i], args, tab_nbr);
		if (j != 0)
			new_env[i] = ft_strdup(args[j]);
		else
			new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (free(args), free(tab_nbr), free_env(new_env), NULL);
		i++;
	}
	return (new_env);
}

int	add_new_args(char **new_env, char **args, int *tab_nbr, int len_env)
{
	int	j;
	int	error;

	j = 1;
	error = 0;
	while (args[j])
	{
		if (tab_nbr[j] == 1)
		{
			new_env[len_env] = ft_strdup(args[j]);
			if (!new_env[len_env])
				return (free_split(args), free(tab_nbr), free_env(new_env), -1);
			len_env++;
		}
		else if (tab_nbr[j] == -2)
		{
			error = 1;
			write (2, "minishell: export: '", 21);
			write (2, args[j], ft_strlen(args[j]));
			write (2, "' not a valid identifier\n", 26);
		}
		j++;
	}
	new_env[len_env] = NULL;
	return (error);
}

char	**ft_export(t_lexbuf *prompt)
{
	char	**new_env;
	int		*tab_nbr;
	char	**args;
	int		error;

	error = 0;
	args = ft_join_word2(prompt);
	if (!args)
		return (NULL);
	if (!args[1])
		return (free(args), ft_export_noarg(prompt->env), prompt->env);
	tab_nbr = parse_export(args, prompt->env);
	if (!tab_nbr)
		return (free_split(args), NULL);
	new_env = creat_new_env(prompt->env, args, tab_nbr);
	if (!new_env)
		return (NULL);
	error = add_new_args(new_env, args, tab_nbr, ft_strlen_tab(prompt->env));
	if (error == -1)
		return (NULL);
	prompt->input->exit_status = error;
	return (free(tab_nbr), free(args), free_env(prompt->env), new_env);
}
