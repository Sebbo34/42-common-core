/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:08:02 by sbo               #+#    #+#             */
/*   Updated: 2024/04/02 12:13:02 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*do_heredoc_expand(char *s, char **env, t_lexbuf **tokens,
		t_utils utils)
{
	char		*envar;
	char		*new_value;
	char		*varname;
	t_lexbuf	*tmp;

	tmp = *tokens;
	envar = NULL;
	varname = get_varname(s, tokens, &utils, 0);
	if (varname && varname[0] == '?')
		new_value = concatene_envar_exit(s, ft_itoa(tmp->input->exit_status),
				tokens, &utils);
	else
	{
		envar = get_envar(s, env, tokens, &utils);
		new_value = concatene_envar(s, envar, tokens, &utils);
	}
	ft_free_str(envar);
	ft_free_str(varname);
	ft_free_str(s);
	s = new_value;
	return (s);
}

char	*expand_heredoc(char *s, t_lexbuf **tokens, char **env)
{
	t_utils	utils;

	init_utils(&utils);
	negate_quotes(tokens);
	while (s)
	{
		utils.start = find_envar(s, 0);
		if (utils.start != -1)
			s = do_heredoc_expand(s, env, tokens, utils);
		else
			break ;
	}
	return (s);
}

int	is_last_in(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;

	tmp = prompt->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INREDIR || tmp->type == HEREDOC)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	add_here_doc(t_lexbuf *tmp, int *tube)
{
	char	*chaine;

	free(tmp->value);
	tmp->value = ft_itoa(tube[0]);
	if (!tmp->value)
		return (free_child(tmp), exit(1));
	chaine = ft_itoa(tube[1]);
	if (!chaine)
		return (free_child(tmp), exit(1));
	tmp->value = ft_strjoin2(tmp->value, " ", chaine, 1);
	if (!tmp->value)
		return (free_child(tmp), free(chaine), exit(1));
	free(chaine);
}
