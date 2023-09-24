/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:07:43 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/24 06:41:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	turn_player(t_cub *cub, int key)
{
	double	cosa;
	double	sina;
	double	tmp;

	if (key == ARROW_LEFT)
	{
		cosa = cos(-1 * TURN_SPEED);
		sina = sin(-1 * TURN_SPEED);
	}
	else
	{
		cosa = cos(TURN_SPEED);
		sina = sin(TURN_SPEED);
	}
	tmp = cub->player->direction.x;
	cub->player->direction.x = cosa * tmp - sina * cub->player->direction.y;
	cub->player->direction.y = sina * tmp + cosa * cub->player->direction.y;
	tmp = cub->camera->plane.x;
	cub->camera->plane.x = cosa * tmp - sina * cub->camera->plane.y;
	cub->camera->plane.y = sina * tmp + cosa * cub->camera->plane.y;
}
