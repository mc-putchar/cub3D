/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_pickup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:11:32 by mcutura           #+#    #+#             */
/*   Updated: 2023/11/19 17:11:32 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	item_pickup(t_cub *cub, t_scene *scn)
{
	t_size	idx;

	idx = 0;
	while (idx < scn->n_sprites && scn->spr_arr[idx]->dist < 1)
	{
		if (scn->spr_arr[idx]->collectable)
		{
			ft_printf("Collected item\n");
			mlx_destroy_image(cub->mlx, \
				((t_mlx_image *)(scn->spr_arr[idx]->texture))->img);
			scn->spr_arr[idx]->isloaded = 0;
			scn->spr_arr[idx] = scn->spr_arr[--(scn->n_sprites)];
		}
		++idx;
	}
}
