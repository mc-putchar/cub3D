/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 05:46:50 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 08:32:10 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	door_check(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || (t_size)x >= map->width || (t_size)y >= map->height)
		return (0);
	if (map->val[y][x] == 'D' || map->val[y][x] == 'L' || \
		map->val[y][x] == 'O')
		return (1);
	return (0);
}

static inline void	switch_door(t_map *map, int x, int y)
{
	if (map->val[y][x] == 'D' || map->val[y][x] == 'L')
		map->val[y][x] = 'O';
	else if (map->val[y][x] == 'O')
		map->val[y][x] = 'D';
}

void	interact(t_cub *cub)
{
	t_map *const	map = &cub->scene->map;
	t_player *const	pl = cub->player;

	if (door_check(map, pl->position.x, pl->position.y))
		switch_door(map, pl->position.x, pl->position.y);
	if (door_check(map, pl->position.x + 1, pl->position.y))
		switch_door(map, pl->position.x + 1, pl->position.y);
	if (door_check(map, pl->position.x - 1, pl->position.y))
		switch_door(map, pl->position.x - 1, pl->position.y);
	if (door_check(map, pl->position.x, pl->position.y + 1))
		switch_door(map, pl->position.x, pl->position.y + 1);
	if (door_check(map, pl->position.x, pl->position.y - 1))
		switch_door(map, pl->position.x, pl->position.y - 1);
}
