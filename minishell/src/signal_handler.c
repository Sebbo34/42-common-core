/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:50:02 by sbo               #+#    #+#             */
/*   Updated: 2024/04/02 17:29:02 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_readline(int signum)
{
	if (signum == SIGINT)
		g_signal = SIGINT;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_readline2(int signum)
{
	if (signum == SIGINT)
		g_signal = SIGINT;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_here_doc(int signum)
{
	if (signum == SIGINT)
		g_signal = SIGINT;
	close (STDIN_FILENO);
	printf("\n");
}

void	signal_pipex(int signum)
{
	if (signum == SIGQUIT)
	{
		g_signal = SIGQUIT;
	}
	else
	{
		g_signal = SIGINT;
	}
}
