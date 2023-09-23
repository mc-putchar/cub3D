/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 06:19:39 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/23 23:57:39 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	start_camera(t_camera *camera, t_size height, t_size width, t_vector plane)
{
	camera->height = height;
	camera->width = width;
	camera->plane.x = -plane.y;
	camera->plane.y = plane.x;
	return (0);
}
