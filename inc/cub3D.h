/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:30:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/14 17:30:29 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
/* Define _USE_MATH_DEFINES before including math.h to expose these macro
 * definitions for common math constants.  These are placed under an #ifdef
 * since these commonly-defined names are not part of the C/C++ standards.
 */
# define _USE_MATH_DEFINES
# include <math.h>
# include "MLX42/MLX42.h"
# include "libft.h"

# include "point.h"
# include "game_data.h"

# define WIN_HEIGHT		800
# define WIN_WIDTH		800
# define BPP			4
# define MAP_SQUARE		32

typedef struct s_cub
{
	mlx_t		*mlx;
	t_player	player;
	char		**map;
	int			map_width;
	int			map_height;
	mlx_image_t	*img;
}	t_cub;

/* INIT */
int		init_data(t_cub *cub);

/* DRAW */
void	put_pixel(mlx_image_t *img, int x, int y, int color);
void	draw_square(mlx_image_t *img, t_pointInt position, int size, int color);
int		draw_map(t_cub *cub);
void	draw_player(t_cub *cub);

/* HOOKS */
void	ft_hook(void *param);
void	keys_hook(mlx_key_data_t keydata, void *param);
void	close_hook(void *param);

/* COLORS */
int		get_color(int r, int g, int b, int a);

/* FREEZ */
void	free_map(char **map, int size);

/* UTILS */
ssize_t	get_file_size(int fd, int *line_count);

#endif
