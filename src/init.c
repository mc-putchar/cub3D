/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:54:36 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/14 23:54:36 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define MAP_PATH	"./maps/map1.cub"
#define READ_BLOCK	4096

static ssize_t	get_file_size(int fd, int *line_count)
{
	ssize_t	size;
	ssize_t	r;
	char	buf[READ_BLOCK];
	int		i;

	size = 0;
	r = read(fd, buf, READ_BLOCK);
	while (r > 0)
	{
		size += r;
		i = 0;
		while (i < r)
			if (buf[i++] == '\n')
				(*line_count)++;
		r = read(fd, buf, READ_BLOCK);
	}
	if (r < 0)
		return (-1);
	if (fd > 2)
		close(fd);
	return (size);
}

int	init_map(t_cub *cub)
{
	int		fd;
	char	*line;
	int		len;
	int		i;

	fd = open(MAP_PATH, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	i = 0;
	(void)get_file_size(fd, &i);
	cub->map_height = i;
	fd = open(MAP_PATH, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	cub->map_width = 0;
	cub->map = malloc(cub->map_height * sizeof(char *));
	i = 0;
	line = get_next_line(fd);
	while (line && i < cub->map_height)
	{
		// ft_printf("%s", line);
		cub->map[i++] = line;
		len = (int)ft_strlen(line);
		if (len > cub->map_width)
			cub->map_width = len;
		line = get_next_line(fd);
	}
	return (0);
}

int	init_player(t_cub *cub)
{
	cub->player.position.x = 12.0f;
	cub->player.position.y = 12.0f;
	cub->player.orientation = 0.0f;
	return (EXIT_SUCCESS);
}

int	init_data(t_cub *cub)
{
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!cub->mlx)
		return (EXIT_FAILURE);
	if (init_map(cub))
	{
		mlx_terminate(cub->mlx);
		return (EXIT_FAILURE);
	}
	init_player(cub);
	return (EXIT_SUCCESS);
}
