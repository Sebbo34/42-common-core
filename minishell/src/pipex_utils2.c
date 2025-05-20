/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:43:53 by sbo               #+#    #+#             */
/*   Updated: 2024/04/08 12:05:22 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_no_cmd(t_lexbuf *prompt, int *tube, int fd)
{
	int	status;

	close(tube[0]);
	close(tube[1]);
	if (fd != 0)
		close (fd);
	close_all_here_doc2(prompt);
	status = prompt->input->exit_status;
	free_child(prompt);
	exit(status);
}

void	exit_error_file(t_lexbuf *prompt, int *tube, int fd)
{
	int	status;

	perror("fd");
	if (fd != 0)
		close (fd);
	close(tube[0]);
	close(tube[1]);
	close_all_here_doc2(prompt);
	status = prompt->input->exit_status;
	free_child(prompt);
	exit(status);
}

int	get_output(t_lexbuf *prompt, int *tube)
{
	int	fd2;
	int	output;

	output = get_out(prompt);
	if (output == -1)
	{
		free_child(prompt);
		exit(1);
	}
	if (output != -2)
	{
		fd2 = output;
		dup2(fd2, 1);
		close(fd2);
	}
	else if (output == -2 && is_last_cmd(prompt) == 0)
		dup2(tube[1], 1);
	close(tube[1]);
	return (0);
}

int	is_here_doc(t_lexbuf *prompt)
{
	t_lexbuf	*tmp;

	tmp = prompt;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INREDIR || tmp->type == HEREDOC)
		{
			if (tmp->type == HEREDOC && is_last_in(tmp) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	get_infile(t_lexbuf *prompt, int *tube, int fd, int ind)
{
	int	input;

	input = get_in(prompt);
	if (input == -1)
		return (perror("fd"), -1);
	close(tube[0]);
	if ((input == -2 && ind == 0))
	{
	}
	else
	{
		if (input != -2)
		{
			if (fd != 0)
				close (fd);
			fd = input;
		}
		dup2(fd, 0);
		close_all_here_doc2(prompt);
		if (is_here_doc(prompt) == 0)
			close(fd);
	}
	return (0);
}
