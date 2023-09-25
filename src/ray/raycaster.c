/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:20:37 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 07:37:29 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	params(t_vector position, t_ray *ray)
{
	if (ray->direction.x < 0)
	{
		ray->delta.x = -1 / ray->direction.x;
		ray->stepx = -1;
		ray->distance.x = (position.x - (int)position.x) * ray->delta.x;
	}
	else
	{
		if (ray->direction.x)
			ray->delta.x = 1 / ray->direction.x;
		ray->stepx = 1;
		ray->distance.x = ((int)position.x - position.x + 1) * ray->delta.x;
	}
	if (ray->direction.y < 0)
	{
		ray->delta.y = -1 / ray->direction.y;
		ray->stepy = -1;
		ray->distance.y = (position.y - (int)position.y) * ray->delta.y;
		return ;
	}
	if (ray->direction.y)
		ray->delta.y = 1 / ray->direction.y;
	ray->stepy = 1;
	ray->distance.y = ((int)position.y - position.y + 1) * ray->delta.y;
}

static double	get_wallx(t_ray *ray, t_vector *pos, int side)
{
	double		wallx;

	if (side & 1)
		wallx = (ray->distance.y - ray->delta.y) * ray->direction.x + pos->x;
	else
		wallx = (ray->distance.x - ray->delta.x) * ray->direction.y + pos->y;
	return (wallx - (int)wallx);
}

/* dd[0] = side hit
 * dd[1] = hit what?
 */
static double	dda(t_player *player, t_map *map, t_ray *ray, int dd[2])
{
	int			mapx;
	int			mapy;

	mapx = (int)player->position.x;
	mapy = (int)player->position.y;
	while (!dd[1])
	{
		if (ray->distance.x < ray->distance.y)
		{
			ray->distance.x += ray->delta.x;
			mapx += ray->stepx;
			dd[0] = 1 + ray->stepx;
		}
		else
		{
			ray->distance.y += ray->delta.y;
			mapy += ray->stepy;
			dd[0] = 2 + ray->stepy;
		}
		dd[1] = wall_check(map, mapx, mapy);
	}
	return (get_wallx(ray, &player->position, dd[0]));
}

int	raycaster(t_cub *cub, t_size i, double *dist, double *wallx)
{
	double		camx;
	t_ray		ray;
	int			side_hit[2];

	side_hit[0] = -1;
	side_hit[1] = 0;
	camx = (i << 1) / (double)cub->camera->width - 1;
	ray.direction.x = cub->player->direction.x + cub->camera->plane.x * camx;
	ray.direction.y = cub->player->direction.y + cub->camera->plane.y * camx;
	ray.delta.x = 1e28;
	ray.delta.y = 1e28;
	params(cub->player->position, &ray);
	*wallx = dda(cub->player, &cub->scene->map, &ray, side_hit);
	if (side_hit[0] & 1)
		*dist = ray.distance.y - ray.delta.y;
	else
		*dist = ray.distance.x - ray.delta.x;
	if (side_hit[1] != '1')
		return (side_hit[1]);
	return (side_hit[0]);
}
