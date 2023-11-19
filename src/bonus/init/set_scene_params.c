/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 02:16:15 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/29 04:34:31 by mcutura          ###   ########.fr       */
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
		return (COMMENT);
	if (ft_isdigit(*c))
		return (-1);
	if (!ft_strncmp(c, "F", 1))
		return (FLOOR);
	if (!ft_strncmp(c, "C", 1))
		return (CEILING);
	if (!ft_strncmp(c, "NO", 2))
		return (NORTH_WALL);
	if (!ft_strncmp(c, "SO", 2))
		return (SOUTH_WALL);
	if (!ft_strncmp(c, "WE", 2))
		return (WEST_WALL);
	if (!ft_strncmp(c, "EA", 2))
		return (EAST_WALL);
	return (UNKNOWN);
}

/* >>"R,G,B"
 * [0 - 255]
 * << [RGBA]
 */
static int	check_color_validity(char const **param, int *color)
{
	int	set;
	int	tmp;

	set = 0;
	while (param[++set])
	{
		if (set > 3 || ft_strlen(param[set]) > 3 || !ft_isnumber(param[set]))
			return (throw_error("Irregular color input"));
		tmp = ft_atoi(param[set]);
		if (tmp < 0 || tmp > 255)
			return (throw_error("Irregular color input"));
		*color |= (tmp << ((3 - set) * 8));
	}
	return (0);
}

static int	set_color(t_scene *scene, int type, char const **param)
{
	int	color;

	color = 0;
	if (!param[1] || !param[2] || !param[3])
		return (throw_error("Wrong number of parameters"));
	if (check_color_validity(param, &color))
		return (1);
	if (type == 1)
	{
		if (scene->areset_colors & FLOOR_COLOR_SET)
			return (throw_error("Duplicate color setting found"));
		scene->floor = color | (0xFF << 24);
		scene->areset_colors |= FLOOR_COLOR_SET;
	}
	else
	{
		if (scene->areset_colors & CEILING_COLOR_SET)
			return (throw_error("Duplicate color setting found"));
		scene->ceiling = color | (0xFF << 24);
		scene->areset_colors |= CEILING_COLOR_SET;
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
	if (type == UNKNOWN)
		return (get_extra(scene, param));
	if (type == COMMENT)
		return (0);
	if (type < 0)
		return (type);
	if (type < 3)
		return (set_color(scene, type, param));
	if (!param[1] || param[2])
		return (throw_error("Wrong number of parameters"));
	if (scene->walls[type - 3])
		return (throw_error("Duplicate identifier found"));
	scene->walls[type - 3] = ft_strdup(param[1]);
	if (!scene->walls[type - 3])
		return (throw_error("Memory allocation failed"));
	fd = open(scene->walls[type - 3], O_RDONLY);
	if (fd < 0)
		return (throw_error("Can't open texture file"));
	close(fd);
	return (0);
}
