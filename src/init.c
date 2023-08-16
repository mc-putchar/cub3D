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

/*
"Icon made by Freepik from www.flaticon.com"
*/

#include "cub3D.h"

#define MAP_PATH	"./maps/map1.cub"
#define ICON		"./res/icon.png"

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
	cub->player.position.x = 0.0f;
	cub->player.position.y = 0.0f;
	cub->player.orientation = 0.0f;
	return (EXIT_SUCCESS);
}

void	init_hooks(t_cub *cub)
{
	mlx_key_hook(cub->mlx, keys_hook, cub);
	mlx_close_hook(cub->mlx, close_hook, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
}

int	init_data(t_cub *cub)
{
	// mlx_texture_t	*icon_tex;

	// mlx_set_setting(MLX_MAXIMIZED, true);
	// mlx_set_setting(MLX_FULLSCREEN, true);
	// mlx_set_setting(MLX_DECORATED, true);
	// mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (!cub->mlx)
		return (EXIT_FAILURE);
	// icon_tex = mlx_load_png(ICON);
	// if (icon_tex)
	// 	mlx_set_icon(cub->mlx, icon_tex);
	if (init_map(cub))
	{
		mlx_terminate(cub->mlx);
		return (EXIT_FAILURE);
	}
	init_player(cub);
	init_hooks(cub);
	return (EXIT_SUCCESS);
}
