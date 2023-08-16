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

void	ft_hook(void *param)
{
	draw_player(param);
}

void	keys_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		close_hook(param);
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
