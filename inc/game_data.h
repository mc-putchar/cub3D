/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:53:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/28 03:01:38 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DATA_H
# define GAME_DATA_H

# include "keycodes.h"
# include "point.h"
# include "vector.h"

/* Constants */

# define TITLE			"Cub3D"
# define BPP			4
# define DIRECTIONS		"ESWN"
# define P_MOVE_SPEED	0.05
# define P_TURN_SPEED	0.03
# define MINIMAP_SIZE	256
# define MINIMAP_PDIV	4

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
	double				move_speed;
	double				turn_speed;
	int					dir_move;
	int					side_move;
	int					turn_dir;
	int					has_key;
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

typedef struct s_extra
{
	void				*key;
	void				*value;
	void				*next;
	int					isloaded;
}	t_extra;

typedef struct s_sprite
{
	t_vector			position;
	double				z;
	double				dist;
	int					hdiv;
	int					vdiv;
	void				*texture;
	void				*next;
	int					isloaded;
}	t_sprite;

typedef struct s_sprite_data
{
	int	height;
	int	width;
	int	screenx;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	zoffset;
}	t_sprite_data;

typedef struct s_animation
{
	int		n_frames;
	int		current_frame;
	int		delay;
	int		iter;
}	t_animation;

enum e_scene_identifiers
{
	UNKNOWN = 0,
	FLOOR,
	CEILING,
	WEST_WALL,
	NORTH_WALL,
	EAST_WALL,
	SOUTH_WALL,
	COMMENT = 99
};

enum
{
	FLOOR_COLOR_SET = 1,
	CEILING_COLOR_SET = 2
};

typedef struct s_scene
{
	int					floor;
	int					ceiling;
	unsigned char		areset_colors;
	char				*walls[4];
	t_map				map;
	t_sprite			*sprites;
	t_sprite			**spr_arr;
	t_size				n_sprites;
	t_extra				*extras;
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
	int					win_h;
	int					win_w;
	t_mlx_image			*img;
	t_mlx_image			*minimap;
	t_mlx_image			*walls[4];
	t_scene				*scene;
	t_camera			*camera;
	t_player			*player;
	double				*zbuffer;
	struct timeval		time;
}	t_cub;

#endif
