/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:29:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 05:11:52 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* 0 will never be O
 * Nevermind
 */
int	wall_check(t_map *map, int x, int y)
{
	if (x < 0 || (t_size)x > map->width - 1 || \
		y < 0 || (t_size)y > map->height - 1)
		return (-1);
	if (map->val[y][x] > '0' && map->val[y][x] != 'O')
		return (map->val[y][x]);
	return (0);
}
