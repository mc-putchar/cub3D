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

/*
Projection plane:
640 x 480
FOV = 64deg
CENTER (320, 240)
DISTANCE = 554
wallH = MAP_SQUARE * DISTANCE * 1 / sqrt(wall_d^2)
WALL_MULTI = DISTANCE << MAP_BINDIV
wallH = WALL_MULTI * 1 / sqrt(wall_d^2)
wall_d = ft_abs(p.x - d.x) / cos(a) ?
*/

void	raycaster(t_cub *cub)
{
	int		r;
	int		angle;
	double	scale;

	r = -1;
	while (++r <= cub->plane.fov)
	{
		angle = cub->player.direction + r - (cub->plane.fov >> 1);
		if (angle < 0)
			angle += 360;
		else if (angle > 360)
			angle -= 360;
		scale = cast_ray(cub, &cub->meth, &cub->player.position, angle);
		draw_column(cub->img2, r * cub->plane.ray_width, \
			scale * cub->plane.wall_multi, cub->plane.ray_width);
	}
}

// void	cast_rays(t_cub *cub)
// {
// 	t_vector		ray;
// 	int				raydir;
// 	t_point			rayend;
// 	double			raylen;
// 	int				rays;
// 	unsigned char	shademask;

// 	int const	rayscreenwidth = cub->img2->width / FOV;
// 	rays = FOV / 2 * -1;
// 	while (rays++ <= FOV / 2)
// 	{
// 		shademask = 0xFF;
// 		raydir = cub->player.direction + rays;
// 		if (raydir >= 360)
// 			raydir -= 360;
// 		if (raydir < 0)
// 			raydir += 360;
// 		raylen = get_raylen(cub, raydir, &cub->player.position, &shademask);
// 		if (rays > 0)
// 			raylen *= cub->meth.coss[-rays + 360];
// 		else
// 			raylen *= cub->meth.coss[-rays];
// 		draw_scene(cub, raylen, rayscreenwidth * (rays + FOV / 2), rayscreenwidth, shademask);
// 		ray.x = cub->meth.coss[raydir] * raylen;
// 		ray.y = cub->meth.sins[raydir] * raylen;
// 		rayend.x = cub->player.position.x + ray.x;
// 		rayend.y = cub->player.position.y + ray.y;
// 		rayend.color = 0x00FF00FF;
// 		draw_line(cub->img, &cub->player.position, &rayend);
// 	}
// }
