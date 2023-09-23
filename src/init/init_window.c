/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:04:13 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/23 18:19:27 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_window(t_cub *cub)
{
	if (!cub)
		return (throw_error("WTF? No cub? I blame memory"));
	cub->mlx = mlx_init(WIN_W, WIN_H, "Cub3D", false);
	if (!cub->mlx)
		return (throw_error("Failed to initialize MLX"));
	cub->img = mlx_new_image(cub->mlx, WIN_W, WIN_H);
	if (!cub->img || (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < 0))
		return (throw_error(mlx_strerror(mlx_errno)));
	cub->minimap = mlx_new_image(cub->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	if (!cub->minimap || (mlx_image_to_window(cub->mlx, cub->minimap, 0, 0) < 0))
		return (throw_error(mlx_strerror(mlx_errno)));
	init_hooks(cub);
	(void)ft_printf("Initialized\n");
	return (0);
}
