/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 01:06:40 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/17 01:06:40 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define FOV		66
#define DOF		24

double	get_raylen(t_cub *cub, int dir, t_point *pos)
{
	int	dist;
	double dy, dx;
	int	yo, xo;
	int	mx, my;
	double	tn;

	if (dir == 0 || dir == 180)
		return (0);
	dist = 0;
	tn = tan(angle_torad(dir));
	if (dir > 180)
	{
		dy = (((int)pos->y >> MAP_BINDIV) << MAP_BINDIV) - 0.0001;
		dx = (pos->y - dy) * tn + pos->x;
		yo = MAP_SQUARE * -1;
		xo = yo * tn;
	}
	if (dir < 180)
	{
		dy = (((int)pos->y >> MAP_BINDIV) << MAP_BINDIV) + MAP_SQUARE;
		dx = (pos->y - dy) * tn + pos->x;
		yo = MAP_SQUARE;
		xo = yo * tn;
	}
	while (dist < DOF)
	{
		mx = (int)dx >> MAP_BINDIV;
		my = (int)dy >> MAP_BINDIV;
		if (mx > 0 && my > 0 && mx < cub->map_width && my < cub->map_height && ft_isdigit(cub->map[my][mx]) && cub->map[my][mx] != '0')
			return (sqrt((pos->x - dx) * (pos->x - dx) + (pos->y - dy) * (pos->y - dy)));
		dx += xo;
		dy += yo;
		++dist;
	}
	return (0);
}

void	cast_rays(t_cub *cub)
{
	t_vector	ray;
	int			raydir;
	t_point		rayend;
	double		raylen;
	int			rays;

	rays = -1 * FOV / 2;
	while (rays++ <= FOV / 2)
	{
		raydir = cub->player.direction + rays;
		if (raydir >= 360)
			raydir -= 360;
		if (raydir < 0)
			raydir += 360;
		ray.x = cub->meth.coss[raydir];
		ray.y = cub->meth.sins[raydir];
		raylen = get_raylen(cub, raydir, &cub->player.position);
		rayend.x = cub->player.position.x + ray.x * raylen;
		rayend.y = cub->player.position.y + ray.y * raylen;
		rayend.color = 0x00FF00FF;
		draw_line(cub->img, &cub->player.position, &rayend);
	}
}
