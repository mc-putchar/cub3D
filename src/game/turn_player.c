/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:07:43 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 10:42:46 by mcutura          ###   ########.fr       */
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
	angle = cub->player->turn_speed * (x - (cub->win_w >> 1)) * 0.15;
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
		cosa = cos(cub->player->turn_speed * -1);
		sina = sin(cub->player->turn_speed * -1);
	}
	else
	{
		cosa = cos(cub->player->turn_speed);
		sina = sin(cub->player->turn_speed);
	}
	tmp = cub->player->direction.x;
	cub->player->direction.x = cosa * tmp - sina * cub->player->direction.y;
	cub->player->direction.y = sina * tmp + cosa * cub->player->direction.y;
	tmp = cub->camera->plane.x;
	cub->camera->plane.x = cosa * tmp - sina * cub->camera->plane.y;
	cub->camera->plane.y = sina * tmp + cosa * cub->camera->plane.y;
}
