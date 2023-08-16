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

	if (x < 0 || (uint32_t)x > img->height)
		return ;
	if (y < 0 || (uint32_t)y > img->width)
		return ;
	pix = (x * img->width + y) * BPP;
	img->pixels[pix++] = (color >> 24) & 0xFF;
	img->pixels[pix++] = (color >> 16) & 0xFF;
	img->pixels[pix++] = (color >> 8) & 0xFF;
	img->pixels[pix] = color & 0xFF;
}

void	intensify_pixels(mlx_image_t *img,int x, int y, double r)
{
	(void)r;
	put_pixel(img, x, y, 0xFFFFFFFF);
}

void	gupta_spoull(mlx_image_t *img,t_pointInt p1, t_pointInt p2)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	x = p1.x;
	y = p1.y;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	double	D = 0;
	int	d = 2 * dy - dx;

	double length = sqrt(dx * dx + dy * dy);

	double sin = dx/length;
	double cos = dy/length;
	while (x <= p2.x)
	{
		intensify_pixels(img, x, y - 1, D + cos);
		intensify_pixels(img, x, y, D);
		intensify_pixels(img, x, y + 1, D - cos);
		x++;
		if (d <= 0)
		{
			D += sin;
			d += 2 * dy;
		}
		else
		{
			D = D + sin - cos;
			d = d + 2 * (dy - dx);
			y++;
		}
	}
}

void	draw_line(mlx_image_t *img, t_pointInt p1, t_pointInt p2)
{
	gupta_spoull(img, p1, p2);
}
