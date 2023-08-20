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

/* TODO: fix this S.H.I.T. - sidestep doesn't work properly
		align with framerate
		detect collision
*/
void	move_player(t_cub *cub, int forward, int sideways)
{
	if (forward)
	{
		cub->player.position.x += round(cub->player.pdir.x * forward * cub->player.move_speed);
		cub->player.position.y += round(cub->player.pdir.y * forward * cub->player.move_speed);
	}
	if (sideways)
	{
		cub->player.position.x += round(cub->player.pdir.y * sideways * cub->player.move_speed);
		cub->player.position.y += round(cub->player.pdir.x * sideways * cub->player.move_speed);
	}
}

void	turn_player(t_cub *cub, int rotation)
{
	cub->player.direction += rotation * cub->player.turn_speed;
	if (cub->player.direction >= 360)
		cub->player.direction -= 360;
	if (cub->player.direction < 0)
		cub->player.direction += 360;
	cub->player.pdir.x = cub->meth.coss[cub->player.direction];
	cub->player.pdir.y = cub->meth.sins[cub->player.direction];
}
