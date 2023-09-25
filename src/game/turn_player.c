/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:07:43 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 04:06:31 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mouse_view(t_cub *cub, int x, int y)
{
	double	cosa;
	double	sina;
	double	tmp;
	double	angle;

	(void)y;
	angle = -1.0 * ((WIN_W >> 1) - x) / (WIN_W >> 2);
	cosa = cos(angle);
	sina = sin(angle);
	tmp = cub->player->direction.x;
	cub->player->direction.x = cosa * tmp - sina * cub->player->direction.y;
	cub->player->direction.y = sina * tmp + cosa * cub->player->direction.y;
	tmp = cub->camera->plane.x;
	cub->camera->plane.x = cosa * tmp - sina * cub->camera->plane.y;
	cub->camera->plane.y = sina * tmp + cosa * cub->camera->plane.y;
}

void	turn_player(t_cub *cub, int key)
{
	double	cosa;
	double	sina;
	double	tmp;

	if (key == ARROW_LEFT)
	{
		cosa = cos(TURN_SPEED * -1);
		sina = sin(TURN_SPEED * -1);
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
