/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:02:03 by sbo               #+#    #+#             */
/*   Updated: 2024/03/30 18:52:08 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_var_pwd(char **env, int check)
{
	int		i;
	char	*chaine;

	chaine = NULL;
	i = 0;
	while (env[i])
	{
		if (strcmp_equal("PWD=", env[i]) == 0)
		{
			chaine = ft_strdup(&env[i][4]);
			if (!chaine)
				return (NULL);
		}
		i++;
	}
	if (check == 1)
	{
		if (chaine)
			chaine = ft_strjoin2("OLDPWD=", chaine, NULL, 2);
		else
			chaine = ft_strdup("OLDPWD=");
	}
	return (chaine);
}

void	check_pwd_oldpwd(char **env, char *pwd, char *oldpwd)
{
	int	i;
	int	check_pwd;
	int	check_oldpwd;

	i = 0;
	check_pwd = 0;
	check_oldpwd = 0;
	while (env[i])
	{
		if (strcmp_equal(env[i], "PWD=") == 0)
			check_pwd = 1;
		else if (strcmp_equal(env[i], "OLDPWD=") == 0)
			check_oldpwd = 1;
		i++;
	}
	if (check_pwd == 1 && check_oldpwd == 0)
		free(oldpwd);
	if (check_pwd == 0 && check_oldpwd == 1)
		free(pwd);
	if (check_pwd == 0 && check_oldpwd == 0)
	{
		free(pwd);
		free(oldpwd);
	}
}

char	**ft_export_cd(char **env, char *pwd)
{
	char	*oldpwd;
	int		i;

	oldpwd = get_var_pwd(env, 1);
	if (!oldpwd)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (strcmp_equal(env[i], "PWD=") == 0)
		{
			free(env[i]);
			env[i] = pwd;
		}
		else if (strcmp_equal(env[i], "OLDPWD=") == 0)
		{
			free(env[i]);
			env[i] = oldpwd;
		}
		i++;
	}
	check_pwd_oldpwd(env, pwd, oldpwd);
	return (env);
}
