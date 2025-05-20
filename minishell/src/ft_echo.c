/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:44:27 by sbo               #+#    #+#             */
/*   Updated: 2024/04/11 12:36:14 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_no_newline(char *arg)
{
	int	i;

	i = 1;
	if (ft_strlen(arg) < 2)
		return (0);
	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)

{
	int	cpt;

	cpt = 0;
	while ((s1[cpt] == s2[cpt]) && s1[cpt] && s2[cpt])
	{
		cpt++;
	}
	if ((unsigned char)s1[cpt] > (unsigned char)s2[cpt])
		return (1);
	else if ((unsigned char)s1[cpt] < (unsigned char)s2[cpt])
		return (-1);
	else
		return (0);
}

void	print_arg(char **args, int i)
{
	while (args[i])
	{
		if (is_no_newline(args[1]) == 1 && !args[i + 1])
			printf("%s", args[i]);
		else if (is_no_newline(args[i]) == 0 && !args[i + 1])
			printf("%s\n", args[i]);
		if ((is_no_newline(args[i]) == 0 || i != 1) && args[i + 1])
			printf("%s ", args[i]);
		i++;
	}
}

void	ft_echo(t_lexbuf *prompt)
{
	int		i;
	char	**args;

	i = 1;
	if (!extract_in_lexbuf(prompt, WORD, 2))
	{
		printf ("\n");
		prompt->input->exit_status = 0;
		return ;
	}
	args = ft_join_word2(prompt);
	if (!args)
		return (free_child(prompt), exit(1));
	while (args[i] && is_no_newline(args[i]) == 1)
		i++;
	print_arg(args, i);
	free(args);
	prompt->input->exit_status = 0;
}
