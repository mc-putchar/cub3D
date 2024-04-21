/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:04:41 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 01:55:34 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

static inline int	door_check(t_map *map, int x, int y)
{
	if (x < 0 || (size_t)x >= map->width || y < 0 || (size_t)y >= map->height)
		return (0);
	if (map->val[y][x] == 'D' || map->val[y][x] == 'O')
		return (1);
	return (0);
}

static inline void	toggle_door(t_map *map, int x, int y)
{
	if (map->val[y][x] == 'D')
		map->val[y][x] = 'O';
	else if (map->val[y][x] == 'O')
		map->val[y][x] = 'D';
}

void	player_interact(t_player *player, t_map *map)
{
	int	x;
	int	y;

	x = 1 - 2 * (player->direction.x < 0);
	y = 1 - 2 * (player->direction.y < 0);
	if (door_check(map, player->position.x + x, player->position.y))
		toggle_door(map, player->position.x + x, player->position.y);
	if (door_check(map, player->position.x, player->position.y + y))
		toggle_door(map, player->position.x, player->position.y + y);
	if (door_check(map, player->position.x + x, player->position.y + y))
		toggle_door(map, player->position.x + x, player->position.y + y);
}
