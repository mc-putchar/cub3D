/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:55:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/16 22:55:59 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "point.h"

static void	get_quadrant(t_point *p1, t_point *p2, t_point	*quad)
{
	if (p1->x < p2->x)
		quad->x = 1;
	else
		quad->x = -1;
	if (p1->y < p2->y)
		quad->y = 1;
	else
		quad->y = -1;
}

static void	next_point(t_point *cur, t_point *d, t_point *q, int e[2])
{
	e[1] = e[0] * 2;
	if (e[1] > -d->y)
	{
		e[0] -= d->y;
		cur->x += q->x;
	}
	if (e[1] < d->x)
	{
		e[0] += d->x;
		cur->y += q->y;
	}
}

void	bresenham(mlx_image_t *img, t_point *p1, t_point *p2)
{
	t_point	delta;
	t_point	quad;
	t_point	cur;
	int			error[2];

	delta.x = ft_abs(p2->x - p1->x);
	delta.y = ft_abs(p2->y - p1->y);
	error[0] = delta.x - delta.y;
	cur = *p1;
	get_quadrant(p1, p2, &quad);
	while (cur.x != p2->x || cur.y != p2->y)
	{
		put_pixel(img, cur.x, cur.y, get_gradient(&cur, p1, p2, &delta));
		next_point(&cur, &delta, &quad, error);
	}
	put_pixel(img, cur.x, cur.y, get_gradient(&cur, p1, p2, &delta));
}
