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

int	load_animation(void)
{
	return (0);
}

int	init_sprite(t_scene *scene, char const **param)
{
	t_sprite	*spr;

	if (!ft_strncmp(param[0], "A", 2))
		return (load_animation());
	spr = malloc(sizeof(t_sprite));
	if (!spr)
		return (throw_error(MALLOC_FAIL));
	spr->texture = ft_strdup(param[1]);
	if (!spr->texture)
		return (throw_error_free(MALLOC_FAIL, free, spr));
	free(spr->texture);
	free(spr);
	(void)scene;
	return (0);
}
