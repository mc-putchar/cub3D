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

void	draw_hud(t_mlx_image *img)
{
	int const	k_color = 0x424242FF;
	t_uint32	x;

	x = 0;
	while (x < img->width)
	{
		put_pixel(img, x, 0, k_color);
	}
}
