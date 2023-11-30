/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 06:55:53 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/28 01:43:20 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * 011111110111111101111111
 */
static int	shade(int *buff, int side)
{
	int	color;

	color = *buff;
	if (side & 1)
		color = (color >> 1) & 8355711;
	return (color);
}

static t_mlx_image	*texture_lookup(t_cub *cub, int id)
{
	t_extra	*node;

	if (id < 4)
		return (cub->walls[id]);
	node = cub->scene->extras;
	while (node)
	{
		if (*(char *)node->key == id)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

/* Triple info
 * [0] side hit
 * [1] drawing column
 * [2] wall height
 */
static t_size	draw_wall(t_cub *cub, double wallx, int info[3], t_size pix)
{
	t_uint32		texx;
	t_uint32		texy;
	double			ppy;
	double			texpos;
	t_mlx_image		*tex;

	tex = texture_lookup(cub, info[0]);
	if (!tex)
		return (throw_error("Catastrophic failure"), close_hook(&cub));
	texx = (t_uint32)(wallx * tex->width);
	if (!info[0] || info[0] == 3)
		texx = tex->width - texx - 1;
	ppy = (double)tex->height / info[2];
	texpos = ((int)pix - (cub->camera->height >> 1) + (info[2] >> 1)) * ppy;
	while (info[2]--)
	{
		texy = (t_uint32)(texpos) * (tex->width) + texx;
		if (texy > tex->width * tex->height)
			texy = texx;
		texpos += ppy;
		put_pixel(cub->img, info[1], pix++, shade((int *)tex->pixels + \
		texy, info[0]));
	}
	return (pix);
}

/* Double wall
 * [0] wall distance
 * [1] wall x ratio
 */
static void	draw_strip(t_cub *cub, t_size i, double wall[2], int side)
{
	t_size	pix;
	t_size	wall_start;
	t_size	wall_height;
	int		info[3];

	wall_height = cub->camera->height;
	if (wall[0])
		wall_height /= wall[0];
	wall_start = (cub->camera->height >> 1) - (wall_height >> 1);
	if (wall[0] < 1)
		wall_start = 0;
	pix = 0;
	while (pix < wall_start)
		put_pixel(cub->img, i, pix++, cub->scene->ceiling);
	info[0] = side;
	info[1] = i;
	info[2] = wall_height;
	if (wall_height)
		pix = draw_wall(cub, wall[1], info, pix);
	while (pix < (cub->camera->height))
		put_pixel(cub->img, i, pix++, cub->scene->floor);
}

/* Single strip = single ray
 */
int	draw_screen(t_cub *cub)
{
	double	wall[2];
	int		side;
	t_size	strip;

	wall[0] = 0;
	strip = 0;
	while (strip < cub->camera->width)
	{
		side = raycaster(cub, strip, wall, wall + 1);
		draw_strip(cub, strip, wall, side);
		cub->zbuffer[strip++] = wall[0];
	}
	return (0);
}
