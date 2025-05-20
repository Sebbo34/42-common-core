/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:30:32 by sbo               #+#    #+#             */
/*   Updated: 2024/04/08 18:33:45 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cpy_env(char **env)
{
	int		i;
	char	**cpy;

	i = 0;
	while (env[i])
		i++;
	cpy = malloc((i + 1) * sizeof(char *));
	if (!cpy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		cpy[i] = ft_strdup(env[i]);
		if (!cpy[i])
			return (free_split(cpy), NULL);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

int	check_env(char *arg, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strcmp_equal(env[i], arg) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
}

void	ft_env(t_lexbuf *prompt)
{
	int	i;

	i = 0;
	while (prompt->env[i])
	{
		printf("%s\n", prompt->env[i]);
		i++;
	}
}

void	init_env_in_lex(t_lexbuf *prompt, char **env)
{
	t_lexbuf	*tmp;

	tmp = prompt;
	while (tmp)
	{
		tmp->env = env;
		tmp = tmp->next;
	}
}
