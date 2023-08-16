/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:58:45 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/16 10:58:45 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_square(mlx_image_t *img, t_pointInt *position, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(img, position->x + i, position->y + j, color);
			++j;
		}
		++i;
	}
}

void	draw_circle(mlx_image_t *img, t_pointInt *center, int radius, int color)
{
	int		i;
	int		j;
	double	d;

	j = center->y - radius;
	if (j < 0)
		j = 0;
	while (j <= center->y + radius && (uint32_t)j < img->height)
	{
		i = center->x - radius;
		if (i < 0)
			i = 0;
		while (i <= center->x + radius && (uint32_t)i < img->width)
		{
			d = sqrt((i - center->x) * (i - center->x) + \
				(j - center->y) * (j - center->y));
			if (round(d) <= radius)
				put_pixel(img, i, j, color);
			++i;
		}
		++j;
	}
}
