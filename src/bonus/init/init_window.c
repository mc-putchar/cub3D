/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:04:13 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 09:54:27 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	img_gen(void *mlx, t_mlx_image *img, int width, int height)
{
	if (width < 0 || height < 0)
		return (throw_error("Negative image size"));
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
		return (throw_error_free("MLX image failed", free, img));
	img->pixels = mlx_get_data_addr(img->img, \
		&img->bpp, &img->size_line, &img->endian);
	if (!img->pixels)
		return (throw_error("MLX error"));
	img->width = width;
	img->height = height;
	return (0);
}

int	tex_load(void *mlx, t_mlx_image *img, char *path)
{
	img->img = mlx_xpm_file_to_image(mlx, path, \
		(int *)&img->width, (int *)&img->height);
	if (!img->img)
		return (throw_error("Failed to load texture"));
	img->pixels = mlx_get_data_addr(img->img, &img->bpp, \
		&img->size_line, &img->endian);
	if (!img->pixels)
		return (throw_error("MLX error"));
	return (0);
}

static int	init_imgs(t_cub *cub)
{
	if (img_gen(cub->mlx, cub->cutscene, cub->win_w, cub->win_h))
		return (1);
	if (img_gen(cub->mlx, cub->img, cub->win_w, cub->win_h - HUD_HEIGHT))
		return (1);
	if (img_gen(cub->mlx, cub->hud, cub->win_w, HUD_HEIGHT))
		return (1);
	if (img_gen(cub->mlx, cub->minimap, MINIMAP_SIZE, MINIMAP_SIZE))
		return (1);
	if (tex_load(cub->mlx, cub->logo, LOGO_FILE))
		return (1);
	return (0);
}

int	init_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (throw_error("Failed to initialize MLX"));
	(void)mlx_get_screen_size(cub->mlx, &cub->win_w, &cub->win_h);
	cub->win = mlx_new_window(cub->mlx, cub->win_w, cub->win_h, TITLE);
	if (!cub->win)
		return (throw_error("MLX failed to create window"));
	cub->cutscene = malloc(sizeof(t_mlx_image));
	cub->img = malloc(sizeof(t_mlx_image));
	cub->hud = malloc(sizeof(t_mlx_image));
	cub->logo = malloc(sizeof(t_mlx_image));
	cub->minimap = malloc(sizeof(t_mlx_image));
	if (!cub->cutscene || !cub->img || !cub->hud || !cub->logo || !cub->minimap)
		return (throw_error("Memory allocation failed"));
	if (init_imgs(cub))
		return (1);
	init_hooks(cub);
	return (0);
}
