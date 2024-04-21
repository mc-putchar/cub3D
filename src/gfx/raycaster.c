/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:34:38 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 07:17:09 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		dda(t_vector *origin, t_map *map, t_ray *ray);
static double	get_wallx(t_ray *ray, t_vector *pos);
static int		wall_check(t_map *map, int x, int y);

void	cast_ray(t_cub *cub, t_ray *ray, size_t n)
{
	double const	cam_x = (n << 1) / (double)cub->camera->width - 1;

	ray->direction.x = cub->player->direction.x + cub->camera->plane.x * cam_x;
	ray->direction.y = cub->player->direction.y + cub->camera->plane.y * cam_x;
	if (ray->direction.x)
		ray->delta.x = fabs(1 / ray->direction.x);
	else
		ray->delta.x = 1e30;
	if (ray->direction.y)
		ray->delta.y = fabs(1 / ray->direction.y);
	else
		ray->delta.y = 1e30;
	ray->stepx = 1 - 2 * (ray->direction.x < 0);
	ray->stepy = 1 - 2 * (ray->direction.y < 0);
	ray->distance.x = cub->player->position.x - (int)cub->player->position.x;
	if (ray->direction.x < 0)
		ray->distance.x *= ray->delta.x;
	else
		ray->distance.x = (1 - ray->distance.x) * ray->delta.x;
	ray->distance.y = cub->player->position.y - (int)cub->player->position.y;
	if (ray->direction.y < 0)
		ray->distance.y *= ray->delta.y;
	else
		ray->distance.y = (1 - ray->distance.y) * ray->delta.y;
	dda(&cub->player->position, &cub->scene->map, ray);
}

void	dda(t_vector *origin, t_map *map, t_ray *ray)
{
	int	mapx;
	int	mapy;

	mapx = (int)origin->x;
	mapy = (int)origin->y;
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->distance.x < ray->distance.y)
		{
			ray->distance.x += ray->delta.x;
			mapx += ray->stepx;
			ray->side = 1 + ray->stepx;
		}
		else
		{
			ray->distance.y += ray->delta.y;
			mapy += ray->stepy;
			ray->side = 2 + ray->stepy;
		}
		ray->hit = wall_check(map, mapx, mapy);
	}
	ray->wallx = get_wallx(ray, origin);
}

int	wall_check(t_map *map, int x, int y)
{
	if (x < 0 || (size_t)x >= map->width \
	|| y < 0 || (size_t)y >= map->height)
		return (-1);
	if (map->val[y][x] == '0' || map->val[y][x] == 'O')
		return (0);
	return (map->val[y][x]);
}

double	get_wallx(t_ray *ray, t_vector *pos)
{
	double	wallx;

	if (ray->side & 1)
	{
		wallx = (ray->distance.y - ray->delta.y) * ray->direction.x + pos->x;
		ray->wall_dist = ray->distance.y - ray->delta.y;
	}
	else
	{
		wallx = (ray->distance.x - ray->delta.x) * ray->direction.y + pos->y;
		ray->wall_dist = ray->distance.x - ray->delta.x;
	}
	return (wallx - (int)wallx);
}
