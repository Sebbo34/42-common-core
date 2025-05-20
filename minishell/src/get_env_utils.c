/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:15:11 by sbo               #+#    #+#             */
/*   Updated: 2024/03/30 19:05:21 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr2(char *s, int c)
{
	int	cpt;

	if (s == NULL)
		return (-1);
	cpt = 0;
	c = (unsigned char)c;
	while (s[cpt])
	{
		if (s[cpt] == c)
			return (1);
		cpt++;
	}
	return (-1);
}

int	check_path_in_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strcmp_equal(env[i], "PATH=") == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_join_cmd(char *path, char *cmd)
{
	char	*chaine;
	char	*path_cmd;

	chaine = ft_strjoin(path, "/");
	if (!chaine)
		return (NULL);
	path_cmd = ft_strjoin(chaine, cmd);
	if (!path_cmd)
		return (free(chaine), NULL);
	free(chaine);
	return (path_cmd);
}

void	write_error(t_lexbuf *prompt, char *s1, char *s2, int exit_status)
{
	if (write (2, s1, ft_strlen(s1)) == -1)
		return (free_child(prompt), exit(1));
	if (s2)
	{
		if (write (2, s2, ft_strlen(s2)) == -1)
			return (free_child(prompt), exit(1));
	}
	if (exit_status != -1)
		prompt->input->exit_status = exit_status;
}

void	free_split(char **r_split)
{
	int	j;

	j = 0;
	while (r_split[j])
	{
		free(r_split[j]);
		j++;
	}
	free(r_split);
}
