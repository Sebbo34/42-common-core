/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:11:38 by sbo               #+#    #+#             */
/*   Updated: 2024/04/11 12:37:38 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_doc(char *limiter, int *tube, char **env, t_lexbuf **tokens)
{
	char	*chaine;

	while (1)
	{
		chaine = readline(" >");
		if (!chaine && g_signal != SIGINT)
		{
			write(2, "here-document delimited by EOF wanted ", 38);
			write_error(*tokens, limiter, "\n", -1);
			break ;
		}
		if (g_signal == SIGINT)
			break ;
		if (ft_strcmp(chaine, limiter) == 0)
		{
			free(chaine);
			break ;
		}
		chaine = expand_heredoc(chaine, tokens, env);
		write(tube[1], chaine, ft_strlen(chaine));
		write(tube[1], "\n", 1);
		free(chaine);
	}
	return (0);
}

int	close_all_here_doc(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;
	char		**split;

	if (g_signal != SIGINT)
		return (0);
	tmp = prompt;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp && tmp != prompt)
	{
		if (tmp->type == HEREDOC && is_last_in(tmp) == 1
			&& extract_in_lexbuf(tmp, WORD, 1))
		{
			split = ft_split(tmp->value, ' ');
			if (!split)
				return (free_child(prompt), exit(1), 0);
			close (ft_atoi(split[1]));
			close (ft_atoi(split[0]));
			free_split(split);
		}
		if (tmp == prompt)
			break ;
		tmp = tmp->next;
	}
	return (1);
}

void	creat_here_doc(t_lexbuf **prompt, int *tube, int *i, t_lexbuf *tmp)
{
	if (pipe(tube))
		return (perror("pipe"), free_child(tmp), exit(1));
	if (ft_here_doc(tmp->value, tube, (*prompt)->env, prompt) == -1)
		return (free_child(*prompt), exit(1));
	if (is_last_in(tmp) == 1 && extract_in_lexbuf(tmp, WORD, 1))
		add_here_doc(tmp, tube);
	*i = *i + 1;
}

void	close_here_doc( t_lexbuf *tmp, int *tube, int *i)
{
	if ((is_last_in(tmp) == 0 || !extract_in_lexbuf(tmp, WORD, 1)))
	{
		close(tube[0]);
		close(tube[1]);
		*i = *i + 1;
	}
	if (is_last_in(tmp) == 1 && extract_in_lexbuf(tmp, WORD, 1))
		*i = *i + 1;
}

void	open_here_doc(t_lexbuf **prompt)
{
	t_lexbuf	*tmp;
	t_lexbuf	*tmp2;
	int			i;
	int			tube[1024][2];

	i = 0;
	tmp = *prompt;
	while (tmp)
	{
		if (close_all_here_doc(tmp))
			break ;
		if (tmp->type == HEREDOC)
			creat_here_doc(prompt, tube[i], &i, tmp);
		tmp = tmp->next;
	}
	i = 0;
	tmp2 = tmp;
	tmp = *prompt;
	while (tmp != tmp2)
	{
		if (tmp->type == HEREDOC)
			close_here_doc(tmp, tube[i], &i);
		tmp = tmp->next;
	}
}
