/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:44:06 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/22 18:04:16 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_removal(t_lexbuf **tokens)
{
	t_lexbuf	*current;
	char		*tmp;

	current = *tokens;
	while (current)
	{
		if (current->value && current->value[0] != '\0')
		{
			tmp = ft_strdup(current->value);
			free(current->value);
			current->value = remove_quotes(tmp, tokens);
			free(tmp);
		}
		current = current->next;
	}
	if (!tokens)
		ft_free("alloc error quotes removal", tokens, 1);
}

char	*ft_join_quotes(char *src, char *new_str, int len)
{
	t_utils	utils;

	init_utils(&utils);
	while (utils.j < len)
	{
		if (src[utils.i] == -34)
			skip_squotes(&utils, src, len, new_str);
		else if (src[utils.i] == -39)
			skip_dquotes(&utils, src, len, new_str);
		else
		{
			new_str[utils.j] = src[utils.i];
			utils.j++;
			utils.i++;
		}
	}
	new_str[utils.j] = 0;
	return (new_str);
}

char	*remove_quotes(char *src, t_lexbuf **tokens)
{
	int		i;
	int		del;
	int		j;
	char	*new_str;

	j = 0;
	i = 0;
	del = 0;
	new_str = NULL;
	count_quotesrm(src, &i, &del);
	if (del == 0)
	{
		new_str = ft_strdup(src);
		return (new_str);
	}
	new_str = (char *)malloc(sizeof(char) * (i + 1 - del));
	if (new_str == NULL)
		ft_free("Malloc Error at remove_quotes", tokens, 1);
	new_str = ft_join_quotes(src, new_str, i - del);
	return (new_str);
}

void	count_quotesrm(char *src, int *i, int *del)
{
	while (src[*i])
	{
		if (src[*i] == -34)
		{
			(*del)++;
			(*i)++;
			while (src[*i] && src[*i] != -34)
				(*i)++;
			(*del)++;
			(*i)++;
		}
		else if (src[*i] == -39)
		{
			(*del)++;
			(*i)++;
			while (src[*i] && src[*i] != -39)
				(*i)++;
			(*del)++;
			(*i)++;
		}
		else
			(*i)++;
	}
}

int	quote_break(t_lexbuf **tokens, char *s, int *i)
{
	if (s[*i] == '"')
	{
		if ((*tokens)->type != WORD)
			return (1);
		skip(s, i, '"');
	}
	if (s[*i] == 39)
	{
		if ((*tokens)->type != WORD)
			return (1);
		skip(s, i, '\'');
	}
	return (0);
}
