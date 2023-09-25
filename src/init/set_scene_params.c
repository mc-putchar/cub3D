/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 02:16:15 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 11:46:08 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Whoami
 * whatyasayin
 */
static int	identify(char const *c)
{
	if (!c)
		return (0);
	if (*c == '#')
		return (99);
	if (ft_isdigit(*c))
		return (-1);
	if (!ft_strncmp(c, "F", 1))
		return (1);
	if (!ft_strncmp(c, "C", 1))
		return (2);
	if (!ft_strncmp(c, "NO", 2))
		return (4);
	if (!ft_strncmp(c, "SO", 2))
		return (6);
	if (!ft_strncmp(c, "WE", 2))
		return (5);
	if (!ft_strncmp(c, "EA", 2))
		return (3);
	return (0);
}

/* >>"R,G,B"
 * [0 - 255]
 * << [RGBA]
 */
static int	set_color(t_scene *scene, int type, char const **param)
{
	int	color;
	int	set;
	int	tmp;

	color = 0;
	set = 0;
	while (param[++set])
	{
		if (set > 3 || ft_strlen(param[set]) > 3 || !ft_isnumber(param[set]))
			return (throw_error("Irregular color input"));
		tmp = ft_atoi(param[set]);
		if (tmp < 0 || tmp > 255)
			return (throw_error("Irregular color input"));
		color |= (tmp << ((3 - set) * 8));
	}
	if (type == 1)
		scene->floor = color | (0xFF << 24);
	else
		scene->ceiling = color | (0xFF << 24);
	return (0);
}

static int	get_sprite(t_scene *scene, char const **param)
{
	t_sprite	*spr;
	t_sprite	*node;

	if (!param[1] || !param[2] || !param[3] || param[4])
		return (throw_error("Wrong number of parameters"));
	spr = malloc(sizeof(t_sprite));
	if (!spr)
		return (throw_error("Memory allocation failure"));
	spr->next = NULL;
	spr->position.x = ft_atod_dirty(param[1]);
	spr->position.y = ft_atod_dirty(param[2]);
	spr->texture = ft_strdup(param[3]);
	if (!spr->texture && (free(spr), 1))
		return (throw_error("Memory allocation failure"));
	if (!scene->sprites)
		scene->sprites = spr;
	else
	{
		node = scene->sprites;
		while (node->next)
			node = node->next;
		node->next = spr;
	}
	return (0);
}

static int	get_extra(t_scene *scene, char const **param)
{
	t_extra	*ex;
	t_extra	*node;

	if (!ft_strncmp(param[0], "S", 1))
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

/* Get 'em, bytes!
 * Byttery POWered
 */
int	set_scene_param(t_scene *scene, char const **param)
{
	int	type;
	int	fd;

	type = identify(param[0]);
	if (!type)
		return (get_extra(scene, param));
	if (type == 99)
		return (0);
	if (type < 0)
		return (type);
	if (type < 3)
		return (set_color(scene, type, param));
	if (!param[1] || param[2])
		return (throw_error("Wrong number of parameters"));
	scene->walls[type - 3] = ft_strdup(param[1]);
	if (!scene->walls[type - 3])
		return (throw_error("Memory allocation failed"));
	fd = open(scene->walls[type - 3], O_RDONLY);
	if (fd < 0)
		return (throw_error("Can't open texture file"));
	close(fd);
	return (0);
}
