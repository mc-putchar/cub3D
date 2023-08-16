/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:43:46 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/16 09:43:46 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		fps_calc(t_cub *cub)
{
	return (1 / cub->mlx->delta_time);
}

void	ft_hook(void *param)
{
	draw_map(param);
	draw_player(param);
}

void	keys_hook(mlx_key_data_t keydata, void *param)
{
	int	forward;
	int	sideways;
	int	rotation;

	forward = 0;
	sideways = 0;
	rotation = 0;
	if (keydata.key == MLX_KEY_ESCAPE)
		close_hook(param);
	if (keydata.key == MLX_KEY_W)
		forward = 1;
	if (keydata.key == MLX_KEY_S)
		forward = -1;
	if (keydata.key == MLX_KEY_A)
		sideways = 1;
	if (keydata.key == MLX_KEY_D)
		sideways = -1;
	if (keydata.key == MLX_KEY_LEFT)
		rotation = -1;
	if (keydata.key == MLX_KEY_RIGHT)
		rotation = 1;
	if (forward || sideways)
		move_player(param, forward, sideways);
	if (rotation)
		turn_player(param, rotation);
}

void	close_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	free_map(cub->map, cub->map_height);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_terminate(cub->mlx);
	exit(EXIT_SUCCESS);
}
