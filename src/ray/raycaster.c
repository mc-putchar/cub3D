/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:20:37 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/17 20:20:37 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	params(t_player *player, t_ray *ray)
{
	ray->delta.x = 1e28;
	ray->delta.y = 1e28;
	if (ray->direction.x < 0)
	{
		ray->delta.x = -1 / ray->direction.x;
		ray->stepx = -1;
		ray->distance.x = ray->delta.x * (player->position.x - (int)player->position.x);
	}
	else
	{
		if (ray->direction.x)
			ray->delta.x = 1 / ray->direction.x;
		ray->stepx = 1;
		ray->distance.x = ray->delta.x * ((int)player->position.x - player->position.x + 1);
	}
	if (ray->direction.y < 0)
	{
		ray->delta.y = -1 / ray->direction.y;
		ray->stepy = -1;
		ray->distance.y = ray->delta.y * (player->position.y - (int)player->position.y);
	}
	else
	{
		if (ray->direction.y)
			ray->delta.y = 1 / ray->direction.y;
		ray->stepy = 1;
		ray->distance.y = ray->delta.y * ((int)player->position.y - player->position.y + 1);
	}
}

static int	wall_check(t_map *map, int x, int y)
{
	if (x < 0 || (t_size)x > map->width - 1 || \
		y < 0 || (t_size)y > map->height - 1)
		return (-1);
	if (map->val[y][x] == '1')
		return (1);
	return (0);
}

static double	dda(t_player *player, t_map *map, t_ray *ray, int *side)
{
	int			mapx;
	int			mapy;
	double		dist;
	int			hit;

	params(player, ray);
	mapx = (int)player->position.x;
	mapy = (int)player->position.y;
	hit = wall_check(map, mapx, mapy);
	while(!hit)
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
	if (hit < 0)
		return (-1);
	if (*side & 1)
		dist = ray->distance.y - ray->delta.y;
	else
		dist = ray->distance.x - ray->delta.x;
	return (dist);
}

int	raycaster(t_cub *cub, t_size i, double *dist)
{
	double		camx;
	t_ray		ray;
	int			side;

	side = -1;
	camx = (i << 1) / (double)cub->camera->width - 1;
	ray.direction.x = cub->player->direction.x + cub->camera->plane.x * camx;
	ray.direction.y = cub->player->direction.y + cub->camera->plane.y * camx;
	*dist = dda(cub->player, &cub->scene->map, &ray, &side);
	return (side);
}
