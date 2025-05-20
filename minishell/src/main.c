/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/04/11 12:37:55 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

int	ft_readline(t_lexbuf **tokens, t_input *input, char **my_env, int *check)
{
	if (*check == 0)
		signal(SIGINT, signal_readline);
	else if (*check == 1)
		signal(SIGINT, signal_readline2);
	*check = 0;
	signal(SIGQUIT, SIG_IGN);
	init_struct(input);
	g_signal = 0;
	input->linebuffer = readline("minishell >");
	if (g_signal == SIGINT)
		input->exit_status = 130;
	if (!input->linebuffer)
		return (0);
	g_signal = 0;
	add_history(input->linebuffer);
	input->nread = ft_strlen(input->linebuffer);
	*tokens = parsing(input, my_env);
	if (*tokens)
		init_env_in_lex(*tokens, my_env);
	return (1);
}

void	open_here_doc_main(t_lexbuf *tokens, int *check, t_input *input)
{
	int	std;

	std = dup(0);
	signal(SIGINT, signal_here_doc);
	open_here_doc(&tokens);
	if (g_signal == SIGINT)
	{
		*check = 1;
		dup2(std, STDIN_FILENO);
		input->exit_status = 130;
	}
	close(std);
}

char	**start_exec(t_lexbuf *tokens, t_input *input, char **my_env)
{
	signal(SIGQUIT, signal_pipex);
	signal(SIGINT, signal_pipex);
	if (tokens && g_signal != SIGINT
		&& ((extract_in_lexbuf(tokens, WORD, 1)) || have_pipe(tokens) == 1))
		pipex(tokens, 0, 0);
	else if (g_signal != SIGINT && tokens && check_file(tokens) == 0)
		perror("fd");
	else if (input->linebuffer && input->linebuffer[0] != 0 && g_signal == 0)
		input->exit_status = 0;
	if (tokens)
		return (tokens->env);
	else
		return (my_env);
}

int	main(int ac, char **av, char **env)
{
	t_input		input;
	t_lexbuf	*tokens;
	char		**my_env;
	int			check;

	(void)av;
	if (ac != 1)
		exit(1);
	tokens = NULL;
	input.exit_status = 0;
	my_env = cpy_env(env);
	check = 0;
	while (1)
	{
		if (ft_readline(&tokens, &input, my_env, &check) == 0)
			break ;
		open_here_doc_main(tokens, &check, &input);
		if (g_signal != SIGINT)
			my_env = start_exec(tokens, &input, my_env);
		ft_free(NULL, &tokens, 0);
		if (input.linebuffer)
			free(input.linebuffer);
	}
	write (2, "exit\n", 6);
	return (free_env(my_env), 0);
}
