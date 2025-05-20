/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:49:56 by sbo               #+#    #+#             */
/*   Updated: 2023/12/15 10:21:09 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_pile
{
	int					nbr;
	struct s_pile		*next;
}	t_pile;

int		test_tri(t_pile *stack);
void	sb(t_pile **a);
void	rb(t_pile **a);
void	rrb(t_pile **a);
void	pb(t_pile **a, t_pile **b);
void	sa(t_pile **a);
void	ra(t_pile **a);
void	rra(t_pile **a);
void	rr(t_pile **a, t_pile **b);
void	rrr(t_pile **a, t_pile **b);
void	pa(t_pile **a, t_pile **b);
t_pile	*ft_create_stack(char **tab, int lenght);
int		ft_atoi(const char *nptr);
void	ft_lstclear(t_pile **lst);
int		ft_lstsize(t_pile *lst);
int		ft_max(int i, int j);
int		ft_abs(int n);
int		stack_max(t_pile *pile_a);
int		stack_min(t_pile *pile_a);
void	set_ab(t_pile **a, t_pile **b, int i, int j);
void	set_a(t_pile **a, int i);
void	set_b(t_pile **b, int i);
int		nbr_de_inf(t_pile *a, int n);
int		ft_quartile(t_pile *a, int valeur);
void	push_sort(t_pile **a, t_pile **b);
t_pile	*reverse(t_pile *stack, int index);
int		place(t_pile *a, int n);
int		pick(t_pile *a, t_pile *b);
int		recup_b(t_pile *b, int i);
void	push_swap(t_pile **pile_a, t_pile **pile_b);
void	sort_pile_3(t_pile **pile_a);
void	sort_little(t_pile **pile_a, t_pile **pile_b);
int		ft_isonly(t_pile *stack);
int		error_manage(char **argv, int argc);
t_pile	*ft_lstnew(int nbr);
void	ft_lstadd_back(t_pile **lst, t_pile *new);
void	d_rota(t_pile **a, t_pile **b);
int		ft_strlen(const char *str);
void	d_rev_rota(t_pile **a, t_pile **b);
void	swap(t_pile **a);
void	rota(t_pile **a);
void	rev_rota(t_pile **a);
void	push(t_pile **a, t_pile **b);
int		check_inst(char *instr);
int		ft_strcmp(const char *s1, const char *s2);
void	free_error(char *total, char *instr, t_pile **pile_a);
void	checker(t_pile **pile_a, t_pile **pile_b);

#endif