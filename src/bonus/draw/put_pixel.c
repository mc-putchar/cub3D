/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:34:38 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/24 09:29:41 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* RGBA but Alpha channel is ignored on minilibx Linux implementation */
void	put_pixel(t_mlx_image *img, int x, int y, int color)
{
	t_uint32	pix;

	if (x < 0 || (t_uint32)x >= img->width \
	|| y < 0 || (t_uint32)y >= img->height)
		return ;
	pix = (x + img->width * y) << 2;
	img->pixels[pix] = color & 0xFF;
	img->pixels[++pix] = (color >> 8) & 0xFF;
	img->pixels[++pix] = (color >> 16) & 0xFF;
}

void	put_circle(t_mlx_image *img, t_point *center, int r, int color)
{
	int const	sqrad = r * r;
	int			i;
	int			j;

	if (r < 1)
		return ;
	j = center->y - r;
	if (j < 0)
		j = 0;
	while (j <= center->y + r && (t_uint32)j < img->height)
	{
		i = center->x - r;
		if (i < 0)
			i = 0;
		while (i <= center->x + r && (t_uint32)i < img->width)
		{
			if (((i - center->x) * (i - center->x)) \
			+ ((j - center->y) * (j - center->y)) <= sqrad)
				put_pixel(img, i, j, color);
			++i;
		}
		++j;
	}
}
