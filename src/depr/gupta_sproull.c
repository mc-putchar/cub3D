/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gupta_sproull.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:22:09 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/16 15:22:09 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	intensify_pixels(mlx_image_t *img,int x, int y, double r)
{
	printf("%f\n", r);
	put_pixel(img, x, y, get_color(0, 0, 0, ft_clampd(r * 0xFF, 0, 0xFF)));
}

void	gupta_sproull(mlx_image_t *img,t_point p1, t_point p2)
{
	int const		dx = p2.x - p1.x;
	int const		dy = p2.y - p1.y;
	t_point		p;
	double const	sin = dx/sqrt(dx * dx + dy * dy);
	double const	cos = dy/sqrt(dx * dx + dy * dy);

	double	D = 0;
	int		d = 2 * dy - dx;

	p.x = p1.x;
	p.y = p1.y;
	while (p.x <= p2.x)
	{
		intensify_pixels(img, p.x, p.y - 1, D + cos);
		intensify_pixels(img, p.x, p.y, D);
		intensify_pixels(img, p.x, p.y + 1, D - cos);
		p.x++;
		if (d <= 0)
		{
			D += sin;
			d += 2 * dy;
		}
		else
		{
			D = D + sin - cos;
			d = d + 2 * (dy - dx);
			p.y++;
		}
	}
}
