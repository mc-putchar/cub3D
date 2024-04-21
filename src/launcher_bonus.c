/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:06:51 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 03:00:32 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

// TODO switch to preset scenario
#define LEVEL_ONE	"scenes/bonus/level_one.cub"

int	main(int ac, char **av)
{
	static t_cub		cub;
	static t_camera		camera;
	static t_player		player;
	static t_sound_data	sound_data;

	(void)ac;
	(void)av;
	(void)ft_printf("Cub3D: Peer of Destiny\n");
	cub.camera = &camera;
	cub.player = &player;
	cub.bonus = &sound_data;
	if (init_window_bonus(&cub, FULLSCREEN))
		return (EXIT_FAILURE);
	init_hooks_bonus(&cub);
	if (load_thread(&cub, LEVEL_ONE))
		return (close_hook(&cub));
	// if (pthread_create(&((t_sound_data *)cub.bonus)->sound_thread, NULL, play_intro_sound, NULL))
	// 	return (throw_error(THREAD_FAIL));
	return (mlx_loop(cub.mlx));
}
