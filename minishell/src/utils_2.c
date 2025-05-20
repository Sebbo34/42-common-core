/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:30:18 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/26 13:14:49 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip(char *s, int *i, char del)
{
	(*i)++;
	while (s[*i] && s[*i] != del)
		(*i)++;
}

t_lexbuf	*get_last(t_lexbuf *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	add_back(t_lexbuf **lst, t_lexbuf *new)
{
	t_lexbuf	*tmp;

	if (lst)
	{
		if (*lst)
		{
			tmp = get_last(*lst);
			tmp->next = new;
		}
		else
			*lst = new;
	}
}

void	negate_quotes(t_lexbuf **tokens)
{
	int			i;
	t_lexbuf	*tmp;

	tmp = (*tokens);
	while (tmp)
	{
		i = 0;
		while (tmp->value && tmp->value[i])
		{
			if (tmp->value[i] == '\'')
				tmp->value[i] = -39;
			if (tmp->value[i] == '"')
				tmp->value[i] = -34;
			i++;
		}
		tmp = tmp->next;
	}
}

void	pos_quotes(t_lexbuf **tokens)
{
	int			i;
	t_lexbuf	*tmp;

	tmp = (*tokens);
	while (tmp)
	{
		i = 0;
		while (tmp->value && tmp->value[i])
		{
			if (tmp->value[i] == -39)
				tmp->value[i] = '\'';
			if (tmp->value[i] == -34)
				tmp->value[i] = '"';
			i++;
		}
		tmp = tmp->next;
	}
}
