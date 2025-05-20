/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:29:17 by sbo               #+#    #+#             */
/*   Updated: 2024/04/11 13:07:52 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_is_in_env(char *var_env, char **args, int *tab_nbr)
{
	int	j;

	j = 1;
	while (args[j])
	{
		if (strcmp_equal(args[j], var_env) == 0 && tab_nbr[j] == 2)
			return (j);
		j++;
	}
	return (0);
}

int	ft_strcmp2(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '=' && str2[i] != '=')
	{
		if (str1[i] < str2[i])
			return (1);
		else if (str1[i] > str2[i])
			return (0);
		i++;
	}
	if (str1[i] == '=' && str2[i] != '=')
		return (1);
	return (0);
}

int	nbr_inf(char **env, char *arg)
{
	int	i;
	int	inf;

	inf = 0;
	i = 0;
	while (env[i])
	{
		if (ft_strcmp2(env[i], arg) == 1)
			inf++;
		i++;
	}
	return (inf);
}

int	ft_export_parse_child(char **args, int *tab_nbr)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (args[i])
	{
		if (tab_nbr[i] == -2)
		{
			write (2, "minishell: export: '", 21);
			write (2, args[i], ft_strlen(args[i]));
			write (2, "' not a valid identifier\n", 26);
			error = 1;
			break ;
		}
		i++;
	}
	return (error);
}

void	ft_export_child(t_lexbuf *prompt)
{
	int		*tab_nbr;
	char	**args;

	if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "unset") == 0)
	{
		prompt->input->exit_status = 0;
		return ;
	}
	args = ft_join_word2(prompt);
	if (!args)
		return ;
	if (!args[1])
		return (free(args), ft_export_noarg(prompt->env));
	tab_nbr = parse_export(args, prompt->env);
	if (!tab_nbr)
		return (free_split(args));
	prompt->input->exit_status = ft_export_parse_child(args, tab_nbr);
	return (free(tab_nbr), free(args));
}
