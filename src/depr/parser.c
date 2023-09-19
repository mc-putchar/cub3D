/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:37:16 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/28 11:37:16 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_identifier(char *c)
{
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

static int	validate_path(char *c)
{
	int	fd;

	fd = open(c, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

static char	*set_color(t_scene *scene, int type, char *data)
{
	int		color;
	int		set;
	int		tmp;

	color = 0;
	set = 3;
	while (set)
	{
		while (*data && *data != '\n' && ft_isspace(*data))
			++data;
		if (!ft_isdigit(*data))
			return (NULL);
		tmp = ft_atoi(data);
		if (tmp > 255 || tmp < 0)
			return (NULL);
		color |= tmp << (set-- * 8);
		while (*data && (ft_isdigit(*data) || *data == ','))
			++data;
	}
	if (type == 1)
		scene->floor = color | 255;
	else
		scene->ceiling = color | 255;
	return (data);
}

static char	*set_texture(t_scene *scene, int type, char *data)
{
	size_t	len;
	char	*texpath;

	if (type > 3)
		return (NULL);
	while (*data && *data != '\n' && ft_isspace(*data))
		++data;
	len = 0;
	while (data[len] && !ft_isspace(data[len]))
		++len;
	if (!len)
		return (NULL);
	texpath = ft_memcpy(malloc(len), data, len);
	if (!texpath || validate_path(texpath))
		return (NULL);
	scene->walls[type - 3] = texpath;
	return (data + len);
}

int	read_map(char *data)
{
	char	**map;

	map = ft_split(data, '\n');
}

int	parse_scene(char *data, t_scene *scene)
{
	int		type;
	int		elems_needed;

	elems_needed = 6;
	while (*data && elems_needed)
	{
		if (!ft_isspace(*data))
		{
			type = is_identifier(data);
			if (!type)
				return (1);
			if (type > 2 && elems_needed--)
				data = set_texture(scene, type, data + 2);
			if (type < 3 && elems_needed--)
				data = set_color(scene, type, data + 1);
			if (!data)
				return (1);
		}
		++data;
	}
	if (elems_needed)
		return (1);
	return (0);
}
