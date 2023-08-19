/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:25:23 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/19 14:25:23 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define CEILING_COLOR		0x0000FFFF
#define FLOOR_COLOR			0x555555FF
#define WALL_COLOR			0xFF0000FF

void	draw_column(mlx_image_t *img, t_point *start, int height, int width)
{
	int	i;
	int	j;

	j = 0;
	while ((uint32_t)j < img->height)
	{
		i = 0;
		while (i < width)
		{
			if (j < start->y && (uint32_t)j < img->height >> 1)
				put_pixel(img, start->x + i, j, CEILING_COLOR);
			else if (j > start->y + height)
				put_pixel(img, start->x + i, j, FLOOR_COLOR);
			else
				put_pixel(img, start->x + i, j, start->color);
			++i;
		}
		++j;
	}
}

void	draw_scene(t_cub *cub, double dist, int x, int w, unsigned char shade)
{
	int const	centerY = cub->img2->height >> 1;
	int			wall_height;
	t_point		p;

	wall_height = cub->img2->height;
	if (dist)
	 	wall_height = wall_height / dist * MAP_SQUARE;
	p.x = x;
	p.y = centerY - (wall_height >> 1);
	p.color = (((WALL_COLOR) >> 8) << 8) | shade;
	draw_column(cub->img2, &p, wall_height, w);
}