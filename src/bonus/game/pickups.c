/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:04:04 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/04 17:04:04 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	key_pickup(t_cub *cub, t_mlx_image *img)
{
	cub->player->has_key = img;
}

void	phone_pickup(t_cub *cub, t_mlx_image *img)
{
	cub->player->has_phone = img;
}

void	badge_pickup(t_cub *cub, t_mlx_image *img)
{
	cub->player->has_badge = img;
}

void	tig_pickup(t_cub *cub, t_mlx_image *img)
{
	(void)img;
	++(cub->player->tigs);
}
