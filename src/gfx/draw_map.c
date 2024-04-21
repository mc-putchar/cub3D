/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:36:24 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/18 18:27:35 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "cub3D.h"

void	draw_square(t_mlx_image *img, t_point p, uint32_t size, int color)
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
	int		color;
	t_point	p;

	y = 0;
	scale = (size_t)img->height / map->height;
	if ((size_t)img->width / map->width)
		scale = (size_t)img->width / map->width;
	ft_printf("Scale: %d\n", (int)scale);
	if (scale < 2)
		return ;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->val[y][x] == '0')
				color = 0x424242;
			else if (map->val[y][x] > '0')
				color = 0xFFFF55;
			else
				color = 0x212121;
			p.x = x * scale;
			p.y = y * scale;
			draw_square(img, p, scale - 2, color);
			++x;
		}
		++y;
	}
}
