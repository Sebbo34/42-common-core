/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:51:08 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/22 16:12:44 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexbuf	*split_expands(t_lexbuf **old_list_head, t_input *input)
{
	t_lexbuf	*new_list_head;
	t_lexbuf	*current_old;
	t_lexbuf	*old_next;
	t_lexbuf	*new_node;
	char		**new_strs;

	current_old = *old_list_head;
	new_list_head = NULL;
	new_node = NULL;
	while (current_old)
	{
		old_next = current_old->next;
		if (current_old->value && current_old->value[0] != '\0')
		{
			new_strs = ft_split(current_old->value, -32);
			new_node = create_tmp_list(new_strs, current_old, old_list_head,
					input);
			ft_free_tab(new_strs);
		}
		else
			new_node = copy_tokens(old_list_head, current_old);
		add_back(&new_list_head, new_node);
		current_old = old_next;
	}
	return (ft_addprev(new_list_head));
}

t_lexbuf	*new_tokens_pexpand(char *s, int type, t_lexbuf **tokens,
		t_input *input)
{
	t_lexbuf	*new;

	new = malloc(sizeof(t_lexbuf));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->input = input;
	new->next = NULL;
	new->value = ft_strdup(s);
	if (!new->value)
		ft_free("malloc error at new_tokens_pexpand", tokens, 1);
	return (new);
}

t_lexbuf	*create_tmp_list(char **new_strs, t_lexbuf *tmp, t_lexbuf **tokens,
		t_input *input)
{
	int			i;
	t_lexbuf	*newtokens;
	t_lexbuf	*tmpp;

	i = 0;
	newtokens = NULL;
	tmpp = NULL;
	while (new_strs[i])
	{
		tmpp = new_tokens_pexpand(new_strs[i], tmp->type, tokens, input);
		if (tmpp == NULL)
			ft_free("Alloc Failure in new_tokens", tokens, 1);
		add_back(&newtokens, tmpp);
		i++;
	}
	return (newtokens);
}
