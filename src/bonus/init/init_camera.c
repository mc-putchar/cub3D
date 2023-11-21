/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 06:19:39 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/29 04:16:30 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	start_camera(t_cub *cub, t_camera *camera, t_vector plane)
{
	camera->height = cub->img->height;
	camera->width = cub->img->width;
	camera->plane.x = -plane.y;
	camera->plane.y = plane.x;
	cub->zbuffer = malloc(sizeof(double) * camera->width);
	if (!cub->zbuffer)
		return (throw_error("Memory allocation failed"));
	return (0);
}
