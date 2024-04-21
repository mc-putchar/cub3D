/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_params.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:39:26 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/20 03:04:17 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	set_color(t_scene *scene, int type, char const **param);
static int	check_color_validity(char const **param, int *color);
static int	identify(char const *c);

int	set_scene_param(t_scene *scene, char const **param)
{
	int const	type = identify(param[0]);
	int			fd;

	if (type == UNKNOWN)
		return (throw_error(BAD_IDENTIFIER));
	if (type == COMMENT)
		return (0);
	if (type < 0)
		return (type);
	if (type < 3)
		return (set_color(scene, type, param));
	if (!param[1] || param[2])
		return (throw_error(PARAM_ERROR));
	if (scene->walls[type - 3])
		return (throw_error(DOUBLE_SETTING));
	if (validate_file(param[1], &fd))
		return (throw_error(BAD_FILEPATH));
	scene->walls[type - 3] = ft_strdup(param[1]);
	if (!scene->walls[type - 3])
		return (throw_error(MALLOC_FAIL));
	return (close(fd), 0);
}

int	identify(char const *c)
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

int	set_color(t_scene *scene, int type, char const **param)
{
	int	color;

	color = 0;
	if (!param[1] || !param[2] || !param[3])
		return (throw_error(PARAM_ERROR));
	if (check_color_validity(param, &color))
		return (1);
	if (type == 1)
	{
		if (scene->areset_colors & FLOOR_COLOR_SET)
			return (throw_error(DOUBLE_SETTING));
		scene->floor = color | (0xFF << 24);
		scene->areset_colors |= FLOOR_COLOR_SET;
	}
	else
	{
		if (scene->areset_colors & CEILING_COLOR_SET)
			return (throw_error(DOUBLE_SETTING));
		scene->ceiling = color | (0xFF << 24);
		scene->areset_colors |= CEILING_COLOR_SET;
	}
	return (0);
}

/* >>"R,G,B"
 * [0 - 255]
 * << [RGBA]
 */
int	check_color_validity(char const **param, int *color)
{
	int	set;
	int	tmp;

	set = 0;
	while (param[++set])
	{
		if (set > 3 || ft_strlen(param[set]) > 3 || !ft_isnumber(param[set]))
			return (throw_error(BAD_COLOR));
		tmp = ft_atoi(param[set]);
		if (tmp < 0 || tmp > 255)
			return (throw_error(BAD_COLOR));
		*color |= (tmp << ((3 - set) * 8));
	}
	return (0);
}
