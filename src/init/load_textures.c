/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:27:09 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 08:02:23 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	if (scene->extras && load_extras(cub, scene))
		return (1);
	(void)ft_printf("Textures loaded\n");
	return (0);
}
