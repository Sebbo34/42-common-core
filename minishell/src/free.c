/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:45:18 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/28 14:36:05 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_lexbuf **tokens)
{
	t_lexbuf	*tmp;

	if (*tokens)
	{
		tmp = *tokens;
		while (*tokens)
		{
			tmp = *tokens;
			*tokens = (*tokens)->next;
			if (tmp->value)
				free(tmp->value);
			free(tmp);
		}
	}
	tokens = NULL;
}

void	ft_free(char *msg, t_lexbuf **tokens, int leave)
{
	if (msg != NULL)
		printf("%s\n", msg);
	if ((*tokens))
	{
		if ((*tokens)->input->linebuffer)
			free((*tokens)->input->linebuffer);
		(*tokens)->input->linebuffer = NULL;
	}
	ft_free_list(tokens);
	tokens = NULL;
	if (leave == 1)
		exit(1);
}

void	parse_error(char *msg, t_lexbuf **tokens, int leave, int exit_code)
{
	if (msg != NULL)
		printf("%s\n", msg);
	if ((*tokens))
	{
		if ((*tokens)->input->linebuffer)
			free((*tokens)->input->linebuffer);
		(*tokens)->input->linebuffer = NULL;
		(*tokens)->input->exit_status = exit_code;
	}
	ft_free_list(tokens);
	tokens = NULL;
	if (leave == 1)
		exit(1);
}

void	ft_free_tab(char **value)
{
	int	i;

	if (value)
	{
		i = 0;
		while (value[i])
		{
			free(value[i]);
			i++;
		}
		free(value);
	}
}

void	ft_free_str(char *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
}
