/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:43:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/16 11:43:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(mlx_image_t *img, int x, int y, int color)
{
	int	pix;

	if (x < 0 || (uint32_t)x >= img->width)
		return ;
	if (y < 0 || (uint32_t)y >= img->height)
		return ;
	pix = (x + img->width * y) * BPP;
	img->pixels[pix++] = (color >> 24) & 0xFF;
	img->pixels[pix++] = (color >> 16) & 0xFF;
	img->pixels[pix++] = (color >> 8) & 0xFF;
	img->pixels[pix] = color & 0xFF;
}

void	draw_line(mlx_image_t *img, t_point *p1, t_point *p2)
{
	bresenham(img, p1, p2);
}
