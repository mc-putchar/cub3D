/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 05:46:50 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/26 13:45:19 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	door_check(t_map *map, int x, int y, int haskey)
{
	if (x < 0 || y < 0 || (t_size)x >= map->width || (t_size)y >= map->height)
		return (0);
	if (map->val[y][x] == 'D' || \
		map->val[y][x] == 'O')
		return (1);
	if (map->val[y][x] == 'L')
	{
		if (haskey)
			return (1);
		else
			ft_printf("You need key to open this door\n");
	}
	return (0);
}

static inline void	toggle_door(t_map *map, int x, int y)
{
	if (map->val[y][x] == 'D')
		map->val[y][x] = 'O';
	else if (map->val[y][x] == 'O')
		map->val[y][x] = 'D';
	else if (map->val[y][x] == 'L')
		map->val[y][x] = 'U';
}

void	interact(t_cub *cub)
{
	t_map *const	map = &cub->scene->map;
	t_player *const	pl = cub->player;
	int				x;
	int				y;

	x = 1;
	y = 1;
	if (pl->direction.x < 0)
		x = -x;
	if (pl->direction.y < 0)
		y = -y;
	if (door_check(map, pl->position.x + x, pl->position.y, pl->has_key))
		toggle_door(map, pl->position.x + x, pl->position.y);
	if (door_check(map, pl->position.x, pl->position.y + y, pl->has_key))
		toggle_door(map, pl->position.x, pl->position.y + y);
	if (door_check(map, pl->position.x + x, pl->position.y + y, pl->has_key))
		toggle_door(map, pl->position.x + x, pl->position.y + y);
}
