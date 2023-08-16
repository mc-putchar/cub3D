/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 05:44:23 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/15 05:44:23 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clear_image(mlx_image_t *img)
{
	ft_memset(img->pixels, 0x000000FF, img->width * img->height * BPP);
}

int	draw_map(t_cub *cub)
{
	int			i;
	int			j;
	t_pointInt	p;

	p.x = 0;
	p.y = 0;
	j = 0;
	clear_image(cub->img);
	while (j < cub->map_height)
	{
		i = 0;
		while (i < cub->map_width)
		{
			if (cub->map[j][i] != '0')
			{
				if ((cub->map[j][i] == 'N' || cub->map[j][i] == 'S' \
					|| cub->map[j][i] == 'E' || cub->map[j][i] == 'W') && ++i)
					continue ;
				p.x = i * MAP_SQUARE;
				p.y = j * MAP_SQUARE;
				draw_square(cub->img, &p, MAP_SQUARE, 0xFF00FFFF);
			}
			++i;
		}
		++j;
	}
	return (EXIT_SUCCESS);
}
