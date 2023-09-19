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
#define WALL_COLOR_N		0xFFFF00FF
#define WALL_COLOR_S		0xFF00FFFF
#define WALL_COLOR_E		0xAA0A0AFF
#define WALL_COLOR_W		0xF00F00FF

// void	draw_column(mlx_image_t *img, int x, int height, int width)
// {
// 	int	i;
// 	int	top;
// 	int	bottom;

// 	bottom = img->height >> 1;
// 	top = bottom;
// 	while (height-- && top--)
// 	{
// 		i = -1;
// 		while (++i < width)
// 		{
// 			put_pixel(img, x + i, top, WALL_COLOR);
// 			put_pixel(img, x + i, bottom, WALL_COLOR);
// 		}
// 		++bottom;
// 	}
// 	while (top--)
// 	{
// 		i = -1;
// 		while (++i < width)
// 		{
// 			put_pixel(img, x + i, top, CEILING_COLOR);
// 			put_pixel(img, x + i, bottom, FLOOR_COLOR);
// 		}
// 		++bottom;
// 	}
// }
void	draw_column(mlx_image_t *img, int x, int height, int width)
{
	int			i;
	int			j;
	int const	top = (img->height >> 1) - (height >> 1);
	int			color;

	j = -1;
	while ((uint32_t)++j < img->height)
	{
		if (j < top)
			color = CEILING_COLOR;
		else if (j < top + height)
			color = WALL_COLOR;
		else
		 	color = FLOOR_COLOR;
		i = -1;
		while (++i < width)
			put_pixel(img, x + i, j, color);
	}
}
// void	draw_scene(t_cub *cub, double dist, int x, int w, unsigned char shade)
// {
// 	int const	centerY = cub->img2->height >> 1;
// 	int			wall_height;
// 	t_point		p;

// 	wall_height = cub->img2->height;
// 	if (dist)
// 	 	wall_height = (wall_height / dist) * MAP_SQUARE;
// 	p.x = x;
// 	p.y = centerY - (wall_height >> 1);
// 	p.color = (((WALL_COLOR) >> 8) << 8) | shade;
// 	// draw_column(cub->img2, &p, wall_height, w);
// }
