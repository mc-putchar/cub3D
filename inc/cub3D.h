/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:30:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/29 04:35:16 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft.h"
# include "mlx.h"
// # include "MLX42/MLX42.h"

/* Required for bonus */
# include <sys/time.h> // for FPS calculation and sync

/* Debug mode switch */
# ifndef DEBUG
#  define DEBUG	0
# endif

/* No leaks mode */
# ifndef NOLEAKS
#  define NOLEAKS 0
# endif

/* Usage message */
# define USAGE	"Usage: cub3D [SCENE FILE]"

/* Data structures */
# include "game_data.h"

/* ERROR HANDLING */
int			throw_error(char const *msg);
int			throw_error_free(char const *msg, void (*f)(), void *ptr);

/* INITIALIZING */
int			init_window(t_cub *cub);
void		init_hooks(t_cub *cub);
void		init_cub(t_cub *cub, t_scene *scene, t_camera *camera, \
			t_player *player);
int			init_scene(char const *file, t_scene *scene);
int			set_scene_param(t_scene *scene, char const **param);
int			get_sprite(t_scene *scene, char const **param);
int			get_extra(t_scene *scene, char const **param);
int			read_map(char *line, int fd, t_map *map);
int			load_textures(t_cub *cub, t_scene *scene);
int			spawn_player(t_player *player, t_map *map);
int			start_camera(t_cub *cub, t_camera *camera, t_vector plane);
int			validate_map(t_map *map);

/* FREE MEMORY */
void		free_arr(char **arr);
void		free_map(char **map, int size);
void		free_scene(void *mlx, t_scene *scene);
int			scrap_scene(t_scene *scene);

/* HOOKS */
int			close_hook(void *param);
int			keydown_hook(int key, void *param);
int			keyup_hook(int key, void *param);
int			mouse_look(int x, int y, t_cub *cub);
int			game_loop(void *param);

/* DRAW */
void		put_pixel(t_mlx_image *img, int x, int y, int color);
int			draw_screen(t_cub *cub);
void		draw_minimap(t_mlx_image *img, t_map *map, t_vector position);
int			cast_sprites(t_cub *cub, t_player *pl, t_scene *scn);

/* GAME */
void		move_player(t_player *player, t_map *map);
void		sidestep_player(t_player *player, t_map *map);
void		turn_player(t_player *player, t_camera *camera);
void		interact(t_cub *cub);
int			raycaster(t_cub *cub, t_size i, double *dist, double *wallx);
int			wall_check(t_map *map, int x, int y);
int			get_fps(struct timeval *prev);

/* UTILS */
void		quicksort(t_sprite **tab, int size);
int			sprites_to_array(t_scene *scn);

#endif
