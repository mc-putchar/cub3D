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
	mlx_clear_window(cub->mlx, cub->win);
	if (tex_load(cub->mlx, img, SPLSH_FILE))
		return ;
	mlx_put_image_to_window(cub->mlx, cub->win, img->img, \
		(cub->win_w >> 1) - (img->width >> 1), \
		(cub->win_h >> 1) - (img->height));
	ft_sleep(3000);
	mlx_destroy_image(cub->mlx, img->img);
	free(img);
}
