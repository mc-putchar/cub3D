/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:53:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/24 21:55:32 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DATA_H
# define GAME_DATA_H

# include "point.h"
# include "vector.h"

/* Constants */
# define TITLE			"Cub3D"
# define WIN_H			768
# define WIN_W			1024
# define BPP			4
# define DIRECTIONS		"ESWN"
# define MOVE_SPEED		0.1
# define TURN_SPEED		0.05
# define MINIMAP_SIZE	128
# define MINIMAP_PDIV	3

/* Norme adaptations */
// typedef mlx_t			t_mlx;
// typedef mlx_image_t		t_mlx_image;
// typedef mlx_texture_t	t_mlx_texture;
// typedef mlx_key_data_t	t_mlx_key_data;
// typedef keys_t			t_keys;
typedef size_t			t_size;
typedef __uint32_t		t_uint32;

/* Data structures */

typedef struct s_mlx_image
{
	void		*img;
	char		*pixels;
	t_uint32	width;
	t_uint32	height;
	int			bpp;
	int			endian;
	int			size_line;
}	t_mlx_image;

typedef struct s_map
{
	t_size				height;
	t_size				width;
	char				**val;
}	t_map;

typedef struct s_player
{
	t_vector			position;
	t_vector			direction;
	int					move_speed;
	int					turn_speed;
}	t_player;

typedef struct s_camera
{
	t_size				height;
	t_size				width;
	int					fov;
	int					distance;
	int					brush;
	t_vector			plane;
}	t_camera;

typedef struct s_scene
{
	int					floor;
	int					ceiling;
	char				*walls[4];
	t_map				map;
}	t_scene;

typedef struct s_ray
{
	t_vector	direction;
	t_vector	delta;
	t_vector	distance;
	int			stepx;
	int			stepy;
}	t_ray;

typedef struct s_cub
{
	void				*mlx;
	void				*win;
	t_mlx_image			*img;
	t_mlx_image			*minimap;
	t_mlx_image			*walls[4];
	t_scene				*scene;
	t_camera			*camera;
	t_player			*player;
}	t_cub;

#endif
