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
#define PLAYER_COLOR	0xFF3322FF

void	draw_player(t_cub *cub)
{
	t_pointInt	p;

	p.x = (int)cub->player.position.x * 32;
	p.y = (int)cub->player.position.y * 32;
	draw_square(cub->img, p, PLAYER_SIZE, PLAYER_COLOR);
}
