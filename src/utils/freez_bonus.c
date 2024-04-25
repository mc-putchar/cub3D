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
		mlx_destroy_image(cub->mlx, cub->canvas->img);
		free(cub->canvas);
	}
	if (cub->walls[0])
	{
		mlx_destroy_image(cub->mlx, cub->walls[0]->img);
		free(cub->walls[0]);
		mlx_destroy_image(cub->mlx, cub->walls[1]->img);
		free(cub->walls[1]);
		mlx_destroy_image(cub->mlx, cub->walls[2]->img);
		free(cub->walls[2]);
		mlx_destroy_image(cub->mlx, cub->walls[3]->img);
		free(cub->walls[3]);
	}
	if (!cub->scene)
		return ;
	if (cub->scene->extras)
		free_extras(cub, cub->scene->extras);
	(void)scrap_scene_bonus(cub->scene);
}
