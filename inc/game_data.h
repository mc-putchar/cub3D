/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:53:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/14 23:53:34 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DATA_H
# define GAME_DATA_H

# include "point.h"

# define PLAYER_SIZE	8
# define PLAYER_COLOR	0x00FF88FF

typedef struct s_precalc
{
	double	sins[360];
	double	coss[360];
	double	tans[360];
}	t_precalc;

typedef struct s_player
{
	t_point		position;
	t_vector	pdir;
	int			direction;
	int			move_speed;
	int			turn_speed;
}	t_player;

typedef struct s_plane
{
	int	height;
	int	width;
	int	fov;
	int	distance;
	int	col_multi;
}	t_plane;

typedef struct s_world
{
	int		height;
	int		width;
	int		floor;
	int		ceiling;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	**map;
}	t_world;

typedef struct s_scene
{
	struct s_world	world;
	struct s_player	player;
	struct s_plane	projection;
}	t_scene;

#endif
