/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freez.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:11:54 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/16 10:11:54 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(char **map, int size)
{
	while (size--)
		free(map[size]);
	free(map);
}
