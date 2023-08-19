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

#define FOV			66
#define DOF			32
#define MAX_DIST	20 * MAP_SQUARE

double	vertical_check(t_cub *cub, int dir, t_point *pos)
{
	int	dist;
	int dy, dx;
	int	yo, xo;
	int	mx, my;
	double	tn;

	if (dir == 90 || dir == 270)
		return (MAX_DIST);
	dist = 0;
	tn = tan(angle_torad(dir));
	if (dir > 90 && dir < 270)
	{
		dx = ((pos->x >> MAP_BINDIV) << MAP_BINDIV) - 1;
		dy = pos->y - (pos->x - dx) * tn;
		xo = -MAP_SQUARE;
		yo = xo * tn;
	}
	if (dir < 90 || dir > 270)
	{
		dx = ((pos->x >> MAP_BINDIV) << MAP_BINDIV) + 1;
		dy = (dx - pos->x) * tn + pos->y;
		xo = MAP_SQUARE;
		yo = xo * tn;
	}
	while (dist++ < DOF)
	{
		mx = dx >> MAP_BINDIV;
		my = dy >> MAP_BINDIV;
		if (mx >= 0 && my >= 0 && mx < cub->map_width && my < cub->map_height && ft_isdigit(cub->map[my][mx]) && cub->map[my][mx] != '0')
			return (sqrt((pos->x - dx) * (pos->x - dx) + (pos->y - dy) * (pos->y - dy)));
		dx += xo;
		dy += yo;
	}
	return (MAX_DIST);
}

double	horizontal_check(t_cub *cub, int dir, t_point *pos)
{
	int	dist;
	int dy, dx;
	int	yo, xo;
	int	mx, my;
	double	tn;

	if (!dir || dir == 180)
		return (MAX_DIST);
	dist = 0;
	tn = 1 / tan(angle_torad(dir));
	if (dir > 180)
	{
		dy = ((pos->y >> MAP_BINDIV) << MAP_BINDIV) - 1;
		dx = pos->x - (pos->y - dy) * tn;
		yo = -MAP_SQUARE;
		xo = yo * tn;
	}
	if (dir < 180)
	{
		dy = ((pos->y >> MAP_BINDIV) << MAP_BINDIV) + MAP_SQUARE;
		dx = (dy - pos->y) * tn + pos->x;
		yo = MAP_SQUARE;
		xo = yo * tn;
	}
	while (dist++ < DOF)
	{
		mx = dx >> MAP_BINDIV;
		my = dy >> MAP_BINDIV;
		if (mx >= 0 && my >= 0 && mx < cub->map_width && my < cub->map_height && ft_isdigit(cub->map[my][mx]) && cub->map[my][mx] != '0')
			return (sqrt((pos->x - dx) * (pos->x - dx) + (pos->y - dy) * (pos->y - dy)));
		dx += xo;
		dy += yo;
	}
	return (MAX_DIST);
}

double	get_raylen(t_cub *cub, int dir, t_point *pos, unsigned char *shademask)
{
	double const	hdist = horizontal_check(cub, dir, pos);
	double const	vdist = vertical_check(cub, dir, pos);

	if (vdist && hdist)
	{
		if (vdist < hdist)
		{
			*shademask = 0xAA;
			return (vdist);
		}
		*shademask = 0xDD;
		return (hdist);
	}
	ft_printf("WARNING ray distance = 0\n");
	return (0);
}

void	cast_rays(t_cub *cub)
{
	t_vector		ray;
	int				raydir;
	t_point			rayend;
	double			raylen;
	int				rays;
	unsigned char	shademask;

	int const	rayscreenwidth = cub->img2->width / FOV;
	rays = FOV / 2 * -1;
	while (rays++ <= FOV / 2)
	{
		shademask = 0xFF;
		raydir = cub->player.direction + rays;
		if (raydir >= 360)
			raydir -= 360;
		if (raydir < 0)
			raydir += 360;
		raylen = get_raylen(cub, raydir, &cub->player.position, &shademask);
		if (rays > 0)
			raylen *= cub->meth.coss[-rays + 360];
		else
			raylen *= cub->meth.coss[-rays];
		draw_scene(cub, raylen, rayscreenwidth * (rays + FOV / 2), rayscreenwidth, shademask);
		ray.x = cub->meth.coss[raydir] * raylen;
		ray.y = cub->meth.sins[raydir] * raylen;
		rayend.x = cub->player.position.x + ray.x;
		rayend.y = cub->player.position.y + ray.y;
		rayend.color = 0x00FF00FF;
		draw_line(cub->img, &cub->player.position, &rayend);
	}
}
