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

# define SPLSH_FILE		"res/cubcover.xpm"
# define SPLSH_BONUS	"res/cub3d-pod_logo.xpm"
# define LOGO_FILE		"res/logo.xpm"
# define COIN_FILE		"res/coin.xpm"
# define INFO_FILE		"res/bios.nfo"
# define INTRO_RIFF		"res/peerofdestiny-intro.wav"

typedef struct s_bonus_data
{
	pthread_t	sound_thread;
	void		*sprite_atlas;
}	t_bonus_data;

#endif // GAME_DATA_BONUS_H
