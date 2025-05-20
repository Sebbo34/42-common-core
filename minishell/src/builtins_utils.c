/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:10:26 by sbo               #+#    #+#             */
/*   Updated: 2024/04/11 13:20:09 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(char	*word)
{
	if (ft_strcmp(word, "echo") == 0)
		return (1);
	else if (ft_strcmp(word, "cd") == 0)
		return (2);
	else if (ft_strcmp(word, "pwd") == 0)
		return (1);
	else if (ft_strcmp(word, "export") == 0)
		return (3);
	else if (ft_strcmp(word, "unset") == 0)
		return (3);
	else if (ft_strcmp(word, "env") == 0)
		return (1);
	else if (ft_strcmp(word, "exit") == 0)
		return (2);
	return (0);
}

char	**exec_builtins(t_lexbuf *prompt, char **env)
{
	(void)env;
	if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) == 1)
	{
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "echo") == 0)
			ft_echo(prompt);
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "pwd") == 0)
		{
			prompt->input->exit_status = 0;
			ft_pwd();
		}
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "env") == 0)
			ft_env(prompt);
	}
	else if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) > 1)
	{
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "export") == 0)
			prompt->env = ft_export(prompt);
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "unset") == 0)
			prompt->env = ft_unset(prompt, prompt->env);
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "cd") == 0)
			prompt->env = ft_cd(prompt, prompt->env);
		if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "exit") == 0)
			ft_exit(prompt);
	}
	return (prompt->env);
}
