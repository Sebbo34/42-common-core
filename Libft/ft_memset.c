/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:05:54 by sbo               #+#    #+#             */
/*   Updated: 2023/11/11 19:25:10 by sbo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)

{
	size_t			cpt;
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	cpt = 0;
	while (cpt < n)
	{
		ptr[cpt] = c;
		cpt++;
	}
	return (s);
}
/*
int main(void)

{

	int array [] = { 54, 85, 20, 63, 21 };
	size_t size = sizeof( int ) * 5;
	int length;

	for( length=0; length<5; length++) {
		printf( "%d ", array[ length ] );
	}
	printf( "\n" );
	ft_memset( array, 0, size );

	for( length=0; length<5; length++) {
		printf( "%d ", array[ length ] );
	}
	printf( "\n" );
	
	return 0;

}
*/