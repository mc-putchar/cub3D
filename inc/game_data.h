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
# define PLAYER_STEP	4
# define PLAYER_TURN	3

typedef struct s_precalc
{
	double	sins[360];
	double	coss[360];
}	t_precalc;

typedef struct s_player
{
	t_point		position;
	t_vector	pdir;
	int			direction;
}	t_player;

typedef struct s_map
{
	int		map_height;
	int		map_width;
	char	**map;
}	t_map;

#endif
