/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:46:45 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/17 14:46:45 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	angle_todeg(double angle)
{
	return (round(angle * 180 / M_PI));
}

double	angle_torad(int angle)
{
	return (angle * M_PI / 180);
}

void	precalculate_meth(t_cub *cub)
{
	int		i;
	double	angle;

	i = -1;
	while (++i < 360)
	{
		angle = angle_torad(i);
		cub->meth.sins[i] = sin(angle);
		cub->meth.coss[i] = cos(angle);
		cub->meth.tans[i] = tan(angle);
		cub->meth.itans[i] = 1 / cub->meth.tans[i];
	}
}
