/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:09:35 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/28 14:41:21 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexbuf	*copy_tokens(t_lexbuf **tokens, t_lexbuf *current)
{
	t_lexbuf	*new;

	new = malloc(sizeof(t_lexbuf));
	if (new == NULL)
		return (NULL);
	new->type = current->type;
	new->input = current->input;
	new->next = NULL;
	new->value = ft_strdup(current->value);
	if (!new->value)
		ft_free("malloc error at new_tokens_pexpand", tokens, 1);
	return (new);
}

t_lexbuf	*remove_emptyexpands(t_lexbuf **tokens)
{
	t_lexbuf	*current;
	t_lexbuf	*new_node;
	t_lexbuf	*new_head;

	current = *tokens;
	new_node = NULL;
	new_head = NULL;
	while (current)
	{
		if (current && current->value && current->value[0] != -6)
		{
			new_node = copy_tokens(tokens, current);
			add_back(&new_head, new_node);
		}
		current = current->next;
	}
	return (ft_addprev(new_head));
}

t_lexbuf	*parsing(t_input *input, char **env)
{
	t_lexbuf	*mytokens;
	t_lexbuf	*new_tokens;
	t_lexbuf	*last_tokens;

	mytokens = token_recognition(input->linebuffer, input, 0, env);
	new_tokens = split_expands(&mytokens, input);
	quotes_removal(&new_tokens);
	pos_quotes(&new_tokens);
	last_tokens = remove_emptyexpands(&new_tokens);
	ft_free_list(&mytokens);
	ft_free_list(&new_tokens);
	return (last_tokens);
}

char	*mark_empty_expand(t_lexbuf **tokens)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	if (!str)
		ft_free("ALLOCATION ERROR AT mark_empty_expand", tokens, 1);
	str[0] = -6;
	str[1] = '\0';
	return (str);
}

char	*expand_left_exit(char *value, char *envar, t_lexbuf **tokens,
		t_utils *utils)
{
	char	*tmp;

	reset_iterators(utils);
	tmp = NULL;
	tmp = (char *)malloc(sizeof(char) * (utils->start + ft_strlen(envar) + 1));
	if (tmp == NULL)
		ft_free("Alloc error concatene_envar", tokens, 1);
	utils->i = 0;
	while (utils->i < utils->start)
	{
		tmp[utils->i] = value[utils->i];
		utils->i++;
	}
	while (utils->i < utils->start + (int)ft_strlen(envar) && envar[utils->j])
	{
		tmp[utils->i] = envar[utils->j];
		utils->i++;
		utils->j++;
	}
	tmp[utils->i] = 0;
	return (tmp);
}
