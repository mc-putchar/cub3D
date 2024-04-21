/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:53:12 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/19 18:16:55 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_camera(t_cub *cub, t_camera *cam, t_vector player_dir)
{
	cub->camera = cam;
	cam->height = cub->win_h;
	cam->width = cub->win_w;
	cam->plane.x = -player_dir.y;
	cam->plane.y = player_dir.x;
	cam->zbuffer = malloc(sizeof(double) * cam->width);
	if (!cam->zbuffer)
		return (throw_error(MALLOC_FAIL));
	return (0);
}
