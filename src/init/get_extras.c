/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_extras.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:04:50 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/28 02:58:33 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	sprites_to_array(t_scene *scn)
{
	t_size		i;
	t_sprite	*spr;

	scn->spr_arr = malloc(sizeof(t_sprite *) * scn->n_sprites);
	if (!scn->spr_arr)
		return (throw_error("Memory allocation failed"));
	spr = scn->sprites;
	i = 0;
	while (i < scn->n_sprites && spr)
	{
		scn->spr_arr[i++] = spr;
		spr = spr->next;
	}
	return (0);
}

static void	set_sprite_params(t_sprite *spr, char const **param)
{
	spr->position.x = ft_atod_dirty(param[1]);
	spr->position.y = ft_atod_dirty(param[2]);
	spr->hdiv = 1;
	spr->vdiv = 1;
	spr->z = 0.0;
	if (param[4])
	{
		spr->hdiv = ft_atoi(param[4]);
		if (param[5])
		{
			spr->vdiv = ft_atoi(param[5]);
			if (param[6])
				spr->z = ft_atod_dirty(param[6]);
		}
	}
}

int	get_sprite(t_scene *scene, char const **param)
{
	t_sprite	*spr;
	t_sprite	*node;

	if (!param[1] || !param[2] || !param[3])
		return (throw_error("Wrong number of parameters"));
	spr = malloc(sizeof(t_sprite));
	if (!spr)
		return (throw_error("Memory allocation failure"));
	spr->next = NULL;
	spr->texture = ft_strdup(param[3]);
	if (!spr->texture && (free(spr), 1))
		return (throw_error("Memory allocation failure"));
	set_sprite_params(spr, param);
	if (!scene->sprites)
		scene->sprites = spr;
	else
	{
		node = scene->sprites;
		while (node->next)
			node = node->next;
		node->next = spr;
	}
	scene->n_sprites++;
	return (0);
}

int	get_extra(t_scene *scene, char const **param)
{
	t_extra	*ex;
	t_extra	*node;

	if (!ft_strncmp(param[0], "S", 1) || !ft_strncmp(param[0], "A", 1))
		return (get_sprite(scene, param));
	if (!param[1] || param[2])
		return (throw_error("Wrong number of parameters"));
	ex = malloc(sizeof(t_extra));
	if (!ex)
		return (throw_error("Memory allocation failure"));
	ex->key = ft_strdup(param[0]);
	ex->value = ft_strdup(param[1]);
	if (!ex->key || (!ex->value && (free(ex->key), 1)))
		return (throw_error("Memory allocation failure"));
	ex->next = NULL;
	if (!scene->extras)
		scene->extras = ex;
	else
	{
		node = scene->extras;
		while (node->next)
			node = node->next;
		node->next = ex;
	}
	return (0);
}
