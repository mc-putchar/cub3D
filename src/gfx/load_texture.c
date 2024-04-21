/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:15:15 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/20 18:06:52 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_texture(void *mlx, t_mlx_image *img, char *path)
{
	img->img = mlx_xpm_file_to_image(mlx, path, \
		(int *)&img->width, (int *)&img->height);
	if (!img->img)
		return (throw_error(TEXTURE_ERROR));
	img->pixels = mlx_get_data_addr(img->img, &img->bpp, \
		&img->size_line, &img->endian);
	if (!img->pixels)
		return (throw_error(MLX_ERROR));
	return (0);
}

int	load_scene_textures(t_cub *cub)
{
	int				i;

	i = 0;
	while (i < 4)
	{
		cub->walls[i] = malloc(sizeof(t_mlx_image));
		if (!cub->walls[i])
		{
			while (i)
			{
				mlx_destroy_image(cub->mlx, cub->walls[--i]->img);
				free(cub->walls[i]);
				cub->walls[i] = NULL;
			}
			return (throw_error(MALLOC_FAIL));
		}
		if (load_texture(cub->mlx, cub->walls[i], cub->scene->walls[i]))
		{
			free(cub->walls[i]);
			while (i)
			{
				mlx_destroy_image(cub->mlx, cub->walls[--i]->img);
				free(cub->walls[i]);
				cub->walls[i] = NULL;
			}
			return (1);
		}
		++i;
	}
	return (0);
}

int	load_extras(t_cub *cub)
{
	t_extra		*ex;
	t_mlx_image	*texture;

	ex = cub->scene->extras;
	while (ex)
	{
		if (!ex->isloaded)
		{
			texture = malloc(sizeof(t_mlx_image));
			if (!texture)
				return (throw_error(MALLOC_FAIL));
			if (load_texture(cub->mlx, texture, ex->value))
				return ((free(texture), 1));
			free(ex->value);
			ex->value = texture;
			ex->isloaded = 1;
		}
		ex = ex->next;
	}
	return (0);
}
