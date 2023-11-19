/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:00:48 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 03:35:48 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	draw_player(t_mlx_image *img, int off)
{
	int	y;
	int	x;

	y = 1;
	while (++y < (1 << MINIMAP_PDIV) - 2)
	{
		x = 1;
		while (++x < (1 << MINIMAP_PDIV) - 2)
			put_pixel(img, x + off, y + off, 0xFF118899);
	}
}

void	draw_minimap(t_mlx_image *img, t_map *map, t_vector position)
{
	int const	offx = (int)position.x - (MINIMAP_SIZE >> (MINIMAP_PDIV + 1));
	int const	offy = (int)position.y - (MINIMAP_SIZE >> (MINIMAP_PDIV + 1));
	int			x;
	int			y;
	int			tmp;

	y = -1;
	while (++y < MINIMAP_SIZE)
	{
		tmp = offy + (y >> MINIMAP_PDIV);
		x = -1;
		while (++x < MINIMAP_SIZE)
		{
			if (tmp >= 0 && (t_size)tmp < map->height && \
				offx + (x >> MINIMAP_PDIV) >= 0 && \
				(t_size)(offx + (x >> MINIMAP_PDIV)) < map->width &&
				map->val[tmp][offx + (x >> MINIMAP_PDIV)] > '0')
				put_pixel(img, x, y, 0xFFFFFF55);
			else
				put_pixel(img, x, y, 0xFF333355);
		}
	}
	draw_player(img, MINIMAP_SIZE >> 1);
}
