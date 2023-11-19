/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:51:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/28 02:42:23 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static t_vector	transform_sprite(t_sprite *spr, t_vector *ppos, \
	t_vector *plane, t_vector *dir)
{
	t_vector	xform;
	t_vector	spr_pos;
	double		inv_deter;

	spr_pos.x = spr->position.x - ppos->x;
	spr_pos.y = spr->position.y - ppos->y;
	inv_deter = 1.0 / (plane->x * dir->y - dir->x * plane->y);
	xform.x = (dir->y * spr_pos.x - dir->x * spr_pos.y) * inv_deter;
	xform.y = (-plane->y * spr_pos.x + plane->x * spr_pos.y) * inv_deter;
	return (xform);
}

static void	calc_sprite_y(t_sprite *spr, t_sprite_data *data, t_size h, \
	t_vector *xform)
{
	data->height = (int)h >> spr->vdiv;
	if (data->height < 0)
		data->height = -data->height;
	if (xform->y)
		data->height /= xform->y;
	data->start_y = (-data->height >> 1) + (h >> 1) + data->zoffset;
	if (data->start_y < 0)
		data->start_y = 0;
	data->end_y = (data->height >> 1) + (h >> 1) + data->zoffset;
	if (data->end_y >= (int)h)
		data->end_y = h - 1;
}

static void	calc_sprite_x(t_sprite *spr, t_sprite_data *data, t_camera *cam, \
	t_vector *xform)
{
	data->width = (int)(cam->height) >> spr->hdiv;
	if (data->width < 0)
		data->width = -data->width;
	if (xform->y)
		data->width /= xform->y;
	data->start_x = data->screenx - (data->width >> 1);
	if (data->start_x < 0)
		data->start_x = 0;
	data->end_x = data->screenx + (data->width >> 1);
	if (data->end_x >= (int)cam->width)
		data->end_x = cam->width - 1;
}

/* ts[]	0 = tex x,	1 = tex y,
 * 		2 = dy,		3 = d;
 */
static void	draw_sprite(t_cub *cub, t_sprite *sprite, t_sprite_data *d, \
	double ty)
{
	int			ts[4];
	t_mlx_image	*tex;
	int			col;

	tex = sprite->texture;
	while (d->start_x < d->end_x)
	{
		ts[0] = (int)(256 * (d->start_x - (-d->width / 2 + d->screenx)) * \
			tex->width / d->width) >> 8;
		if (d->start_x < (int)cub->camera->width && d->start_x > 0 && \
			ty > 0 && ty < cub->zbuffer[d->start_x])
		{
			ts[2] = d->start_y;
			while (ts[2]++ < d->end_y - 1)
			{
				ts[3] = ((ts[2] - d->zoffset) << 8) - \
					(cub->camera->height << 7) + (d->height << 7);
				ts[1] = ((ts[3] * tex->height) / d->height) >> 8;
				col = ((int *)tex->pixels)[tex->width * ts[1] + ts[0]];
				if (!(col >> 24))
					put_pixel(cub->img, d->start_x, ts[2], col);
			}
		}
		++d->start_x;
	}
}

int	cast_sprites(t_cub *cub, t_player *pl, t_scene *scn)
{
	t_vector		xform;
	t_sprite_data	data;
	t_size			i;
	t_vector		*p;

	i = 0;
	while (i < scn->n_sprites)
	{
		p = &scn->spr_arr[i]->position;
		scn->spr_arr[i]->dist = (pl->position.x - p->x) * (pl->position.x - \
		p->x) + (pl->position.y - p->y) * (pl->position.y - p->y);
		++i;
	}
	quicksort(scn->spr_arr, scn->n_sprites);
	while (i--)
	{
		xform = transform_sprite(scn->spr_arr[i], \
		&pl->position, &cub->camera->plane, &pl->direction);
		data.screenx = (int)(cub->camera->width / 2 * (1 + xform.x / xform.y));
		data.zoffset = scn->spr_arr[i]->z / xform.y;
		calc_sprite_y(scn->spr_arr[i], &data, cub->camera->height, &xform);
		calc_sprite_x(scn->spr_arr[i], &data, cub->camera, &xform);
		draw_sprite(cub, scn->spr_arr[i], &data, xform.y);
	}
	return (0);
}
