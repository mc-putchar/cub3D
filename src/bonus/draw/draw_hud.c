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

void	init_hud(t_cub *cub)
{
	int const	frame_color = 0x040004;
	int const	bg_color = 0x420242;
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
}

void	draw_hud(t_cub *cub)
{
	t_mlx_image	*img;

	if (cub->player->has_badge)
		mlx_put_image_to_window(cub->mlx, cub->win, cub->logo->img, \
			20, cub->win_h - HUD_HEIGHT + 20);
	if (cub->player->has_phone)
		mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap->img, \
			(cub->win_w >> 1) - (MINIMAP_SIZE >> 1), cub->win_h - HUD_HEIGHT + 20);
	if (cub->player->has_key)
	{
		img = cub->player->has_key;
		mlx_put_image_to_window(cub->mlx, cub->win, img->img, \
			cub->win_w - (img->width << 1), \
			cub->win_h - HUD_HEIGHT + 20);
	}
}
