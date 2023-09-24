/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:30:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/24 06:04:24 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft.h"
# include "MLX42/MLX42.h"
// # include "mlx.h"

/* Debug mode switch */
# ifndef DEBUG
#  define DEBUG	0
# endif

/* Usage message */
# define USAGE	"Usage: cub3D [FILE]"

/* Data structures */
# include "game_data.h"

/* ERROR HANDLING */
int			throw_error(char const *msg);
int			throw_error_free(char const *msg, void (*f)(), void *ptr);

/* INITIALIZING */
int			init_scene(char const *file, t_scene *scene);
int			init_window(t_cub *cub);
void		init_hooks(t_cub *cub);
int			set_scene_param(t_scene *scene, char **param);
int			read_map(char *line, int fd, t_map *map);
int			load_textures(t_cub *cub, t_scene *scene);
int			spawn_player(t_player *player, t_map *map);
int			start_camera(t_camera *camera, t_size height, t_size width, t_vector plane);

/* FREE MEMORY */
void		free_arr(char **arr);
void		free_map(char **map, int size);
void		free_scene(t_scene *scene);

/* HOOKS */
void		close_hook(void *param);
void		keys_hook(t_mlx_key_data keydata, void *param);
void		ft_hook(void *param);

/* DRAW */
void		put_pixel(t_mlx_image *img, int x, int y, int color);
int			draw_screen(t_cub *cub);

/* GAME */
void		move_player(t_cub *cub, t_keys key);
void		sidestep_player(t_cub *cub, t_keys key);
void		turn_player(t_cub *cub, t_keys key);

/* UNSORTED */
int			raycaster(t_cub *cub, t_size i, double *dist, double *wallx);
int			wall_check(t_map *map, int x, int y);
void		draw_minimap(t_mlx_image *img, t_map *map, t_vector position);

#endif
