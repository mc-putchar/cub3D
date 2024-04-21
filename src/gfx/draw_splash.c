/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_splash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:27:53 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 01:57:16 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_splash(t_cub *cub, char const *splash_file)
{
	t_mlx_image	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return ;
	mlx_clear_window(cub->mlx, cub->win);
	if (load_texture(cub->mlx, img, (char *)splash_file))
	{
		free(img);
		return ;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, img->img, \
		(cub->win_w >> 1) - (img->width >> 1), \
		(cub->win_h >> 1) - (img->height >> 1));
	sleep(1);
	mlx_destroy_image(cub->mlx, img->img);
	free(img);
}
