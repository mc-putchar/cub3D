/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:27:09 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/17 12:27:09 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_textures(t_cub *cub, t_scene *scene)
{
	int	i;

	i = 4;
	while (i--)
	{
		cub->walls[i] = mlx_load_png(scene->walls[i]);
		if (!cub->walls[i])
			return (throw_error("Failed to load texture"));
	}
	(void)ft_printf("Textures loaded\n");
	return (0);
}
