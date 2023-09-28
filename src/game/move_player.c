/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:56:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/26 12:52:33 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	sidestep_player(t_player *player, t_map *map)
{
	t_vector	delta;
	t_vector	spacer;

	if (!player->side_move)
		return ;
	delta.x = -player->direction.y * player->move_speed * player->side_move;
	delta.y = player->direction.x * player->move_speed * player->side_move;
	spacer.x = 0.3;
	spacer.y = 0.3;
	if (delta.x < 0)
		spacer.x *= -1;
	if (delta.y < 0)
		spacer.y *= -1;
	if (!wall_check(map, \
		(int)(player->position.x + delta.x + spacer.x), \
		(int)(player->position.y)))
		player->position.x += delta.x;
	if (!wall_check(map, (int)(player->position.x), \
		(int)(player->position.y + delta.y + spacer.y)))
		player->position.y += delta.y;
}

void	move_player(t_player *player, t_map *map)
{
	t_vector	delta;
	t_vector	spacer;

	if (!player->dir_move)
		return ;
	delta.x = player->direction.x * player->move_speed * player->dir_move;
	delta.y = player->direction.y * player->move_speed * player->dir_move;
	spacer.x = 0.3;
	spacer.y = 0.3;
	if (delta.x < 0)
		spacer.x *= -1;
	if (delta.y < 0)
		spacer.y *= -1;
	if (!wall_check(map, \
		(int)(player->position.x + delta.x + spacer.x), \
		(int)(player->position.y)))
		player->position.x += delta.x;
	if (!wall_check(map, (int)(player->position.x), \
		(int)(player->position.y + delta.y + spacer.y)))
		player->position.y += delta.y;
}
