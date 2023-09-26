/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:09:37 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/26 14:30:56 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_fps(struct timeval *prev)
{
	struct timeval	now;
	int				fps;

	if (!prev || gettimeofday(&now, NULL))
		return (throw_error("Time is broken"));
	fps = (int)floor(1 / ((double)(now.tv_usec - prev->tv_usec) / 1000000 + \
			(double)(now.tv_sec - prev->tv_sec)));
	*prev = now;
	return (fps);
}
