/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 06:55:53 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/24 07:30:54 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define WALL	640
#define DEPTH	640

// // ABGR? to RGBA
// static int	get_tex_pix(t_mlx_texture *tex, uint32_t x, uint32_t y)
// {
// 	int32_t	*pix;

// 	if (y >= tex->height)
// 		y %= tex->height;
// 	pix = (int32_t *)(tex->pixels + ((y * tex->width + x) << 2));
// 	return (*pix);
// }

/* Triple info
 * [0] side hit
 * [1] drawing column
 * [2] wall height
 */
static t_size	draw_wall(t_cub *cub, double wallx, int info[3], t_size pix)
{
	t_mlx_image		*tex;
	t_uint32		xoff;
	t_uint32		ppy;
	t_uint32		y;

	tex = cub->walls[info[0]];
	xoff = (t_uint32)(wallx * tex->width);
	ppy = (info[2] / tex->height);
	if (!ppy)
		++ppy;
	y = 0;
	while (info[2]--)
	{
		put_pixel(cub->img, info[1], pix++, *(int *)(tex->pixels + (((y % tex->height) * tex->width + xoff) << 2)));
		y += ppy;
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
	int		wall_height;
	t_size	wall_start;
	int		info[3];

	wall_height = WALL;
	if (wall[0] < 0)
		wall_height = 0;
	if (wall[0])
		wall_height /= wall[0];
	if ((t_uint32)wall_height > cub->img->height)
		wall_height = cub->img->height;
	wall_start = (cub->camera->height >> 1) - (wall_height >> 1);
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
		++strip;
	}
	return (0);
}
