/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 08:26:03 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/15 08:26:03 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player(t_cub *cub)
{
	t_point	p;

	draw_circle(cub->img, &cub->player.position, PLAYER_SIZE, PLAYER_COLOR);
	p.x = cub->player.position.x + cub->player.pdir.x * PLAYER_SIZE * 2;
	p.y = cub->player.position.y + cub->player.pdir.y * PLAYER_SIZE * 2;
	p.color = PLAYER_COLOR;
	draw_line(cub->img, &cub->player.position, &p);
}
