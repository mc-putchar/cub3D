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

int	load_map(t_cub *cub, char const *filepath)
{
	int		fd;
	char	*line;
	int		len;
	int		i;

	cub->map_height = 0;
	(void)get_file_size(filepath, &cub->map_height);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	cub->map_width = 0;
	cub->map = malloc(cub->map_height * sizeof(char *));
	i = 0;
	line = get_next_line(fd);
	while (line && i < cub->map_height)
	{
		cub->map[i++] = line;
		len = (int)ft_strlen(line);
		if (len > cub->map_width)
			cub->map_width = len;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

float	read_player_orientation(char *c)
{
	if (*c == 'N' )
		return (M_PI_2);
	if (*c == 'S')
		return (M_PI_2 + M_PI);
	if (*c == 'E')
		return (0);
	if (*c == 'W')
		return (M_PI);
	return (-1);
}

int	init_player(t_cub *cub)
{
	int		i;
	int		j;

	j = -1;
	while (++j < cub->map_height)
	{
		i = -1;
		while (++i < cub->map_width)
		{
			cub->player.direction = read_player_orientation(&cub->map[j][i]);
			if (cub->player.direction == -1)
				continue ;
			cub->player.position.x = (i + 0.5) * MAP_SQUARE;
			cub->player.position.y = (j + 0.5) * MAP_SQUARE;
			cub->player.pdir.x = cos(cub->player.direction);
			cub->player.pdir.y = sin(cub->player.direction);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

void	init_hooks(t_cub *cub)
{
	mlx_key_hook(cub->mlx, keys_hook, cub);
	mlx_close_hook(cub->mlx, close_hook, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
}

int	init_data(t_cub *cub)
{
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!cub->mlx)
		return (EXIT_FAILURE);
	if (load_map(cub, MAP_PATH))
	{
		mlx_terminate(cub->mlx);
		return (EXIT_FAILURE);
	}
	ft_printf("Map loaded\n");
	if (init_player(cub))
		error_handler("Init player failed\n");
	ft_printf("Player initialized\n");
	init_hooks(cub);
	return (EXIT_SUCCESS);
}
