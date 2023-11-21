/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:48:00 by mcutura           #+#    #+#             */
/*   Updated: 2023/11/19 23:48:00 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	free_animation(void *mlx, t_animation *anim)
{
	int	i;

	i = -1;
	while (++i < anim->n_frames)
	{
		mlx_destroy_image(mlx, anim->frames[i]->img);
		free(anim->frames[i]);
	}
	free(anim->frames);
	free(anim);
}

int	set_animation(t_sprite *spr, char const **param)
{
	t_animation	*anim;

	anim = malloc(sizeof(*anim));
	if (!anim)
		return (1);
	anim->n_frames = ft_atoi(param[4]);
	anim->frame_x = ft_atoi(param[5]);
	anim->frame_y = ft_atoi(param[6]);
	spr->anim = anim;
	if (param[7])
	{
		spr->hdiv = ft_atoi(param[7]);
		if (param[8])
		{
			spr->vdiv = ft_atoi(param[8]);
			if (param[9])
			{
				spr->z = ft_atod_dirty(param[9]);
				if (param[10])
					register_pickup(spr, param[10]);
			}
		}
	}
	return (0);
}
