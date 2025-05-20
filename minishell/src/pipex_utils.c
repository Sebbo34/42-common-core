/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:54:48 by sbo               #+#    #+#             */
/*   Updated: 2024/04/11 13:29:59 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_arg(t_lexbuf *tmp, char **env, int *len)
{
	if (*len == 0)
		return (check_cmd(tmp, env, tmp->value));
	else
		return (tmp->value);
}

char	**ft_join_word(t_lexbuf *prompt, char **env)
{
	t_lexbuf	*tmp;
	char		**join_word;
	int			len;

	len = get_len_cmd(prompt);
	tmp = prompt;
	join_word = malloc((len + 1) * sizeof(char *));
	if (!join_word)
		return (NULL);
	len = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
		{
			join_word[len] = fill_arg(tmp, env, &len);
			if (!join_word[len] && len == 0)
				return (free(join_word), NULL);
			len++;
		}
		tmp = tmp->next;
	}
	join_word[len] = NULL;
	return (join_word);
}

void	free_child(t_lexbuf *prompt)
{
	while (prompt->prev)
		prompt = prompt->prev;
	free_env(prompt->env);
	ft_free(NULL, &prompt, 0);
}

void	get_exit_status(t_lexbuf *prompt, pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (is_last_cmd(prompt) == 1 && (have_pipe(prompt) == 1
			|| is_builtins(extract_in_lexbuf(prompt, WORD, 1)) < 2))
	{
		if (WIFSIGNALED(status))
		{
			prompt->input->exit_status = status;
			if (g_signal == SIGINT)
			{
				printf("\n");
				prompt->input->exit_status = 130;
			}
			if (g_signal == SIGQUIT)
			{
				printf(" quit (core dumped)\n");
				prompt->input->exit_status = 131;
			}
		}
		else
			prompt->input->exit_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status) && status == 139)
		write(2, "segmentation fault (core dumped)\n", 34);
}

int	have_pipe(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;

	tmp = prompt;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
