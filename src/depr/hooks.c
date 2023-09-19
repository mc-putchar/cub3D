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

int	fps_calc(t_cub *cub)
{
	static mlx_image_t	*img;
	char				*str;
	char				*tmp;

	if (img)
		mlx_delete_image(cub->mlx, img);
	tmp = ft_itoa(1 / cub->mlx->delta_time);
	str = ft_strjoin("FPS: ", tmp);
	free(tmp);
	img = mlx_put_string(cub->mlx, str, 800, 20);
	free(str);
	return (1 / cub->mlx->delta_time);
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	clear_image(cub->img, 0x777777FF);
	draw_map(cub);
	draw_player(cub);
	clear_image(cub->img2, 0x777777FF);
	raycaster(cub);
	fps_calc(cub);
	// printf("\rPlayer x:%d y:%d dir:%d | pDir x:%f y:%f", cub->player.position.x, cub->player.position.y, cub->player.direction, cub->player.pdir.x, cub->player.pdir.y);
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
	mlx_delete_image(cub->mlx, cub->img2);
	mlx_terminate(cub->mlx);
	ft_printf("\nByeee\n");
	exit(EXIT_SUCCESS);
}
