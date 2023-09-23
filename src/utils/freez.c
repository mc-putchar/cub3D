/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freez.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:11:54 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/23 14:02:56 by mcutura          ###   ########.fr       */
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

void	free_scene(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < 4)
		free(scene->walls[i++]);
	if (scene->map.val)
		free_map(scene->map.val, scene->map.height);
}
