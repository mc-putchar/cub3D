/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:20:37 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/24 21:48:16 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	params(t_vector position, t_ray *ray)
{
	if (ray->direction.x < 0)
	{
		ray->delta.x = -1 / ray->direction.x;
		ray->stepx = -1;
		ray->distance.x = ray->delta.x * (position.x - (int)position.x);
	}
	else
	{
		if (ray->direction.x)
			ray->delta.x = 1 / ray->direction.x;
		ray->stepx = 1;
		ray->distance.x = ray->delta.x * ((int)position.x - position.x + 1);
	}
	if (ray->direction.y < 0)
	{
		ray->delta.y = -1 / ray->direction.y;
		ray->stepy = -1;
		ray->distance.y = ray->delta.y * (position.y - (int)position.y);
		return ;
	}
	if (ray->direction.y)
		ray->delta.y = 1 / ray->direction.y;
	ray->stepy = 1;
	ray->distance.y = ray->delta.y * ((int)position.y - position.y + 1);
}

static double	get_wallx(t_ray *ray, int side)
{
	double		wallx;

	if (side & 1)
		wallx = ray->distance.y;
	else
		wallx = ray->distance.x;
	return (wallx - (int)wallx);
}

static double	dda(t_player *player, t_map *map, t_ray *ray, int *side)
{
	int			mapx;
	int			mapy;
	int			hit;

	mapx = (int)player->position.x;
	mapy = (int)player->position.y;
	hit = 0;
	while (!hit)
	{
		if (ray->distance.x + ray->delta.x < ray->distance.y + ray->delta.y)
		{
			ray->distance.x += ray->delta.x;
			mapx += ray->stepx;
			*side = 1 + ray->stepx;
		}
		else
		{
			ray->distance.y += ray->delta.y;
			mapy += ray->stepy;
			*side = 2 + ray->stepy;
		}
		hit = wall_check(map, mapx, mapy);
	}
	return (get_wallx(ray, *side));
}

int	raycaster(t_cub *cub, t_size i, double *dist, double *wallx)
{
	double		camx;
	t_ray		ray;
	int			side;

	side = -1;
	camx = (i << 1) / (double)cub->camera->width - 1;
	ray.direction.x = cub->player->direction.x + cub->camera->plane.x * camx;
	ray.direction.y = cub->player->direction.y + cub->camera->plane.y * camx;
	ray.delta.x = 1e28;
	ray.delta.y = 1e28;
	params(cub->player->position, &ray);
	*wallx = dda(cub->player, &cub->scene->map, &ray, &side);
	if (side & 1)
		*dist = ray.distance.y;
	else
		*dist = ray.distance.x;
	return (side);
}
