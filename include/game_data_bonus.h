/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 02:14:28 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 07:33:45 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DATA_BONUS_H
# define GAME_DATA_BONUS_H

# include <pthread.h>
# include <pulse/simple.h>

# define MINIMAP_SIZE		256
# define MINIMAP_PDIV		4
/* P is for player */
# undef P_MOVE_SPEED
# define P_MOVE_SPEED		3
# undef P_TURN_SPEED
# define P_TURN_SPEED		2

# define SPLSH_FILE		"res/cubcover.xpm"
# define SPLSH_BONUS	"res/cub3d-pod_logo.xpm"
# define LOGO_FILE		"res/logo.xpm"
# define COIN_FILE		"res/coin.xpm"
# define INFO_FILE		"res/bios.nfo"
# define INTRO_RIFF		"res/peerofdestiny-intro.wav"


typedef struct s_sprite
{
	struct s_sprite	*next;
	t_vector		position;
	t_vector		scale;
	double			z_offset;
	double			dist;
	char			*tag;
	void			*texture;
	int				isanimated;
	int				isloaded;
}	t_sprite;

typedef struct s_sprite_data
{
	t_point	dimension;
	t_point	start;
	t_point	end;
	int		screenx;
	int		zoffset;
}	t_sprite_data;

typedef struct s_animation
{
	t_sprite		*sprite;
	uint32_t		n_frames;
}	t_animation;

typedef struct s_bonus_data
{
	t_sprite		**sprite_arr;
	pthread_t		sound_thread;
}	t_bonus_data;

#endif // GAME_DATA_BONUS_H
