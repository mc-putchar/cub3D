/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:15:04 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/29 05:15:07 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Everything and nothing
 * By definition: *.cub
 */
static int	validate_path(char const *path, int *fd)
{
	int	idx;

	idx = 0;
	if (!path)
		exit(throw_error("Corrupted path to file"));
	while (path[idx])
		++idx;
	if (idx < 4 || ft_strncmp(path + idx - 4, ".cub", 4))
		exit(throw_error("Scene file must have .cub extension"));
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
		exit(throw_error("Unable to open file at provided path"));
	return (0);
}

/* 2 colors w/ 4 walls pls
 * (Y/n)? $ 
*/
static int	complete(t_scene *scene, char *line)
{
	int	i;

	if (scene->areset_colors != (FLOOR_COLOR_SET | CEILING_COLOR_SET))
		return (free(line), 1);
	i = 0;
	while (i < 4)
		if (!scene->walls[i++])
			return (free(line), 1);
	return (0);
}

static int	reset_scene(t_scene *scene)
{
	int	i;

	scene->areset_colors = 0;
	scene->ceiling = -1;
	scene->floor = -1;
	i = 0;
	while (i < 4)
		scene->walls[i++] = NULL;
	scene->sprites = NULL;
	scene->spr_arr = NULL;
	scene->n_sprites = 0;
	scene->extras = NULL;
	return (0);
}

/* Lock, chop & smoke
 * exit thru the back
 */
int	init_scene(char const *file, t_scene *scene)
{
	int		error;
	int		fd;
	char	*line;
	char	**chop;

	error = 0;
	fd = -1;
	if (!scene || validate_path(file, &fd) || reset_scene(scene))
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		chop = ft_splits(line, " ,\n\r\t");
		if (!chop)
			return (throw_error_free("Something went wrong", free, line));
		if (chop[0])
			error = set_scene_param(scene, (char const **)chop);
		free_arr(chop);
		if (error == -1)
			return (complete(scene, line) || read_map(line, fd, &scene->map));
		if ((free(line), 1) && error)
			return (throw_error("Scene file misconfigured"));
		line = get_next_line(fd);
	}
	return (close(fd), throw_error("Scene file misconfigured"));
}
