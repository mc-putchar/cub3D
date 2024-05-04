/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 03:37:09 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 07:21:02 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

static void	reset_scene(t_scene *scene);
static int	parse_scene_file(t_scene *scene, int fd);
static int	is_complete(t_scene *scene);

int	init_scene(char const *file, t_scene *scene)
{
	int		fd;

	if (validate_extension(file, ".cub"))
		return (throw_error(BAD_EXTENSION));
	if (validate_file(file, &fd))
		return (throw_error(BAD_FILEPATH));
	reset_scene(scene);
	if (parse_scene_file(scene, fd))
		return (scrap_scene(scene));
	return (0);
}

static inline void	flush_gnl(int fd)
{
	char	*tmp;

	close(fd);
	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}

int	parse_scene_file(t_scene *scene, int fd)
{
	char	*line;
	char	**chop;
	int		error;

	line = get_next_line(fd);
	while (line)
	{
		chop = ft_splits(line, " ,\n\r\t");
		if (!chop)
			return (flush_gnl(fd), throw_error_free(GENERIC_ERROR, free, line));
		if (chop[0])
			error = set_scene_param(scene, (char const **)chop);
		else
			error = 0;
		free_arr(chop);
		if (error == -1 && is_complete(scene))
			return (read_map(line, fd, &scene->map));
		free(line);
		if (error)
			return (flush_gnl(fd), throw_error(BAD_SCENE));
		line = get_next_line(fd);
	}
	close(fd);
	return (throw_error(BAD_SCENE));
}

void	reset_scene(t_scene *scene)
{
	int	i;

	scene->areset_colors = 0;
	scene->ceiling = 0;
	scene->floor = 0;
	i = 0;
	while (i < 4)
		scene->walls[i++] = NULL;
	scene->map.height = 0;
	scene->map.val = NULL;
	scene->extras = NULL;
	scene->sprites = NULL;
	scene->n_sprites = 0;
}

int	is_complete(t_scene *scene)
{
	int	i;

	if (scene->areset_colors != (FLOOR_COLOR_SET | CEILING_COLOR_SET))
		return (0);
	i = 0;
	while (i < 4)
		if (!scene->walls[i++])
			return (0);
	return (1);
}
