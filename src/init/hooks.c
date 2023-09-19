/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:39:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/17 12:39:49 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	close_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	free_scene(cub->scene);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_terminate(cub->mlx);
	ft_printf("Exiting\n");
	exit(EXIT_SUCCESS);
}

void	keys_hook(t_mlx_key_data keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		close_hook(param);
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
		move_player(param, keydata.key);
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
		sidestep_player(param, keydata.key);
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		turn_player(param, keydata.key);
}

static inline void	clear_image(t_mlx_image *img, int background)
{
	ft_memset(img->pixels, background, img->width * img->height * BPP);
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	// ft_printf("FPS: %d\n", 1 / cub->mlx->delta_time);
	clear_image(cub->img, 0x9999FFFF);
	draw_screen(cub);
}

void	init_hooks(t_cub *cub)
{
	mlx_key_hook(cub->mlx, keys_hook, cub);
	mlx_close_hook(cub->mlx, close_hook, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
}
