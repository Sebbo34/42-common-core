/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:15:29 by sbo               #+#    #+#             */
/*   Updated: 2024/03/29 15:46:34 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_exit_status(int *exit_status, int error)
{
	*exit_status = error;
}

char	**ft_join_word2(t_lexbuf *prompt)
{
	int			len;
	t_lexbuf	*tmp;
	char		**join_word;

	tmp = prompt;
	len = get_len_cmd(prompt);
	join_word = malloc((len + 1) * sizeof(char *));
	if (!join_word)
		return (NULL);
	len = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
		{
			join_word[len] = tmp->value;
			len++;
		}
		tmp = tmp->next;
	}
	join_word[len] = NULL;
	return (join_word);
}

int	check_path(char *path)
{
	struct stat	sb;

	if (lstat(path, &sb) == -1 && is_directory(path) == 0)
		return (0);
	else
		return (1);
}

int	is_directory(char *file)
{
	DIR	*rep;

	rep = opendir(file);
	if (!rep)
		return (0);
	else
	{
		closedir(rep);
		return (1);
	}
}

char	*trunc_path(char *oldpwd)
{
	int		i;
	int		len;
	char	*pwd;

	i = 0;
	len = 0;
	while (oldpwd[i])
	{
		if (oldpwd[i] == '/')
			len = i;
		i++;
	}
	if (len == 0)
		return (ft_strdup("/"));
	pwd = malloc(sizeof(char) * (len + 1));
	if (!pwd)
		return (NULL);
	i = 0;
	while (oldpwd[i] && i < len)
	{
		pwd[i] = oldpwd[i];
		i++;
	}
	pwd[i] = 0;
	return (pwd);
}
