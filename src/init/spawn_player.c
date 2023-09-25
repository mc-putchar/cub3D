/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 05:20:24 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 04:19:37 by mcutura          ###   ########.fr       */
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
			player->position.x = x + 0.5;
			player->position.y = y + 0.5;
			set_direction(d, &player->direction);
			map->val[y][x] = '0';
			(void)ft_printf("Player spawned\n");
			return (0);
		}
	}
	return (throw_error("Player disappeared from the map"));
}
