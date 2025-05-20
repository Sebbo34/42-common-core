/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:21:55 by sbo               #+#    #+#             */
/*   Updated: 2023/12/15 10:21:52 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "get_next_line.h"

int	ft_strlen(const char *str)

{
	int	longueur;

	if (!str)
		return (0);
	longueur = 0;
	while (str[longueur])
	{
		longueur++;
	}
	return (longueur);
}

void	d_rota(t_pile **a, t_pile **b)

{
	rota(a);
	rota(b);
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

int	check_inst(char *instr)

{
	if (!instr)
		return (0);
	if (ft_strcmp(instr, "ra\n") == 0)
		return (1);
	if (ft_strcmp(instr, "rb\n") == 0)
		return (1);
	if (ft_strcmp(instr, "pa\n") == 0)
		return (1);
	if (ft_strcmp(instr, "pb\n") == 0)
		return (1);
	if (ft_strcmp(instr, "rra\n") == 0)
		return (1);
	if (ft_strcmp(instr, "rrb\n") == 0)
		return (1);
	if (ft_strcmp(instr, "sa\n") == 0)
		return (1);
	if (ft_strcmp(instr, "sb\n") == 0)
		return (1);
	if (ft_strcmp(instr, "rr\n") == 0)
		return (1);
	if (ft_strcmp(instr, "rrr\n") == 0)
		return (1);
	if (ft_strcmp(instr, "ss\n") == 0)
		return (1);
	return (0);
}

void	free_error(char *total, char *instr, t_pile **pile_a)
{
	if (total)
		free(total);
	ft_lstclear(pile_a);
	free(instr);
	exit(0);
}
