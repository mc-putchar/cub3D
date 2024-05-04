/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:27:15 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 02:20:57 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

/* Libraries */
# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"

/* Additional data */
# include "keycodes.h"
# include "game_data.h"

/* Window constants */
# define WIN_TITLE	"Cub3D"
# define DEFAULT_WIDTH	1024
# define DEFAULT_HEIGHT	768
# ifndef FULLSCREEN
#  define FULLSCREEN	0
# endif

/* Error messages */
# define USAGE			"Usage:	./cub3D <path_to_scene_file>"
# define MALLOC_FAIL	"Memory allocation failed"
# define MLX_FAIL		"Failed to initialize MLX"
# define MLX_ERROR		"MLX error"
# define WIN_FAIL		"Failed to create window"
# define BAD_IMG_SIZE	"Invalid image size"
# define TEXTURE_ERROR	"Failed to load texture"
# define BAD_SCENE		"Scene file misconfigured"
# define BAD_EXTENSION	"Scene file must have .cub extension"
# define BAD_FILEPATH	"Unable to open file at provided path"
# define BAD_COLOR		"Irregular color input"
# define DOUBLE_SETTING	"Duplicate setting found"
# define PARAM_ERROR	"Wrong number of parameters"
# define BAD_IDENTIFIER	"Unrecognized scene identifier"
# define NODE_FAILED	"Failed creating map node"
# define NO_PLAYER		"No player spawn on the map"
# define MULTIPLAYER	"Multiple player spawns"
# define UNKNOWN_MAPSYM	"Unrecognized symbol on map"
# define MAP_NOT_CLOSED	"Map not enclosed by walls"
# define GENERIC_ERROR	"Uh oh! Something went wrong"
# define THREAD_FAIL	"Failed creating thread"

enum e_mlx_events
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

/* Init */
int		init_window(t_cub *cub, int fullscreen);
void	init_hooks(t_cub *cub);
int		close_hook(void *param);
int		init_scene(char const *file, t_scene *scene);
int		set_scene_param(t_scene *scene, char const **param);
int		read_map(char *line, int fd, t_map *map);
int		validate_map(t_map *map);
int		spawn_player(t_player *player, t_map *map);
int		init_camera(t_cub *cub, t_camera *cam, t_vector player_dir);
int		init_canvas(t_cub *cub);

/* Graphics */
void	put_pixel(t_mlx_image *img, int x, int y, int color);
int		new_image(void *mlx, t_mlx_image *img, int width, int height);
int		load_texture(void *mlx, t_mlx_image *img, char *path);
int		flip_axes(void *mlx, t_mlx_image **img);
int		load_scene_textures(t_cub *cub);
void	draw_map(t_mlx_image *img, t_map *map);
void	cast_ray(t_cub *cub, t_ray *ray, size_t n);
void	render_scene(t_cub *cub, t_mlx_image *canvas);

/* Core */
void	turn_player(t_player *player, t_camera *camera);
void	move_player(t_player *player, t_map *map);

/* Utils */
int		throw_error(char const *msg);
int		throw_error_free(char const *msg, void (*f)(), void *ptr);
int		validate_file(char const *path, int *fd);
int		validate_extension(char const *path, char const *extension);
void	free_arr(char **arr);
void	free_map(char **map, int size);
void	shred_image(void *mlx, t_mlx_image *img);
int		scrap_scene(t_scene *scene);
void	cleanup(t_cub *cub);

#endif // CUB3D_H
