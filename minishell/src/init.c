/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:50:48 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/27 18:15:14 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_input *input)
{
	input->nread = 0;
	input->again = 1;
	input->len = 0;
}

void	init_utils(t_utils *utils)
{
	utils->i = 0;
	utils->j = 0;
	utils->varname_start = -1;
	utils->end = 0;
	utils->varname_len = 0;
	utils->varcontent_len = 0;
	utils->varname1 = NULL;
	utils->varcontent1 = NULL;
}

void	reset_iterators(t_utils *utils)
{
	utils->i = 0;
	utils->j = 0;
	utils->start += -1;
	utils->i = utils->start;
}
