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

void	put_pixel(t_mlx_image *img, int x, int y, int color)
{
	t_uint32	pix;

	if (x < 0 || (t_uint32)x >= img->width || \
		y < 0 || (t_uint32)y >= img->height)
		return ;
	pix = (x + img->width * y) << 2;
	img->pixels[pix++] = (color >> 0) & 0xFF;
	img->pixels[pix++] = (color >> 8) & 0xFF;
	img->pixels[pix++] = (color >> 16) & 0xFF;
	img->pixels[pix] = (color >> 24) & 0xFF;
}
