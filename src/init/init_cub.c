/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 04:00:38 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/29 04:25:05 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_cub(t_cub *cub, t_scene *scene, t_camera *camera, t_player *player)
{
	cub->scene = scene;
	cub->camera = camera;
	cub->player = player;
}
