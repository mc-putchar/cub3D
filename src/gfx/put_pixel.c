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

/* ARGB but Alpha channel is ignored on minilibx Linux implementation */
void	put_pixel(t_mlx_image *img, int x, int y, int color)
{
	uint32_t	pix;

	if (x < 0 || (uint32_t)x >= img->width || \
		y < 0 || (uint32_t)y >= img->height)
		return ;
	pix = (img->width * y + x) << 2;
	img->pixels[pix] = color & 0xFF;
	img->pixels[++pix] = (color >> 8) & 0xFF;
	img->pixels[++pix] = (color >> 16) & 0xFF;
}
