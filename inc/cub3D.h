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
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
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
# include "vector.h"
# include "game_data.h"

# define WIN_HEIGHT		800
# define WIN_WIDTH		1600
# define BPP			4
# define MAP_SQUARE		32
# define MAP_BINDIV		5
# define MAP_COLOR		0xFF00FFFF

typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*img2;
	double		runtime;
	t_player	player;
	t_precalc	meth;
	int			map_width;
	int			map_height;
	char		**map;
}	t_cub;

/* INIT */
int		init_data(t_cub *cub);

/* DRAW */
void	put_pixel(mlx_image_t *img, int x, int y, int color);
void	draw_line(mlx_image_t *img, t_point *p1, t_point *p2);
void	bresenham(mlx_image_t *img, t_point *p1, t_point *p2);
void	draw_square(mlx_image_t *img, t_point *position, \
		int size, int color);
void	draw_circle(mlx_image_t *img, t_point *center, \
		int radius, int color);
void	draw_column(mlx_image_t *img, t_point *start, \
		int height, int width);
void	clear_image(mlx_image_t *img, int background);
int		draw_map(t_cub *cub);
void	draw_player(t_cub *cub);

/* RAYCASTER */
void	cast_rays(t_cub *cub);

/* HOOKS */
void	ft_hook(void *param);
void	keys_hook(mlx_key_data_t keydata, void *param);
void	close_hook(void *param);

/* COLORS */
int		get_color(int r, int g, int b, int a);
int		get_gradient(t_point *curr, t_point *start, t_point *end, \
		t_point *delta);

/* FREEZ */
void	free_map(char **map, int size);

/* UTILS */
ssize_t	get_file_size(char const *filepath, int *line_count);
int		angle_todeg(double angle);
double	angle_torad(int angle);
void	precalculate_meth(t_cub *cub);

void	error_handler(char const *message);
void	move_player(t_cub *cub, int forward, int sideways);
void	turn_player(t_cub *cub, int direction);

void	draw_scene(t_cub *cub, double dist, int x, int w, unsigned char shade);

#endif
