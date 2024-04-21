/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:29:24 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 03:10:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_mlx_image	*select_texture(t_cub *cub, t_ray *ray);
static uint32_t		texture_x_offset(t_mlx_image *tex, t_ray *ray);
static void			draw_wall(t_mlx_image *tex, t_mlx_image *canv, \
					t_ray *ray, t_point *xy);
static int			close_wall(t_mlx_image *tex, t_mlx_image *canv, \
					t_ray *ray, t_point *xy);

/*
 * 011111110111111101111111
 */
static inline int	shade(int color, int side)
{
	if (side & 1)
		color = (color >> 1) & 8355711;
	return (color);
}

void	render_scene(t_cub *cub, t_mlx_image *canvas)
{
	t_point		xy;
	t_ray		ray;
	uint32_t	wall_height;

	xy.x = 0;
	while (xy.x < canvas->width)
	{
		xy.y = 0;
		cast_ray(cub, &ray, xy.x);
		if (ray.hit == -1 && ++xy.x)
			continue ;
		if (ray.wall_dist < 1 \
		&& close_wall(select_texture(cub, &ray), canvas, &ray, &xy))
			continue ;
		wall_height = canvas->height / ray.wall_dist;
		while (xy.y < (canvas->height >> 1) - (wall_height >> 1))
			put_pixel(canvas, xy.x, xy.y++, cub->scene->ceiling);
		draw_wall(select_texture(cub, &ray), canvas, &ray, &xy);
		while (xy.y < canvas->height)
			put_pixel(canvas, xy.x, xy.y++, cub->scene->floor);
		++xy.x;
	}
}

t_mlx_image	*select_texture(t_cub *cub, t_ray *ray)
{
	t_extra	*ex;

	if (ray->hit == '1')
		return (cub->walls[ray->side]);
	ex = cub->scene->extras;
	while (ex)
	{
		if (*ex->key == ray->hit)
			return (ex->value);
		ex = ex->next;
	}
	return (NULL);
}

void	draw_wall(t_mlx_image *tex, t_mlx_image *canv, t_ray *ray, t_point *xy)
{
	uint32_t const	texx = texture_x_offset(tex, ray);
	double const	ppy = (double)tex->height / (((canv->height >> 1) - xy->y) << 1);
	uint32_t		h;
	uint32_t		texoff;

	h = 0;
	while (h < (((canv->height >> 1) - xy->y) << 1))
	{
		texoff = ((uint32_t)(ppy * h)) * tex->width + texx;
		put_pixel(canv, xy->x, xy->y + h++, ((int *)tex->pixels)[texoff]);
	}
	xy->y += h;
}

int	close_wall(t_mlx_image *tex, t_mlx_image *canv, t_ray *ray, t_point *xy)
{
	uint32_t const	texx = texture_x_offset(tex, ray);
	double const	ppy = ray->wall_dist * tex->height / canv->height;
	double			texi;
	uint32_t		texoff;

	texi = (uint32_t)(ppy * canv->height * (1 - ray->wall_dist)) * tex->width;
	while (xy->y < canv->height)
	{
		texoff = (uint32_t)(ppy * xy->y) * tex->width + texx + texi;
		put_pixel(canv, xy->x, xy->y, ((int *)tex->pixels)[texoff]);
		++xy->y;
	}
	return (++xy->x);
}

uint32_t	texture_x_offset(t_mlx_image *tex, t_ray *ray)
{
	uint32_t	texx;

	texx = (uint32_t)(ray->wallx * (double)tex->width);
	if (!ray->side || ray->side == 3)
		texx = tex->width - texx - 1;
	return (texx);
}
