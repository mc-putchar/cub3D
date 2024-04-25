/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_sync.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:33:24 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/25 04:08:27 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

void	do_frame_sync(t_cub *cub)
{
	static struct timeval	prev;
	struct timeval			now;

	gettimeofday(&now, NULL);
	cub->frame_time = difftime(now.tv_sec, prev.tv_sec);
	cub->frame_time += ((double)(now.tv_usec - prev.tv_usec) / 1000000);
	prev = now;
	cub->player->move_speed = P_MOVE_SPEED * cub->frame_time;
	cub->player->turn_speed = P_TURN_SPEED * cub->frame_time;
}

void	display_fps(t_cub *cub)
{
	char	*fps;

	if (!cub->frame_time)
		return ;
	fps = ft_itoa((int)(1.0 / cub->frame_time));
	mlx_string_put(cub->mlx, cub->win, 10, 30, 0xFFFFFFFF, "FPS: ");
	mlx_string_put(cub->mlx, cub->win, 50, 30, 0xFFFFFFFF, fps);
	free(fps);
}
