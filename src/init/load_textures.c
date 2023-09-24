/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:27:09 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/24 07:44:30 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	(void)ft_printf("Textures loaded\n");
	return (0);
}
