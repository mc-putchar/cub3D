/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freez_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 02:52:20 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/20 02:52:20 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

void	free_extras(t_cub *cub, t_extra *ex)
{
	t_extra	*tmp;

	while (ex)
	{
		tmp = ex;
		ex = ex->next;
		free(tmp->key);
		if (tmp->isloaded)
			mlx_destroy_image(cub->mlx, ((t_mlx_image *)tmp->value)->img);
		free(tmp->value);
		free(tmp);
	}
}

void	free_sprites(t_cub *cub, t_sprite *spr)
{
	t_sprite	*tmp;

	while (spr)
	{
		tmp = spr;
		spr = spr->next;
		if (tmp->tag)
			free(tmp->tag);
		if (tmp->isloaded)
			mlx_destroy_image(cub->mlx, ((t_mlx_image *)tmp->texture)->img);
		free(tmp->texture);
		free(tmp);
	}
	if (((t_bonus_data *)cub->bonus)->sprite_arr)
		free(((t_bonus_data *)cub->bonus)->sprite_arr);
}

int	scrap_scene_bonus(t_scene *scene)
{
	free(scene->walls[0]);
	free(scene->walls[1]);
	free(scene->walls[2]);
	free(scene->walls[3]);
	if (scene->map.height)
		free_map(scene->map.val, scene->map.height);
	free(scene);
	return (1);
}

void	cleanup_bonus(t_cub *cub)
{
	if (cub->camera->zbuff)
		free(cub->camera->zbuff);
	if (cub->canvas)
	{
		shred_image(cub->mlx, cub->canvas);
	}
	if (cub->walls[0])
	{
		shred_image(cub->mlx, cub->walls[0]);
		shred_image(cub->mlx, cub->walls[1]);
		shred_image(cub->mlx, cub->walls[2]);
		shred_image(cub->mlx, cub->walls[3]);
	}
	if (!cub->scene)
		return ;
	if (cub->scene->extras)
		free_extras(cub, cub->scene->extras);
	if (cub->scene->sprites)
		free_sprites(cub, cub->scene->sprites);
	(void)scrap_scene_bonus(cub->scene);
}
