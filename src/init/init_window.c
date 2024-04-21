/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:47:19 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/20 01:45:23 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_window_size(t_cub *cub, int fs);

int	init_window(t_cub *cub, int fullscreen)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (throw_error(MLX_FAIL));
	set_window_size(cub, fullscreen);
	cub->win = mlx_new_window(cub->mlx, cub->win_w, cub->win_h, WIN_TITLE);
	if (!cub->win)
		return (throw_error(WIN_FAIL));
	return (0);
}

void	set_window_size(t_cub *cub, int fs)
{
	if (!fs)
	{
		cub->win_w = DEFAULT_WIDTH;
		cub->win_h = DEFAULT_HEIGHT;
	}
	else
		(void)mlx_get_screen_size(cub->mlx, &cub->win_w, &cub->win_h);
}
