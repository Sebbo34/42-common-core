/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:00:47 by sbo               #+#    #+#             */
/*   Updated: 2024/04/02 10:17:02 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_digit2(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0
			&& ((str[i] != '+' && str[i] != '-') || i != 0))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_lexbuf *prompt)
{
	char	*arg;
	int		status;

	arg = extract_in_lexbuf(prompt, WORD, 2);
	if (!arg)
		status = 0;
	else
		status = ft_atoi(arg);
	if (is_digit2(arg) == 0)
	{
		if (have_pipe(prompt) == 0)
			write(2, "exit\n", 6);
		write_error(prompt, "minishell: exit: ", arg, 2);
		write(2, ": numeric argument required\n", 29);
		free_child(prompt);
		exit(2);
	}
	if (number_of_args(prompt) > 1)
		return (write_error(prompt,
				"minishell : exit : too many arguments\n", NULL, 1));
	if (have_pipe(prompt) == 0)
		write(2, "exit\n", 6);
	free_child(prompt);
	exit(status);
}
