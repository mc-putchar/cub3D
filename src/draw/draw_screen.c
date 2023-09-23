/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 06:55:53 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/23 14:45:04 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define WALL	360
#define DEPTH	640

static void	draw_strip(t_cub *cub, t_size i, double wall_dist, int side)
{
	t_size	pix;
	int		wall_height;
	t_size	wall_start;

	wall_height = WALL;
	if (wall_dist < 0)
		wall_height = -wall_height;
	if (wall_dist)
		wall_height /= wall_dist;
	if (wall_height > WALL)
		wall_height = WALL;
	wall_start = (cub->camera->height >> 1) - (wall_height >> 1);
	pix = 0;
	while (pix < wall_start)
		put_pixel(cub->img, i, pix++, cub->scene->ceiling);
	while (wall_height--)
		put_pixel(cub->img, i, pix++, cub->walls[side]->pixels[wall_height]);
	while (pix < (cub->camera->height))
		put_pixel(cub->img, i, pix++, cub->scene->floor);
}

int	draw_screen(t_cub *cub)
{
	double	wall_dist;
	int		side;
	t_size	strip;

	wall_dist = 0;
	strip = 0;
	while (strip < cub->camera->width)
	{
		side = raycaster(cub, strip, &wall_dist);
		draw_strip(cub, strip, wall_dist, side);
		++strip;
	}
	return (0);
}
