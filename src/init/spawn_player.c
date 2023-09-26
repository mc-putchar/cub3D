/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 05:20:24 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/26 13:22:14 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	read_direction(char c)
{
	int	i;

	i = 3;
	while (DIRECTIONS[i] != c && i--)
		;
	return (i + 1);
}

static void	set_direction(int c, t_vector *dir)
{
	if (c & 1)
	{
		dir->y = 0;
		if (c >> 1)
			dir->x = -1;
		else
			dir->x = 1;
	}
	else
	{
		dir->x = 0;
		if (c >> 2)
			dir->y = -1;
		else
			dir->x = 1;
	}
}

static void	reset_data(t_player *player, t_size x, t_size y, int d)
{
	player->position.x = x + 0.5;
	player->position.y = y + 0.5;
	set_direction(d, &player->direction);
	player->has_key = 0;
	player->move_speed = P_MOVE_SPEED;
	player->turn_speed = P_TURN_SPEED;
	player->dir_move = 0;
	player->side_move = 0;
	player->turn_dir = 0;
}

int	spawn_player(t_player *player, t_map *map)
{
	t_size	x;
	t_size	y;
	int		d;

	y = 0;
	while (++y < map->height - 1)
	{
		x = 0;
		while (++x < map->width - 1)
		{
			d = read_direction(map->val[y][x]);
			if (!d)
				continue ;
			reset_data(player, x, y, d);
			map->val[y][x] = '0';
			(void)ft_printf("Player spawned\n");
			return (0);
		}
	}
	return (throw_error("Player disappeared from the map"));
}
