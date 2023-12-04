/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_shredder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:07:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/04 17:07:34 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	img_shredder(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->walls[0]->img);
	free(cub->walls[0]);
	mlx_destroy_image(cub->mlx, cub->walls[1]->img);
	free(cub->walls[1]);
	mlx_destroy_image(cub->mlx, cub->walls[2]->img);
	free(cub->walls[2]);
	mlx_destroy_image(cub->mlx, cub->walls[3]->img);
	free(cub->walls[3]);
	mlx_destroy_image(cub->mlx, cub->logo->img);
	free(cub->logo);
	mlx_destroy_image(cub->mlx, cub->minimap->img);
	free(cub->minimap);
	mlx_destroy_image(cub->mlx, cub->hud->img);
	free(cub->hud);
	mlx_destroy_image(cub->mlx, cub->img->img);
	free(cub->img);
	mlx_destroy_image(cub->mlx, cub->cutscene->img);
	free(cub->cutscene);
}
