/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:32:09 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/28 00:50:52 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	swap_ptr(t_sprite **p1, t_sprite **p2)
{
	t_sprite	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void	quicksort(t_sprite **tab, int size)
{
	double	pivot;
	int		i;
	int		j;

	if (size < 2)
		return ;
	pivot = tab[size / 2]->dist;
	i = -1;
	j = size;
	while (1)
	{
		while (tab[++i]->dist < pivot)
			;
		while (tab[--j]->dist > pivot)
			;
		if (i >= j)
			break ;
		swap_ptr(&tab[i], &tab[j]);
	}
	quicksort(tab, i);
	quicksort(tab + i, size - i);
}
