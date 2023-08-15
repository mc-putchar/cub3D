/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawMap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 05:44:23 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/15 05:44:23 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	drawSquare(mlx_image_t *img, t_pointInt position, int size, int color)
{
	int const			x = (int)position.x;
	int const			y = (int)position.y;
	int					i;
	int					j;
	long unsigned int	pix;

	i = 0;
	while(i < size)
	{
		j = 0;
		while (j < size)
		{
			pix = (x + i) * img->width * BPP + ((y + j) * BPP);
			if (pix > img->width * img->height * BPP)
				break ;
			img->pixels[pix++] = (color >> 24) & 0xFF;
			img->pixels[pix++] = (color >> 16) & 0xFF;
			img->pixels[pix++] = (color >> 8) & 0xFF;
			img->pixels[pix] = color & 0xFF;
			++j;
		}
		++i;
	}
}

int	drawMap(t_cub *cub)
{
	int			i;
	int			j;
	t_pointInt	p;

	p.x = 0;
	p.y = 0;
	ft_memset(cub->img->pixels, getColor(255, 255, 255, 255), cub->img->width * cub->img->height * BPP);
	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (j < cub->map_width)
		{
			if (cub->map[i][j] != '0')
			{
				p.x = i * MAP_SQUARE;
				p.y = j * MAP_SQUARE;
				drawSquare(cub->img, p, MAP_SQUARE, getColor(0x0, 0x0, 0xFF, 0xFF));
			}
			++j;
		}
		++i;
	}
	return (EXIT_SUCCESS);
}
