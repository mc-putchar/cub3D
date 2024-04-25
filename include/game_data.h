/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:19:12 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 03:06:56 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DATA_H
# define GAME_DATA_H

# include <stddef.h>
# include <stdint.h>

# define DIRECTIONS			"ESWN"
# define CAMERA_PLANE_DIST	0.6
# define WALL_BUFFER		0.2
/* P is for player */
# define P_MOVE_SPEED		0.1
# define P_TURN_SPEED		0.05

enum
{
	FLOOR_COLOR_SET = 1,
	CEILING_COLOR_SET = 2
};

enum e_scene_identifiers
{
	UNKNOWN = 0,
	FLOOR,
	CEILING,
	WEST_WALL,
	NORTH_WALL,
	EAST_WALL,
	SOUTH_WALL,
	WALL,
	SPRITE,
	KEY,
	COLLECTIBLE,
	ITEM,
	WEAPON,
	ENEMY,
	COMMENT = 99
};

typedef struct s_point
{
	uint32_t	x;
	uint32_t	y;
}	t_point;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray
{
	t_vector			direction;
	t_vector			delta;
	t_vector			distance;
	double				wall_dist;
	double				wallx;
	int					stepx;
	int					stepy;
	int					hit;
	int					side;
}	t_ray;

typedef struct s_mlx_image
{
	void				*img;
	char				*pixels;
	uint32_t			width;
	uint32_t			height;
	int					bpp;
	int					endian;
	int					size_line;
}	t_mlx_image;

typedef struct s_map
{
	size_t				height;
	size_t				width;
	char				**val;
}	t_map;

typedef struct s_sprite_data
{
	t_vector		position;
	t_vector		scale;
	void			*texture;
	double			v_offset;
	char			*tag;
	struct s_sprite	*next;
}	t_sprite_data;

typedef struct s_extra
{
	char			*key;
	void			*value;
	struct s_extra	*next;
	int				type;
	int				isloaded;
}	t_extra;

typedef struct s_scene
{
	int					floor;
	int					ceiling;
	unsigned char		areset_colors;
	t_map				map;
	char				*walls[4];
	t_extra				*extras;
}	t_scene;

typedef struct s_player
{
	t_vector			position;
	t_vector			direction;
	double				move_speed;
	double				turn_speed;
	int					dir_move;
	int					side_move;
	int					turn_dir;
	int					tigs;
	void				*has_phone;
	void				*has_key;
}	t_player;

typedef struct s_camera
{
	size_t				height;
	size_t				width;
	int					fov;
	int					distance;
	int					brush;
	t_vector			plane;
	double				*zbuff;
}	t_camera;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	int				win_h;
	int				win_w;
	t_scene			*scene;
	t_camera		*camera;
	t_player		*player;
	t_mlx_image		*canvas;
	t_mlx_image		*walls[4];
	void			*bonus;
	double			frame_time;
}	t_cub;

#endif // GAME_DATA_H
