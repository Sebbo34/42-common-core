/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <sbo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:19:59 by sbo               #+#    #+#             */
/*   Updated: 2023/11/21 19:45:46 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uputnbr(unsigned int nbr)

{
	int		j;
	char	*chaine;

	chaine = ft_itoa(nbr);
	if (chaine == NULL)
		return (0);
	j = ft_strlen(chaine);
	ft_putstr_fd(chaine, 1);
	free(chaine);
	return (j);
}
