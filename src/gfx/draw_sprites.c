/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:36:31 by mcutura           #+#    #+#             */
/*   Updated: 2024/05/02 20:29:28 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

static t_vector	transform(t_sprite *spr, t_vector *plane, t_player *player);
static void		calc_sprite_x(t_sprite *spr, t_sprite_data *data, \
				t_camera *cam, t_vector *xform);
static void		calc_sprite_y(t_sprite *spr, t_sprite_data *data, size_t h, \
				t_vector *xform);
static void		draw_sprite(t_cub *cub, t_sprite *sprite, t_sprite_data *d, double ty);


int	cast_sprites(t_cub *cub, t_sprite **arr, t_player *pl)
{
	t_vector		xform;
	t_vector		p;
	int				i;
	t_sprite_data	data;

	i = -1;
	while (++i < cub->scene->n_sprites)
	{
		p = arr[i]->position;
		arr[i]->dist = (pl->position.x - p.x) * (pl->position.x - p.x);
		arr[i]->dist += (pl->position.y - p.y) * (pl->position.y - p.y);
	}
	quicksort(arr, cub->scene->n_sprites);
	while (i--)
	{
		xform = transform(arr[i], &cub->camera->plane, pl);
		data.screenx = (int)(cub->camera->width / 2 * (1 + xform.x / xform.y));
		data.zoffset = arr[i]->z_offset / xform.y;
		calc_sprite_y(arr[i], &data, cub->camera->height, &xform);
		calc_sprite_x(arr[i], &data, cub->camera, &xform);
		draw_sprite(cub, arr[i], &data, xform.y);
	}
	return (0);
}

t_vector	transform(t_sprite *spr, t_vector *plane, t_player *player)
{
	t_vector const	ppos = player->position;
	t_vector const	dir = player->direction;
	t_vector		xform;
	t_vector		spr_pos;
	double			inv_deter;

	spr_pos.x = spr->position.x - ppos.x;
	spr_pos.y = spr->position.y - ppos.y;
	inv_deter = 1.0 / (plane->x * dir.y - dir.x * plane->y);
	xform.x = (dir.y * spr_pos.x - dir.x * spr_pos.y) * inv_deter;
	xform.y = (-plane->y * spr_pos.x + plane->x * spr_pos.y) * inv_deter;
	return (xform);
}

void	calc_sprite_y(t_sprite *spr, t_sprite_data *data, size_t h, \
	t_vector *xform)
{
	data->dimension.y = spr->scale.y * h;
	if (data->dimension.y < 0)
		data->dimension.y = -data->dimension.y;
	if (xform->y)
		data->dimension.y /= xform->y;
	data->start.y = (-data->dimension.y >> 1) + (h >> 1) + data->zoffset;
	if (data->start.y < 0)
		data->start.y = 0;
	data->end.y = (data->dimension.y >> 1) + (h >> 1) + data->zoffset;
	if (data->end.y >= (int)h)
		data->end.y = h - 1;
}

void	calc_sprite_x(t_sprite *spr, t_sprite_data *data, t_camera *cam, \
	t_vector *xform)
{
	data->dimension.x = spr->scale.x * cam->height;
	if (data->dimension.x < 0)
		data->dimension.x = -data->dimension.x;
	if (xform->y)
		data->dimension.x /= xform->y;
	data->start.x = data->screenx - (data->dimension.x >> 1);
	if (data->start.x < 0)
		data->start.x = 0;
	data->end.x = data->screenx + (data->dimension.x >> 1);
	if (data->end.x >= (int)cam->width)
		data->end.x = cam->width - 1;
}

/* ts[]	0 = tex x,	1 = tex y,
 * 		2 = dy,		3 = d;
 */
void	draw_sprite(t_cub *cub, t_sprite *sprite, t_sprite_data *d, double ty)
{
	int			ts[4];
	t_mlx_image	*tex;
	int			col;

	tex = sprite->texture;
	while (d->start.x < d->end.x)
	{
		ts[0] = (int)(((d->start.x - (-d->dimension.x / 2 + d->screenx)) << 8) \
			* tex->width / d->dimension.x) >> 8;
		if (d->start.x < (int)cub->camera->width && d->start.x > 0 && \
			ty > 0 && ty < cub->camera->zbuff[d->start.x])
		{
			ts[2] = d->start.y;
			while (ts[2]++ < d->end.y - 1)
			{
				ts[3] = ((ts[2] - d->zoffset) << 8) - \
					(cub->camera->height << 7) + (d->dimension.y << 7);
				ts[1] = ((ts[3] * tex->height) / d->dimension.y) >> 8;
				col = ((int *)tex->pixels)[tex->width * ts[1] + ts[0]];
				if (!(col >> 24))
					put_pixel(cub->canvas, d->start.x, ts[2], col);
			}
		}
		++d->start.x;
	}
}
