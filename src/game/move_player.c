/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:56:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/19 19:56:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_cub *cub, t_keys key)
{
	t_vector	delta;

	delta.x = cub->player->direction.x * MOVE_SPEED;
	delta.y = cub->player->direction.y * MOVE_SPEED;
	if (key == MLX_KEY_S)
	{
		delta.x *= -1;
		delta.y *= -1;
	}
	cub->player->position.x += delta.x;
	cub->player->position.y += delta.y;
	printf("Move (%f, %f) > POS(%f, %f)\n", delta.x, delta.y, \
	cub->player->position.x, cub->player->position.y);
}

void	sidestep_player(t_cub *cub, t_keys key)
{
	t_vector	delta;

	delta.x = cub->player->direction.y * MOVE_SPEED;
	delta.y = cub->player->direction.x * MOVE_SPEED;
	if (key == MLX_KEY_A)
	{
		delta.x *= -1;
		delta.y *= -1;
	}
	cub->player->position.x += delta.x;
	cub->player->position.y += delta.y;
	printf("Move (%f, %f) > POS(%f, %f)\n", delta.x, delta.y, \
	cub->player->position.x, cub->player->position.y);
}
