/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:24:06 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/04/02 10:04:10 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexbuf	*new_tokens(char *s, int *i, t_input *input)
{
	t_lexbuf	*new;

	new = malloc(sizeof(t_lexbuf));
	if (new == NULL)
		return (NULL);
	new->value = NULL;
	new->input = input;
	new->type = token_type(s, i);
	new->next = NULL;
	return (new);
}

int	token_check(t_lexbuf *tmp, t_lexbuf **tokens)
{
	if (tokens && (*tokens)->type == PIPE)
		return (0);
	else if (tmp->type == INREDIR)
	{
		if (precise_token(&tmp, tokens, INREDIR) == 0)
			return (0);
	}
	else if (tmp->type == OUTREDIR)
	{
		if (precise_token(&tmp, tokens, OUTREDIR) == 0)
			return (0);
	}
	else if (tmp->type == HEREDOC)
	{
		if (precise_token(&tmp, tokens, HEREDOC) == 0)
			return (0);
	}
	else if (tmp->type == APPOUTREDIR)
	{
		if (precise_token(&tmp, tokens, APPOUTREDIR) == 0)
			return (0);
	}
	return (1);
}

int	token_context(t_lexbuf **tokens)
{
	t_lexbuf	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (token_check(tmp, tokens) == 0)
			return (0);
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

int	precise_token(t_lexbuf **tmp, t_lexbuf **tokens, int type)
{
	t_lexbuf	*current;

	current = *tmp;
	if (tmp)
	{
		if (!(*tmp)->next)
			return (0);
		else if ((*tmp)->next->type != WORD)
			return (0);
		else
		{
			(*tmp)->type = type;
			free((*tmp)->value);
			(*tmp)->value = NULL;
			(*tmp)->value = ft_strdup((*tmp)->next->value);
			if (!(*tmp)->value)
				ft_free("Alloc Error at ft_inredir", tokens, 1);
			current = current->next;
			(*tmp)->next = (*tmp)->next->next;
			free(current->value);
			free(current);
			return (1);
		}
	}
	return (0);
}

t_lexbuf	*ft_addprev(t_lexbuf *token)
{
	t_lexbuf	*tmp;
	t_lexbuf	*tmp2;

	if (token)
	{
		token->prev = NULL;
		tmp = token;
		tmp2 = token->next;
		while (tmp && tmp2)
		{
			tmp2->prev = tmp;
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
	}
	return (token);
}
