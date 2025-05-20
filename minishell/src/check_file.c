/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:31:07 by sbo               #+#    #+#             */
/*   Updated: 2024/04/11 12:35:39 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_in(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;
	int			fd;
	char		*in;

	fd = -2;
	tmp = prompt;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INREDIR)
		{
			fd = -1;
			in = tmp->value;
		}
		else if (tmp->type == HEREDOC && is_last_in(tmp))
			fd = ft_atoi(tmp->value);
		tmp = tmp->next;
	}
	if (fd == -1)
		fd = open(in, O_RDONLY);
	return (fd);
}

int	get_out(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;
	int			fd;
	char		*out;

	tmp = prompt;
	fd = -2;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUTREDIR)
		{
			fd = -4;
			out = tmp->value;
		}
		else if (tmp->type == APPOUTREDIR)
		{
			fd = -3;
			out = tmp->value;
		}
		tmp = tmp->next;
	}
	if (fd == -4)
		fd = open(out, O_WRONLY | O_TRUNC);
	else if (fd == -3)
		fd = open(out, O_WRONLY | O_APPEND);
	return (fd);
}

int	check_outfile(t_lexbuf *tmp)
{
	int	fd;

	fd = 0;
	if (tmp->type == OUTREDIR && access(tmp->value, F_OK) == 0)
		fd = open(tmp->value, O_WRONLY | O_TRUNC);
	else if (tmp->type == APPOUTREDIR && access(tmp->value, F_OK) == 0)
		fd = open(tmp->value, O_WRONLY | O_APPEND);
	else
		fd = open(tmp->value, O_CREAT, 0644);
	if (fd == -1)
	{
		tmp->input->exit_status = 1;
		return (0);
	}
	close (fd);
	return (1);
}

int	check_file(t_lexbuf *tokens)
{
	t_lexbuf	*tmp;
	int			fd;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OUTREDIR || tmp->type == APPOUTREDIR)
		{
			if (check_outfile(tmp) == 0)
				return (0);
		}
		else if (tmp->type == INREDIR)
		{
			fd = open(tmp->value, O_RDONLY);
			if (fd == -1)
			{
				tmp->input->exit_status = 1;
				return (0);
			}
			close (fd);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	close_all_here_doc2(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;
	char		**split;

	tmp = prompt;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == HEREDOC && is_last_in(tmp) == 1
			&& extract_in_lexbuf(tmp, WORD, 1))
		{
			split = ft_split(tmp->value, ' ');
			if (!split)
				return (free_child(prompt), exit(1), 0);
			if (split[1])
				close (ft_atoi(split[1]));
			if (split[0] && extract_in_lexbuf(tmp, WORD, 1))
				close (ft_atoi(split[0]));
			free_split(split);
		}
		tmp = tmp->next;
	}
	return (1);
}
