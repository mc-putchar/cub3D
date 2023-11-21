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

void	key_pickup(t_cub *cub, t_mlx_image *img)
{
	cub->player->has_key = img;
}

void	phone_pickup(t_cub *cub, t_mlx_image *img)
{
	++(cub->player->has_phone);
	(void)img;
}

void	badge_pickup(t_cub *cub, t_mlx_image *img)
{
	++(cub->player->has_badge);
	(void)img;
}

void	register_pickup(t_sprite *spr, char const *type)
{
	if (!ft_strncmp(type, "key", 4))
		spr->on_pickup = &key_pickup;
	else if (!ft_strncmp(type, "badge", 6))
		spr->on_pickup = &badge_pickup;
	else if (!ft_strncmp(type, "phone", 6))
		spr->on_pickup = &phone_pickup;
	spr->collectable = 1;
}

void	item_pickup(t_cub *cub, t_scene *scn)
{
	t_size	idx;

	idx = 0;
	while (idx < scn->n_sprites && scn->spr_arr[idx]->dist < 1)
	{
		if (scn->spr_arr[idx]->collectable)
		{
			if (scn->spr_arr[idx]->on_pickup)
				scn->spr_arr[idx]->on_pickup(cub, scn->spr_arr[idx]->texture);
			else
				ft_printf("Collected item\n");
			scn->spr_arr[idx] = scn->spr_arr[--(scn->n_sprites)];
		}
		++idx;
	}
}
