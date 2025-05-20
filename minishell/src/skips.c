/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skips.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:22:29 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/04/11 13:36:07 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_check(char *value, int *i, int *inquote, char del)
{
	(*inquote)++;
	skip(value, i, del);
	if (value[*i] == del)
	{
		(*i)++;
		(*inquote)++;
	}
}

void	skip_squotes(t_utils *utils, char *src, int len, char *new_str)
{
	utils->i++;
	while (utils->j < len && src[utils->i] != -34)
	{
		new_str[utils->j] = src[utils->i];
		utils->j++;
		utils->i++;
	}
	utils->i++;
}

void	skip_dquotes(t_utils *utils, char *src, int len, char *new_str)
{
	utils->i++;
	while (utils->j < len && src[utils->i] != -39)
	{
		new_str[utils->j] = src[utils->i];
		utils->j++;
		utils->i++;
	}
	utils->i++;
}

void	quote_check(t_lexbuf **tokens)
{
	t_lexbuf	*tmp;
	int			i;
	int			inquote;

	i = 0;
	inquote = 2;
	tmp = *tokens;
	tmp = get_last(tmp);
	while (tmp && tmp->value[i])
	{
		if (tmp->value[i] == '"')
			skip_check(tmp->value, &i, &inquote, '"');
		else if (tmp->value[i] == '\'')
			skip_check(tmp->value, &i, &inquote, '\'');
		else
			i++;
	}
	if (inquote % 2 == 0)
		return ;
	(*tokens)->input->exit_status = 2;
	ft_free("Unclosed Quotes", tokens, 0);
}
