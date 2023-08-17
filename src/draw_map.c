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
	ft_bzero(img->pixels, img->width * img->height * BPP);
}

int	draw_map(t_cub *cub)
{
	int			i;
	int			j;
	t_point		p;

	j = -1;
	while (++j < cub->map_height)
	{
		i = -1;
		while (++i < cub->map_width)
		{
			if (ft_isdigit(cub->map[j][i]) && cub->map[j][i] != '0')
			{
				p.x = i * MAP_SQUARE;
				p.y = j * MAP_SQUARE;
				p.color = MAP_COLOR;
				draw_square(cub->img, &p, MAP_SQUARE, MAP_COLOR);
			}
		}
	}
	return (EXIT_SUCCESS);
}
