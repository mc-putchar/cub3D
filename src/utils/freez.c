/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freez.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:11:54 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/29 04:35:04 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(char **map, int size)
{
	while (size--)
		free(map[size]);
	free(map);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	scrap_scene(t_scene *scene)
{
	free(scene->walls[0]);
	free(scene->walls[1]);
	free(scene->walls[2]);
	free(scene->walls[3]);
	if (scene->map.height)
		free_map(scene->map.val, scene->map.height);
	return (1);
}

void	cleanup(t_cub *cub)
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
	(void)scrap_scene(cub->scene);
}
