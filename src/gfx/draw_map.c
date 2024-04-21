/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:36:24 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 07:13:37 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "cub3D.h"

static void	draw_square(t_mlx_image *img, t_point p, uint32_t size, int color)
{
	uint32_t	i;
	uint32_t	j;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			put_pixel(img, p.x + i, p.y + j, color);
			++i;
		}
		++j;
	}
}

void	draw_map(t_mlx_image *img, t_map *map)
{
	size_t	x;
	size_t	y;
	size_t	scale;
	t_point	p;

	scale = (size_t)img->height / map->height;
	if ((size_t)img->width / map->width)
		scale = (size_t)img->width / map->width;
	if (scale < 4)
		scale = 4;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			p.x = x * scale;
			p.y = y * scale;
			draw_square(img, p, scale - 2, 0x424242 * (map->val[y][x] == '0') \
			+ 0xEEEE42 * (map->val[y][x] > '0') + 0x111111);
			++x;
		}
		++y;
	}
}
