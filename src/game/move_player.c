/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:56:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 09:14:02 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_cub *cub, int key)
{
	t_vector	delta;
	t_vector	spacer;

	delta.x = cub->player->direction.x * MOVE_SPEED;
	delta.y = cub->player->direction.y * MOVE_SPEED;
	spacer.x = 0.3;
	spacer.y = 0.3;
	if (delta.x < 0)
		spacer.x *= -1;
	if (delta.y < 0)
		spacer.y *= -1;
	if (key == KEY_S)
	{
		delta.x *= -1;
		delta.y *= -1;
		spacer.x *= -1;
		spacer.y *= -1;
	}
	if (!wall_check(&cub->scene->map, \
		(int)(cub->player->position.x + delta.x + spacer.x), \
		(int)(cub->player->position.y)))
		cub->player->position.x += delta.x;
	if (!wall_check(&cub->scene->map, (int)(cub->player->position.x), \
		(int)(cub->player->position.y + delta.y + spacer.y)))
		cub->player->position.y += delta.y;
}

void	sidestep_player(t_cub *cub, int key)
{
	t_vector	delta;
	t_vector	spacer;

	delta.x = -cub->player->direction.y * MOVE_SPEED;
	delta.y = cub->player->direction.x * MOVE_SPEED;
	spacer.x = 0.3;
	spacer.y = 0.3;
	if (delta.x < 0)
		spacer.x *= -1;
	if (delta.y < 0)
		spacer.y *= -1;
	if (key == KEY_A)
	{
		delta.x *= -1;
		delta.y *= -1;
		spacer.x *= -1;
		spacer.y *= -1;
	}
	if (!wall_check(&cub->scene->map, \
		(int)(cub->player->position.x + delta.x + spacer.x), \
		(int)(cub->player->position.y)))
		cub->player->position.x += delta.x;
	if (!wall_check(&cub->scene->map, (int)(cub->player->position.x), \
		(int)(cub->player->position.y + delta.y + spacer.y)))
		cub->player->position.y += delta.y;
}
