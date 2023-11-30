/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:28:17 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/26 13:32:06 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_hooks(t_cub *cub)
{
	(void)mlx_hook(cub->win, ON_DESTROY, 1L << 17, close_hook, cub);
	(void)mlx_hook(cub->win, ON_KEYDOWN, 1L << 0, keydown_hook, cub);
	(void)mlx_hook(cub->win, ON_KEYUP, 1L << 1, keyup_hook, cub);
	(void)mlx_loop_hook(cub->mlx, game_loop, cub);
}
