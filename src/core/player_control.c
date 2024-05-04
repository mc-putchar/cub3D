/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:02:44 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/20 21:04:05 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	turn_player(t_player *player, t_camera *camera)
{
	double const	cosa = cos(player->turn_speed * player->turn_dir);
	double const	sina = sin(player->turn_speed * player->turn_dir);
	double			tmp;

	if (!player->turn_dir)
		return ;
	tmp = player->direction.x;
	player->direction.x = cosa * tmp - sina * player->direction.y;
	player->direction.y = sina * tmp + cosa * player->direction.y;
	tmp = camera->plane.x;
	camera->plane.x = cosa * tmp - sina * camera->plane.y;
	camera->plane.y = sina * tmp + cosa * camera->plane.y;
}

static inline int	wall_check(t_map *map, int x, int y)
{
	if (x < 0 || (size_t)x >= map->width \
	|| y < 0 || (size_t)y >= map->height)
		return (1);
	return (map->val[y][x] != '0' && map->val[y][x] != 'O');
}

void	move_player(t_player *player, t_map *map)
{
	t_vector	delta;
	t_vector	spacer;

	if (!player->dir_move && !player->side_move)
		return ;
	delta.x = player->direction.x * player->dir_move;
	delta.x -= player->direction.y * player->side_move;
	delta.x *= player->move_speed;
	delta.y = player->direction.y * player->dir_move;
	delta.y += player->direction.x * player->side_move;
	delta.y *= player->move_speed;
	spacer.x = WALL_BUFFER * (1 + (delta.x < 0) * -2);
	spacer.y = WALL_BUFFER * (1 + (delta.y < 0) * -2);
	if (!wall_check(map, (int)(player->position.x + delta.x + spacer.x), \
		(int)(player->position.y + spacer.y)) \
	&& !wall_check(map, (int)(player->position.x + delta.x + spacer.x), \
		(int)(player->position.y - spacer.y)))
		player->position.x += delta.x;
	if (!wall_check(map, (int)(player->position.x + spacer.x), \
		(int)(player->position.y + delta.y + spacer.y)) \
	&& !wall_check(map, (int)(player->position.x - spacer.x), \
		(int)(player->position.y + delta.y + spacer.y)))
		player->position.y += delta.y;
}
