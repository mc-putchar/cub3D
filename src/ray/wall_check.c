/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:29:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/23 13:30:20 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	wall_check(t_map *map, int x, int y)
{
	if (x < 0 || (t_size)x > map->width - 1 || \
		y < 0 || (t_size)y > map->height - 1)
		return (-1);
	if (map->val[y][x] == '1')
		return (1);
	return (0);
}
