/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:03:28 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/20 17:03:28 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define DRAW_DISTANCE		24

static int	wall_check(t_point *p, t_cub *cub)
{
	int const	x = p->x >> MAP_BINDIV;
	int const	y = p->y >> MAP_BINDIV;

	if (x < 0 || x >= cub->map_width || y < 0 || y >= cub->map_height)
		return (0);
	if (ft_isdigit(cub->map[y][x]) && cub->map[y][x] != '0')
		return (1);
	return (0);
}

inline static void	offset_point(t_point *p, t_point *o)
{
	p->x += o->x;
	p->y += o->y;
}

int	find_horizontal_intersect(t_cub *cub, t_point *p, t_vector *ray, double const itn)
{
	t_point			d;
	t_point			o;
	int				steps;

	if (!ray->y)
		return (INT_MAX);
	if (ray->y < 0)
	{
		d.y = ((p->y >> MAP_BINDIV) << MAP_BINDIV) - 1;
		d.x = p->x + (p->y - d.y) * itn;
		o.y = -MAP_SQUARE;
		o.x = MAP_SQUARE * itn;
	}
	if (ray->y > 0)
	{
		d.y = ((p->y >> MAP_BINDIV) << MAP_BINDIV) + MAP_SQUARE;
		d.x = p->x + (p->y - d.y) * itn;
		o.y = MAP_SQUARE;
		o.x = MAP_SQUARE * itn;
	}
	steps = 0;
	while (!wall_check(&d, cub) && steps++ < DRAW_DISTANCE)
		offset_point(&d, &o);
	if (steps == DRAW_DISTANCE)
		return (INT_MAX);
	return ((d.x - p->x) * (d.x - p->x) + (d.y - p->y) * (d.y - p->y));
}

int	find_vertical_intersect(t_cub *cub, t_point *p, t_vector *ray, double const tn)
{
	t_point			d;
	t_point			o;
	int				steps;

	if (!ray->x)
		return (INT_MAX);
	if (ray->x < 0)
	{
		d.x = ((p->x >> MAP_BINDIV) << MAP_BINDIV) - 1;
		d.y = p->y + (p->x - d.x) * tn;
		o.x = -MAP_SQUARE;
		o.y = MAP_SQUARE * tn;
	}
	if (ray->x > 0)
	{
		d.x = ((p->x >> MAP_BINDIV) << MAP_BINDIV) + MAP_SQUARE;
		d.y = p->y + (p->x - d.x) * tn;
		o.x = MAP_SQUARE;
		o.y = MAP_SQUARE * tn;
	}
	steps = 0;
	while (!wall_check(&d, cub) && steps++ < DRAW_DISTANCE)
		offset_point(&d, &o);
	if (steps == DRAW_DISTANCE)
		return (INT_MAX);
	return ((d.x - p->x) * (d.x - p->x) + (d.y - p->y) * (d.y - p->y));
}

double	cast_ray(t_cub *cub, t_precalc *meth, t_point *p, int angle)
{
	t_vector	ray;
	int			h;
	int			v;
	double		fishbowl_corr;
	int			angle_diff;

	ray.x = meth->coss[angle];
	ray.y = meth->sins[angle];
	angle_diff = angle - cub->player.direction;
	if (angle_diff < 0)
		angle_diff += 360;
	else if (angle_diff > 360)
		angle_diff -= 360;
	fishbowl_corr = meth->coss[angle_diff];
	if (!fishbowl_corr)
		fishbowl_corr = 1;
	h = find_horizontal_intersect(cub, p, &ray, meth->itans[angle]);
	v = find_vertical_intersect(cub, p, &ray, meth->tans[angle]);
	if(h < v)
		return (1 / (sqrt(h) * fishbowl_corr));
	return (1 / (sqrt(v) * fishbowl_corr));
}
