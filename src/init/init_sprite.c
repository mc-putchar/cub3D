/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 03:23:15 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 07:21:14 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

static int	set_sprite_params(t_sprite *spr, char const **param);

int	load_animation(void)
{
	return (0);
}

int	init_sprite(t_scene *scene, char const **param)
{
	t_sprite	*spr;
	t_sprite	*tmp;

	if (!param[2] || !param[3])
		return (throw_error(PARAM_ERROR));
	if (!ft_strncmp(param[0], "A", 2))
		return (load_animation());
	spr = malloc(sizeof(t_sprite));
	if (!spr)
		return (throw_error(MALLOC_FAIL));
	if (set_sprite_params(spr, param))
	{
		free(spr->texture);
		free(spr->tag);
		free(spr);
		return (1);
	}
	tmp = scene->sprites;
	if (!tmp)
	{
		scene->sprites = spr;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = spr;
	return (++scene->n_sprites, 0);
}

int	set_sprite_params(t_sprite *spr, char const **param)
{
	spr->next = NULL;
	spr->tag = NULL;
	spr->isloaded = 0;
	spr->isanimated = 0;
	spr->z_offset = 0.0f;
	spr->texture = ft_strdup(param[1]);
	if (!spr->texture)
		return (throw_error(MALLOC_FAIL));
	spr->position.x = ft_atod(param[2]);
	spr->position.y = ft_atod(param[3]);
	spr->scale.x = 1.0f;
	spr->scale.y = 1.0f;
	if (!param[4])
		return (0);
	spr->scale.x = 1 / ft_atod(param[4]);
	if (!param[5])
		return (0);
	spr->scale.y = 1 / ft_atod(param[5]);
	if (!param[6])
		return (0);
	spr->z_offset = ft_atod(param[6]);
	if (!param[7])
		return (0);
	spr->tag = ft_strdup(param[7]);
	return (!spr->tag && throw_error(MALLOC_FAIL));
}
