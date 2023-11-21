/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:27:09 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/28 00:04:24 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	get_frame(t_animation *anim, t_mlx_image *tex, int idx)
{
	t_size const	size = anim->frame_x * BPP;
	int const		xoff = idx * anim->frame_x % tex->width;
	int const		yoff = idx * anim->frame_x / tex->width;
	int				j;

	j = 0;
	while (j < anim->frame_y)
	{
		(void)ft_memcpy(anim->frames[idx]->pixels + (j * anim->frame_x * BPP), \
			tex->pixels + (((yoff + j) * tex->width + xoff) * BPP), size);
		++j;
	}
}

static int	load_anim(t_cub *cub, t_sprite *spr)
{
	int	i;

	if (spr->anim->n_frames < 1)
		return (throw_error("Incorrect number of animation frames"));
	spr->anim->frames = malloc(spr->anim->n_frames * sizeof(t_mlx_image *));
	if (!spr->anim->frames)
		return (throw_error("Memory allocation failed"));
	i = 0;
	while (i < spr->anim->n_frames)
	{
		spr->anim->frames[i] = malloc(sizeof(t_mlx_image));
		if (img_gen(cub->mlx, spr->anim->frames[i], spr->anim->frame_x, spr->anim->frame_y))
			return (1); // TODO - destroy imgs and deallocate memory
		get_frame(spr->anim, spr->texture, i);
		++i;
	}
	mlx_destroy_image(cub->mlx, ((t_mlx_image *)spr->texture)->img);
	free(spr->texture);
	spr->texture = spr->anim->frames[0];
	spr->anim->current_frame = 0;
	spr->anim->iter = 0;
	spr->anim->delay = 10;
	return (0);
}

static int	load_sprites(t_cub *cub, t_scene *scene)
{
	t_sprite	*node;
	t_mlx_image	*img;
	char		*tmp;

	node = scene->sprites;
	while (node)
	{
		tmp = node->texture;
		img = malloc(sizeof(t_mlx_image));
		if (!img)
			return (throw_error("Memory allocation failed"));
		if (tex_load(cub->mlx, img, tmp))
			return (1);
		node->texture = img;
		free(tmp);
		if (node->anim && load_anim(cub, node))
			return (1);
		node->isloaded = 1;
		node = node->next;
	}
	return (0);
}

static int	load_extras(t_cub *cub, t_scene *scene)
{
	t_extra		*node;
	t_mlx_image	*img;
	char		*tmp;

	node = scene->extras;
	while (node)
	{
		tmp = node->value;
		img = malloc(sizeof(t_mlx_image));
		if (!img)
			return (throw_error("Memory allocation failed"));
		img->img = mlx_xpm_file_to_image(cub->mlx, tmp, \
					(int *)&img->width, (int *)&img->height);
		if (!img->img)
			return (throw_error("Failed to load texture"));
		img->pixels = mlx_get_data_addr(img->img, &img->bpp, \
					&img->size_line, &img->endian);
		if (!img->pixels)
			return (throw_error("MLX error"));
		node->value = img;
		free(tmp);
		node->isloaded = 1;
		node = node->next;
	}
	return (0);
}

int	load_textures(t_cub *cub, t_scene *scene)
{
	int	i;

	i = 4;
	while (i--)
	{
		cub->walls[i] = malloc(sizeof(t_mlx_image));
		if (!cub->walls[i])
			return (throw_error("Memory allocation failed"));
		cub->walls[i]->img = mlx_xpm_file_to_image(cub->mlx, scene->walls[i], \
			(int *)&cub->walls[i]->width, (int *)&cub->walls[i]->height);
		if (!cub->walls[i]->img)
			return (throw_error("Failed to load texture"));
		cub->walls[i]->pixels = mlx_get_data_addr(cub->walls[i]->img, \
			&cub->walls[i]->bpp, &cub->walls[i]->size_line, \
			&cub->walls[i]->endian);
		if (!cub->walls[i]->pixels)
			return (throw_error("MLX error"));
	}
	if (scene->sprites && load_sprites(cub, scene))
		return (1);
	if (scene->extras && load_extras(cub, scene))
		return (1);
	(void)ft_printf("Textures loaded\n");
	return (0);
}
