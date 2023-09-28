/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:07:43 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/26 13:00:59 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	turn_player(t_player *player, t_camera *camera)
{
	double	cosa;
	double	sina;
	double	tmp;

	if (!player->turn_dir)
		return ;
	cosa = cos(player->turn_speed * player->turn_dir);
	sina = sin(player->turn_speed * player->turn_dir);
	tmp = player->direction.x;
	player->direction.x = cosa * tmp - sina * player->direction.y;
	player->direction.y = sina * tmp + cosa * player->direction.y;
	tmp = camera->plane.x;
	camera->plane.x = cosa * tmp - sina * camera->plane.y;
	camera->plane.y = sina * tmp + cosa * camera->plane.y;
}
