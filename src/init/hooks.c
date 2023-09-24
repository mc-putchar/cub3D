/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:39:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/24 06:05:54 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	close_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_delete_texture(cub->walls[0]);
	mlx_delete_texture(cub->walls[1]);
	mlx_delete_texture(cub->walls[2]);
	mlx_delete_texture(cub->walls[3]);
	mlx_delete_image(cub->mlx, cub->minimap);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_terminate(cub->mlx);
	free_scene(cub->scene);
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

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	ft_bzero(cub->img->pixels, cub->img->width * cub->img->height * BPP);
	draw_screen(cub);
	draw_minimap(cub->minimap, &cub->scene->map, cub->player->position);
	// ft_printf("FPS: %d\n", (int)(1 / cub->mlx->delta_time));
}

void	init_hooks(t_cub *cub)
{
	mlx_key_hook(cub->mlx, keys_hook, cub);
	mlx_close_hook(cub->mlx, close_hook, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
}
