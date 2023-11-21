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

#include "cub3D_bonus.h"

inline static int	check_file(char const *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (throw_error("Can't open texture file"));
	close(fd);
	return (0);
}

static int	set_sprite_params(t_sprite *spr, char const **param)
{
	spr->on_pickup = NULL;
	spr->anim = NULL;
	spr->hdiv = 1;
	spr->vdiv = 1;
	spr->z = 0.0;
	spr->position.x = ft_atod_dirty(param[2]);
	spr->position.y = ft_atod_dirty(param[3]);
	spr->collectable = 0;
	if (!ft_strncmp(param[0], "A", 2))
		return (set_animation(spr, param));
	if (param[4])
	{
		spr->hdiv = ft_atoi(param[4]);
		if (param[5])
		{
			spr->vdiv = ft_atoi(param[5]);
			if (param[6])
			{
				spr->z = ft_atod_dirty(param[6]);
				if (param[7])
					register_pickup(spr, param[7]);
			}
		}
	}
	return (0);
}

int	get_sprite(t_scene *scene, char const **param)
{
	t_sprite	*spr;
	t_sprite	*node;

	if (!param[2] || !param[3])
		return (throw_error("Wrong number of parameters"));
	spr = malloc(sizeof(t_sprite));
	if (!spr)
		return (throw_error("Memory allocation failure"));
	spr->texture = ft_strdup(param[1]);
	if ((!spr->texture && (free(spr), 1)) || set_sprite_params(spr, param))
		return (throw_error("Memory allocation failure"));
	spr->isloaded = 0;
	spr->next = NULL;
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

static int	set_extra_params(t_extra *ex, char const **param)
{
	ex->key = ft_strdup(param[0]);
	if (!ex->key)
		return (1);
	ex->value = ft_strdup(param[1]);
	if (!ex->value)
	{
		free(ex->key);
		return (1);
	}
	ex->next = NULL;
	ex->isloaded = 0;
	return (0);
}

int	get_extra(t_scene *scene, char const **param)
{
	t_extra	*ex;
	t_extra	*node;

	if (!param[1])
		return (throw_error("Wrong number of parameters"));
	if (check_file(param[1]))
		return (1);
	if (!ft_strncmp(param[0], "S", 1) || !ft_strncmp(param[0], "A", 1))
		return (get_sprite(scene, param));
	ex = malloc(sizeof(t_extra));
	if (!ex || (set_extra_params(ex, param) && (free(ex), 1)))
		return (throw_error("Memory allocation failure"));
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
