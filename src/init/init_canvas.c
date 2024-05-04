/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_canvas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:58:21 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 03:04:09 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_canvas(t_cub *cub)
{
	cub->canvas = malloc(sizeof(t_mlx_image));
	if (!cub->canvas)
		return (throw_error(MALLOC_FAIL));
	if (new_image(cub->mlx, cub->canvas, cub->win_w, cub->win_h))
		return (1);
	return (0);
}

int	init_canvas_bonus(t_cub *cub)
{
	cub->canvas = malloc(sizeof(t_mlx_image));
	if (!cub->canvas)
		return (throw_error(MALLOC_FAIL));
	if (new_image(cub->mlx, cub->canvas, cub->win_w, (cub->win_h >> 2) * 3))
		return (1);
	return (0);
}
