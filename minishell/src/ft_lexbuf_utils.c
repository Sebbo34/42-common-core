/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexbuf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:15:11 by sbo               #+#    #+#             */
/*   Updated: 2024/03/30 19:07:43 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_cmd(t_lexbuf *prompt)
{
	int			len;
	t_lexbuf	*tmp;

	len = 0;
	tmp = prompt;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

int	is_last_cmd(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;

	tmp = prompt;
	while (tmp && tmp->type != PIPE)
	{
		tmp = tmp->next;
	}
	if (tmp)
		return (0);
	return (1);
}

t_lexbuf	*move_by_pipe(t_lexbuf *tokens)
{
	t_lexbuf	*tmp;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		tmp = tmp->next;
	}
	if (tmp && tmp->type == PIPE && tmp->next)
		return (tmp->next);
	if (tmp && !tmp->next && tmp->type == PIPE)
		return (NULL);
	return (tmp);
}

int	number_of_args(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;
	int			arg;

	tmp = prompt;
	arg = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			arg++;
		tmp = tmp->next;
	}
	return (arg - 1);
}

char	*extract_in_lexbuf(t_lexbuf *prompt, int type, int ind)
{
	t_lexbuf	*tmp;
	int			i;

	i = 0;
	tmp = prompt;
	if (type == PIPE && tmp->prev)
		return (tmp->prev->value);
	while (tmp->prev && tmp->prev->type != PIPE)
		tmp = tmp->prev;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == type)
			i++;
		if (i == ind)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
