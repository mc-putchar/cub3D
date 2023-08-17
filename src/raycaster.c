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
#define DOF		16

void	cast_rays(t_cub *cub)
{
	int			rays;
	double		ray_angle;
	float		atn;
	t_pointf	offset;
	t_pointf	ray;
	t_point		ray_end;
	int			dof;
	t_point		map;

	rays = 10;
	while (rays--)
	{
		dof = 0;
		ray_angle = cub->player.direction + 0.1 * rays;
		atn = atan(ray_angle);
		if (ray_angle < M_PI)
		{
			ray.y = (((cub->player.position.y) >> MAP_BINDIV) << MAP_BINDIV) + MAP_SQUARE;
			ray.x = (cub->player.position.y - ray.y) * atn + cub->player.position.x;
			offset.y = MAP_SQUARE * -1;
			offset.x = -offset.y * atn;
		}
		if (ray_angle > M_PI)
		{
			ray.y = (((cub->player.position.y) >> MAP_BINDIV) << MAP_BINDIV) - 0.0001;
			ray.x = (cub->player.position.y - ray.y) * atn + cub->player.position.x;
			offset.y = MAP_SQUARE;
			offset.x = -offset.y * atn;
		}
		if (ray_angle == 0 || ray_angle == M_PI)
		{
			ray.x = cub->player.position.x;
			ray.y = cub->player.position.y;
			dof = DOF;
		}
		while (dof < DOF)
		{
			map.x = (int)ray.x >> MAP_BINDIV;
			map.y = (int)ray.y >> MAP_BINDIV;
			if (map.x < cub->map_width && map.y < cub->map_height && ft_isdigit(cub->map[map.y][map.x]) && cub->map[map.y][map.x] != '0')
				dof = DOF;
			else
			{
				ray.x += offset.x;
				ray.y += offset.y;
				++dof;
			}
		}
		ray_end.x = ray.x;
		ray_end.y = ray.y;
		ray_end.color = 0x00FF00FF;
		draw_line(cub->img, &cub->player.position, &ray_end);
	}
}
