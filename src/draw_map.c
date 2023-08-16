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

int	draw_map(t_cub *cub)
{
	int			i;
	int			j;
	t_pointInt	p;

	p.x = 0;
	p.y = 0;
	ft_printf("Setting background\n");
	ft_memset(cub->img->pixels, get_color(255, 255, 255, 255), cub->img->width * cub->img->height * BPP); // Set background color
	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (j < cub->map_width)
		{
			if (cub->map[i][j] != '0')
			{
				if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' || cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
				{
					ft_printf("Found player: %c", cub->map[i][j]);
					cub->player.position.x = i;
					cub->player.position.y = j;
					if (cub->map[i][j] == 'N' )
						cub->player.orientation = M_PI_2;
					else if (cub->map[i][j] == 'S')
						cub->player.orientation = M_PI_2 + M_PI;
					else if (cub->map[i][j] == 'E')
						cub->player.orientation = 0;
					else if (cub->map[i][j] == 'W')
						cub->player.orientation = M_PI;
					++j;
					continue;
				}
				p.x = i * MAP_SQUARE;
				p.y = j * MAP_SQUARE;
				draw_square(cub->img, p, MAP_SQUARE, get_color(0x0, 0x0, 0xFF, 0xFF));
			}
			++j;
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
