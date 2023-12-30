/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:09:37 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/26 14:43:48 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	get_fps(struct timeval *prev)
{
	struct timeval	now;
	int				fps;

	if (!prev || gettimeofday(&now, NULL))
		return (throw_error("I don't have time for this"));
	fps = (int)floor(1 / ((double)(now.tv_usec - prev->tv_usec) / 1000000 + \
			(double)(now.tv_sec - prev->tv_sec)));
	*prev = now;
	return (fps);
}

void	display_fps(t_cub *cub)
{
	char	*fps;

	cub->fps = get_fps(&cub->time);
	fps = ft_itoa(cub->fps);
	mlx_string_put(cub->mlx, cub->win, 10, 30, 0xFFFFFFFF, "FPS: ");
	mlx_string_put(cub->mlx, cub->win, 50, 30, 0xFFFFFFFF, fps);
	free(fps);
}
