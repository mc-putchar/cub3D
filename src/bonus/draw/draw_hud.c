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
	int const	frame_color = 0x420242;
	int const	bg_color = 0x0;
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

static void	draw_score(t_cub *cub)
{
	int const	score_color = 0x42AA42;
	char		*score;

	score = ft_itoa(cub->player->tigs);
	if (!score)
		return ;
	mlx_put_image_to_window(cub->mlx, cub->win, cub->tig->img, \
		cub->win_w - 120, cub->win_h - HUD_HEIGHT + 120);
	mlx_string_put(cub->mlx, cub->win, cub->win_w - 120, \
		cub->win_h - HUD_HEIGHT + 180, score_color, "Score: ");
	mlx_string_put(cub->mlx, cub->win, cub->win_w - 60, \
		cub->win_h - HUD_HEIGHT + 180, score_color, score);
	free(score);
}

void	draw_hud(t_cub *cub)
{
	t_mlx_image	*img;

	if (cub->player->has_badge)
		mlx_put_image_to_window(cub->mlx, cub->win, cub->logo->img, \
			20, cub->win_h - HUD_HEIGHT + 20);
	if (cub->player->has_phone)
	{
		mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap->img, \
		(cub->win_w >> 1) - (MINIMAP_SIZE >> 1), cub->win_h - HUD_HEIGHT + 20);
	}
	if (cub->player->has_key)
	{
		img = cub->player->has_key;
		mlx_put_image_to_window(cub->mlx, cub->win, img->img, \
			cub->win_w - (img->width << 1), \
			cub->win_h - HUD_HEIGHT + 20);
	}
	if (cub->player->tigs)
		draw_score(cub);
}
