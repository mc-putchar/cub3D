/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:04:13 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/24 07:41:24 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int	init_window(t_cub *cub)
// {
// 	if (!cub)
// 		return (throw_error("WTF? No cub? I blame memory"));
// 	cub->mlx = mlx_init(WIN_W, WIN_H, "Cub3D", false);
// 	if (!cub->mlx)
// 		return (throw_error("Failed to initialize MLX"));
// 	cub->img = mlx_new_image(cub->mlx, WIN_W, WIN_H);
// 	if (!cub->img || (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < 0))
// 		return (throw_error(mlx_strerror(mlx_errno)));
// 	cub->minimap = mlx_new_image(cub->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
// 	if (!cub->minimap || (mlx_image_to_window(cub->mlx, cub->minimap, \
// 		(WIN_W >> 1) - (MINIMAP_SIZE >> 1), WIN_H - MINIMAP_SIZE) < 0))
// 		return (throw_error(mlx_strerror(mlx_errno)));
// 	init_hooks(cub);
// 	(void)ft_printf("Initialized\n");
// 	return (0);
// }

static int	img_gen(void *mlx, t_mlx_image *img, int width, int height)
{
	if (width < 0 || height < 0)
		return (throw_error("Negative image size"));
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
		return (throw_error_free("MLX image failed", free, img));
	img->pixels = mlx_get_data_addr(img->img, \
		&img->bpp, &img->size_line, \
		&img->endian);
	if (!img->pixels)
		return (throw_error("MLX error"));
	img->width = width;
	img->height = height;
	return (0);
}

int	init_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (throw_error("Failed to initialize MLX"));
	cub->win = mlx_new_window(cub->mlx, WIN_W, WIN_H, TITLE);
	if (!cub->win)
		return (throw_error("MLX failed to create window"));
	cub->img = malloc(sizeof(t_mlx_image));
	cub->minimap = malloc(sizeof(t_mlx_image));
	if (!cub->img || !cub->minimap)
		return (throw_error("Memory allocation failed"));
	if (img_gen(cub->mlx, cub->img, WIN_W, WIN_H))
		return (1);
	if (img_gen(cub->mlx, cub->minimap, MINIMAP_SIZE, MINIMAP_SIZE))
		return (1);
	init_hooks(cub);
	return (0);
}
