/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:30:29 by sbo               #+#    #+#             */
/*   Updated: 2023/12/15 10:22:42 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "get_next_line.h"

char	*read_stdin(t_pile **pile_a)

{
	char	*instr;
	char	*total;
	int		i;

	i = 0;
	instr = NULL;
	total = NULL;
	while (instr || i == 0)
	{
		instr = get_next_line (0);
		if (check_inst (instr) == 0 && instr)
			free_error(total, instr, pile_a);
		if (instr)
		{
			total = join_gnl(total, instr, ft_strlen(instr), &i);
			if (!total)
				return (NULL);
			free(instr);
		}
	}
	return (total);
}

void	do_instruc(t_pile **pile_a, t_pile **pile_b, char *instr)

{
	if (ft_strcmp(instr, "ra\n") == 0)
		rota(pile_a);
	if (ft_strcmp(instr, "rb\n") == 0)
		rota(pile_b);
	if (ft_strcmp(instr, "pa\n") == 0)
		push(pile_b, pile_a);
	if (ft_strcmp(instr, "pb\n") == 0)
		push(pile_a, pile_b);
	if (ft_strcmp(instr, "rra\n") == 0)
		rev_rota(pile_a);
	if (ft_strcmp(instr, "rrb\n") == 0)
		rev_rota(pile_b);
	if (ft_strcmp(instr, "sa\n") == 0)
		swap(pile_a);
	if (ft_strcmp(instr, "sb\n") == 0)
		swap (pile_b);
	if (ft_strcmp(instr, "ss\n") == 0)
	{
		swap (pile_b);
		swap (pile_a);
	}
	if (ft_strcmp(instr, "rr\n") == 0)
		d_rota(pile_a, pile_b);
	if (ft_strcmp(instr, "rrr\n") == 0)
		d_rev_rota(pile_a, pile_b);
}

char	*extract_instr(char *total, int debut)

{
	int		i;
	char	*instr;

	i = 0;
	while (total[debut + i] != '\n')
		i++;
	instr = malloc (i + 2);
	if (instr == NULL)
		return (NULL);
	i = 0;
	while (total[debut] != '\n')
	{
		instr[i] = total[debut];
		i++;
		debut++;
	}
	instr[i] = total[debut];
	instr[i + 1] = 0;
	return (instr);
}

void	checker(t_pile **pile_a, t_pile **pile_b)

{
	char	*total;
	char	*instr;
	int		i;
	int		debut;

	i = 0;
	debut = 0;
	total = read_stdin(pile_a);
	while (total && total[i])
	{
		if (total[i] == '\n')
		{
			instr = extract_instr(total, debut);
			debut = i + 1;
			do_instruc(pile_a, pile_b, instr);
			free(instr);
		}
		i++;
	}
	if (total)
		free(total);
}

int	main(int argc, char *argv[])

{
	t_pile	*pile_a;
	t_pile	*pile_b;

	if (argc < 2 || error_manage(argv, argc) == 0)
		return (0);
	pile_a = NULL;
	pile_b = NULL;
	pile_a = ft_create_stack(argv, argc);
	if (!pile_a)
		return (0);
	if (ft_isonly(pile_a) == 0)
	{
		ft_lstclear(&pile_a);
		return (0);
	}
	checker(&pile_a, &pile_b);
	if (test_tri(pile_a) == 1 && !pile_b)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	ft_lstclear(&pile_a);
	ft_lstclear(&pile_b);
	return (0);
}
