/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:07:51 by sbo               #+#    #+#             */
/*   Updated: 2024/03/29 15:45:13 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only(char **arg, int ind)
{
	int	i;

	i = ind + 1;
	while (arg[i])
	{
		if (strcmp_equal(arg[ind], arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_first_char(char *chaine)
{
	int	i;

	i = 0;
	if (ft_isalpha(chaine[i]) == 0 && chaine[i] != '_')
		return (0);
	else
		return (1);
	return (0);
}

int	check_char(char *chaine)
{
	int	i;

	i = 0;
	if (check_first_char(chaine) == 0)
		return (0);
	while (chaine[i] != '=' && chaine[i])
	{
		if (ft_isalnum(chaine[i]) == 0 && chaine[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	*parse_export(char **arg, char **env)
{
	int		*tab_nbr;
	int		i;

	tab_nbr = malloc((ft_strlen_tab(arg) + 1) * sizeof(int));
	if (!tab_nbr)
		return (NULL);
	i = 1;
	tab_nbr[0] = ft_strlen_tab(env);
	while (arg[i])
	{
		if (check_char(arg[i]) == 0)
			tab_nbr[i] = -2;
		else if (find_equal(arg[i]) == 0)
			tab_nbr[i] = -1;
		else if (check_env(arg[i], env) == 1)
			tab_nbr[i] = 2;
		else if (check_env(arg[i], env) == 0 && is_only(arg, i) == 1)
			tab_nbr[i] = 1;
		else if (check_env(arg[i], env) == 0 && is_only(arg, i) == 0)
			tab_nbr[i] = -3;
		if (tab_nbr[i] == 1)
			tab_nbr[0]++;
		i++;
	}
	return (tab_nbr);
}
