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

void	free_extras(void *mlx, t_scene *scene)
{
	t_extra		*next;
	t_mlx_image	*img;

	while (scene->extras)
	{
		next = scene->extras->next;
		free(scene->extras->key);
		img = scene->extras->value;
		mlx_destroy_image(mlx, img->img);
		free(scene->extras->value);
		free(scene->extras);
		scene->extras = next;
	}
}

void	free_scene(void *mlx, t_scene *scene)
{
	int			i;
	t_sprite	*next;
	t_mlx_image	*img;

	i = 0;
	while (i < 4)
		free(scene->walls[i++]);
	if (scene->map.val)
		free_map(scene->map.val, scene->map.height);
	while (scene->sprites)
	{
		next = scene->sprites->next;
		img = scene->sprites->texture;
		mlx_destroy_image(mlx, img->img);
		free(scene->sprites->texture);
		free(scene->sprites);
		scene->sprites = next;
	}
	if (scene->spr_arr)
		free(scene->spr_arr);
	free_extras(mlx, scene);
}

int	scrap_scene(t_scene *scene)
{
	free(scene->walls[0]);
	free(scene->walls[1]);
	free(scene->walls[2]);
	free(scene->walls[3]);
	return (1);
}
