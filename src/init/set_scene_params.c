/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 02:16:15 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/16 02:16:15 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Whoami
 * whatyasayin
 */
static int	is_identifier(char const *c)
{
	if (!c)
		return (0);
	if (!ft_strncmp(c, "F", 1))
		return (1);
	if (!ft_strncmp(c, "C", 1))
		return (2);
	if (!ft_strncmp(c, "NO", 2))
		return (3);
	if (!ft_strncmp(c, "SO", 2))
		return (4);
	if (!ft_strncmp(c, "WE", 2))
		return (5);
	if (!ft_strncmp(c, "EA", 2))
		return (6);
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
		color |= (tmp << ((4 - set) * 8));
	}
	if (type == 1)
		scene->floor = color | 0xFF;
	else
		scene->ceiling = color | 0xFF;
	return (0);
}

/* Get 'em, bytes!
 * Byttery POWered
 */
int	set_scene_param(t_scene *scene, char **param)
{
	int	type;
	int	fd;

	type = is_identifier(param[0]);
	if (!type)
		return (1);
	if (type < 3)
		return (set_color(scene, type, (char const **)param));
	if (!param[1] || param[2])
		return (1);
	scene->walls[type - 3] = ft_strdup(param[1]);
	if (!scene->walls[type - 3])
		return (throw_error("Memory allocation failed"));
	fd = open(scene->walls[type - 3], O_RDONLY);
	if (fd < 0)
		return (throw_error("Can't open texture file"));
	close(fd);
	return (0);
}
