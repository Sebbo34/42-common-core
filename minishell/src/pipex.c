/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:44:45 by sbo               #+#    #+#             */
/*   Updated: 2024/04/11 13:06:06 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cmd(t_lexbuf *prompt)
{
	int	status;

	status = prompt->input->exit_status;
	free_child(prompt);
	exit(status);
}

void	job(t_lexbuf *prompt, int *tube, char **env)
{
	char	**split;
	int		status;

	get_output(prompt, tube);
	if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) != 0)
	{	
		if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) == 1
			|| (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) == 2
				&& have_pipe(prompt) == 1))
			prompt->env = exec_builtins(prompt, prompt->env);
		else if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) == 3
			&& have_pipe(prompt) == 1)
			ft_export_child(prompt);
		status = prompt->input->exit_status;
		free_child(prompt);
		if (status != 0)
			exit (status);
		exit (EXIT_SUCCESS);
	}
	split = ft_join_word(prompt, env);
	if (!split)
		error_cmd(prompt);
	execve(split[0], split, env);
	free_split(split);
	exit(1);
}

void	job_parent(t_lexbuf *prompt, int *tube, int *ind, int fd)
{
	close(tube[1]);
	if (extract_in_lexbuf(prompt, WORD, 1))
	{
		if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) > 1
			&& check_file(prompt) && have_pipe(prompt) == 0)
		{
			if (ft_strcmp(extract_in_lexbuf(prompt, WORD, 1), "exit") == 0)
				close(tube[0]);
			prompt->env = exec_builtins(prompt, prompt->env);
			if (!prompt->env)
				return (free_child(prompt), exit(1));
			init_env_in_lex(prompt, prompt->env);
		}
		if (is_builtins(extract_in_lexbuf(prompt, WORD, 1)) > 1
			&& check_file(prompt) == 0 && have_pipe(prompt) == 0)
			perror("fd");
	}
	if (is_last_cmd(prompt) || !move_by_pipe(prompt))
		close_all_here_doc2(prompt);
	if (fd != 0)
		close(fd);
	*ind = *ind + 1;
	prompt = move_by_pipe(prompt);
	pipex(prompt, tube[0], *ind);
	close(tube[0]);
}

void	job_child(t_lexbuf *prompt, int *tube, int fd, int ind)
{
	if (check_file(prompt))
	{
		if (extract_in_lexbuf(prompt, WORD, 1))
		{
			get_infile(prompt, tube, fd, ind);
			job(prompt, tube, prompt->env);
		}
		else
			exit_error_no_cmd(prompt, tube, fd);
	}
	else if ((have_pipe(prompt) == 1
			|| is_builtins(extract_in_lexbuf(prompt, WORD, 1)) < 2))
		exit_error_file(prompt, tube, fd);
}

void	pipex(t_lexbuf *prompt, int fd, int ind)
{
	pid_t	pid;
	int		tube[2];

	if (prompt)
	{
		if (pipe(tube))
			return (perror("pipe"), free_child(prompt), exit(1));
		pid = fork();
		if (pid == -1)
			return (perror("fork"), free_child(prompt), exit(1));
		else if (pid == 0)
			job_child(prompt, tube, fd, ind);
		else
		{
			job_parent(prompt, tube, &ind, fd);
			get_exit_status(prompt, pid, 0);
		}
	}
}
