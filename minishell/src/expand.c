/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:58:02 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/26 13:14:05 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_expansion(t_lexbuf *tmp, t_lexbuf **tokens, char **env,
		t_utils *utils)
{
	char	*envar;
	char	*new_value;
	char	*varname;

	init_utils(utils);
	envar = NULL;
	varname = get_varname(tmp->value, tokens, utils, 0);
	if (varname && varname[0] == '?')
		new_value = concatene_envar_exit(tmp->value,
				ft_itoa(tmp->input->exit_status), tokens, utils);
	else
	{
		envar = get_envar(tmp->value, env, tokens, utils);
		new_value = concatene_envar(tmp->value, envar, tokens, utils);
	}
	ft_free_str(envar);
	ft_free_str(varname);
	ft_free_str(tmp->value);
	if (new_value && new_value[0] == '\0')
	{
		free(new_value);
		new_value = mark_empty_expand(tokens);
	}
	tmp->value = new_value;
}

void	expand(t_lexbuf **tokens, char **env)
{
	t_lexbuf	*tmp;
	t_utils		utils;

	init_utils(&utils);
	tmp = (*tokens);
	negate_quotes(tokens);
	while (tmp)
	{
		while (tmp->value && tmp->type != HEREDOC)
		{
			utils.start = find_envar(tmp->value, 0);
			if (utils.start != -1)
				do_expansion(tmp, tokens, env, &utils);
			else
				break ;
		}
		tmp = tmp->next;
	}
}

char	*get_envar(char *value, char **env, t_lexbuf **tokens, t_utils *utils)
{
	char	*varname;
	char	*varcontent;

	varcontent = NULL;
	varname = get_varname(value, tokens, utils, 0);
	if (!varname)
		return (NULL);
	while (env[utils->i])
	{
		if (strncmp_env(varname, env[utils->i], utils->varname_len) == 1)
		{
			while (env[utils->i][utils->j] && env[utils->i][utils->j] != '=')
				utils->j++;
			utils->varcontent_start = utils->j + 1;
			varcontent = get_varcontent(env[utils->i], tokens, utils, value);
			ft_free_str(varname);
			if (varcontent == NULL)
				return (NULL);
			return (varcontent);
		}
		utils->i++;
	}
	ft_free_str(varname);
	return (varcontent);
}

char	*expand_left(char *value, char *envar, t_lexbuf **tokens,
		t_utils *utils)
{
	char	*tmp;

	reset_iterators(utils);
	tmp = NULL;
	while (value[utils->i] && (ft_isalnum(value[utils->i])
			|| value[utils->i] == '_'))
		utils->i++;
	tmp = (char *)malloc(sizeof(char) * (utils->start + utils->varcontent_len
				+ 1));
	if (tmp == NULL)
		ft_free("Alloc error concatene_envar", tokens, 1);
	utils->i = 0;
	while (utils->i < utils->start)
	{
		tmp[utils->i] = value[utils->i];
		utils->i++;
	}
	while (utils->i < utils->start + utils->varcontent_len && envar[utils->j])
	{
		tmp[utils->i] = envar[utils->j];
		utils->i++;
		utils->j++;
	}
	tmp[utils->i] = 0;
	return (tmp);
}

char	*concatene_envar(char *tokenvalue, char *envar, t_lexbuf **tokens,
		t_utils *utils)
{
	char	*tmp;
	char	*new_value;
	int		i;
	char	*tmp2;

	tmp = NULL;
	new_value = NULL;
	i = find_envar(tokenvalue, 0);
	tmp = expand_left(tokenvalue, envar, tokens, utils);
	if (tokenvalue[i] && tokenvalue[i] == '?')
		i++;
	else
		while (tokenvalue[i] && (ft_isalnum(tokenvalue[i])
				|| tokenvalue[i] == '_'))
			i++;
	tmp2 = &tokenvalue[i];
	new_value = ft_strjoin(tmp, tmp2);
	ft_free_str(tmp);
	return (new_value);
}
