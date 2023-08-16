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

#define PLAYER_SIZE		8
#define PLAYER_COLOR	0xFFFF22FF

void	draw_player(t_cub *cub)
{
	t_pointInt	p;

	p.x = cub->player.position.x;
	p.y = cub->player.position.y;
	draw_circle(cub->img, &p, PLAYER_SIZE, PLAYER_COLOR);
	p.x += cub->player.pdir.x * PLAYER_SIZE * 2;
	p.y += cub->player.pdir.y * PLAYER_SIZE * 2;
	draw_line(cub->img, &cub->player.position, &p);
}
