/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:17:20 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/16 19:17:20 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_cub *cub, int forward, int sideways)
{

	if (forward)
	{
		cub->player.position.x += cub->player.pdir.x * forward * PLAYER_STEP;
		cub->player.position.y += cub->player.pdir.y * forward * PLAYER_STEP;
	}
	if (sideways)
	{
		cub->player.position.x -= cub->player.pdir.y * sideways * PLAYER_STEP;
		cub->player.position.y -= cub->player.pdir.x * sideways * PLAYER_STEP;
	}
}

void	turn_player(t_cub *cub, int rotation)
{
	cub->player.direction += 0.1 * rotation;
	if (cub->player.direction > M_PI * 2)
		cub->player.direction -= M_PI * 2;
	if (cub->player.direction < 0)
		cub->player.direction += M_PI * 2;
	cub->player.pdir.x = cos(cub->player.direction);
	cub->player.pdir.y = sin(cub->player.direction);
}
