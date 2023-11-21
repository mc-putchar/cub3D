/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_splash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 14:20:52 by mcutura           #+#    #+#             */
/*   Updated: 2023/11/19 14:20:52 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_splash(t_cub *cub)
{
	t_mlx_image	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return ;
	tex_load(cub->mlx, img, SPLSH_FILE);
	mlx_put_image_to_window(cub->mlx, cub->win, img->img, 0, 0);
	ft_sleep(2000);
	mlx_destroy_image(cub->mlx, img->img);
	free(img);
}
