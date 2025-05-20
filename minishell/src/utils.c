/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:55:20 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/22 15:12:46 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_stack(t_lexbuf *tokens)
{
	int			i;
	t_lexbuf	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		printf("top node Nb %i ----> value : %s  type --->%i \n", i, tmp->value,
			tmp->type);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (tmp)
	{
		printf("top node Nb %i ----> value : %s  type --->%i \n", i, tmp->value,
			tmp->type);
		if (tmp->prev == NULL)
			break ;
		tmp = tmp->prev;
		i++;
	}
}

int	is_space(char c)
{
	if (c == ' ' || c == 9)
		return (1);
	return (0);
}

void	print_tab(char **strs)
{
	int	i;

	if (strs)
	{
		i = 0;
		while (strs[i])
		{
			printf("str%i : %s.\n", i, strs[i]);
			i++;
		}
	}
}

int	ft_strncmpp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (s1 || s2)
	{
		while (s1 && s1[i] && s2 && s2[i] && i < n)
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	strncmp_env(char *s1, char *s2, int n)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s2 && s2[j] != '=')
		j++;
	if (s1 || s2)
	{
		while (s1 && s1[i] && s2 && s2[i] && i < n)
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		if (i != j)
			return (0);
		return (1);
	}
	return (0);
}
