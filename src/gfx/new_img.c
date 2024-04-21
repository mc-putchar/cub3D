/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:17:44 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/18 17:13:17 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	new_image(void *mlx, t_mlx_image *img, int width, int height)
{
	if (width < 1 || height < 1)
		return (throw_error(BAD_IMG_SIZE));
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
		return (throw_error(MLX_ERROR));
	img->pixels = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, \
		&img->endian);
	if (!img->pixels)
		return (throw_error(MLX_ERROR));
	img->width = width;
	img->height = height;
	return (0);
}
