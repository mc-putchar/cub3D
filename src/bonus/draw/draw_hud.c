/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 08:30:19 by mcutura           #+#    #+#             */
/*   Updated: 2023/11/19 08:30:19 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_hud(t_cub *cub)
{
	int const	bg_color = 0x420242;
	int const	frame_color = 0x040004;
	t_uint32	x;
	t_uint32	y;

	y = 0;
	while (y < cub->hud->height)
	{
		x = 0;
		if (y < 16 || y > cub->hud->height - 16)
		{
			while (x < cub->hud->width)
				put_pixel(cub->hud, x++, y, frame_color);
		}
		else
		{
			while (x < 16)
				put_pixel(cub->hud, x++, y, frame_color);
			while (x < cub->hud->width - 16)
				put_pixel(cub->hud, x++, y, bg_color);
			while (x < cub->hud->width)
				put_pixel(cub->hud, x++, y, frame_color);
		}
		++y;
	}
	draw_minimap(cub->hud, &cub->scene->map, cub->player->position);
}
