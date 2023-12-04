/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:29:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/29 05:14:00 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

// TODO switch to preset scenario
#define LEVEL_ONE	"scenes/bonus/level_one.cub"

/* Take: 2
 * Bonus!
 */
int	main(int ac, char **av)
{
	t_cub		cub;
	t_scene		scene;
	t_player	player;
	t_camera	camera;
	pthread_t	load_thread;

	(void)ft_printf("Cub3D: Peer of Destiny\n");
	init_cub(&cub, &scene, &camera, &player);
	if (init_scene(LEVEL_ONE, &scene))
		return (scrap_scene(&scene) && throw_error("No scene no play"));
	if (init_window(&cub))
		return (EXIT_FAILURE);
	cub.zbuffer = NULL;
	if (pthread_create(&load_thread, NULL, load_resources, &cub))
		return (throw_error("Failed creating thread"), close_hook(&cub));
	if (ac < 2 || ft_strncmp(av[1], "--skip", 7))
	{
		draw_splash(&cub);
		draw_intro(&cub);
	}
	pthread_join(load_thread, NULL);
	init_hud(&cub);
	return (mlx_loop(cub.mlx));
}
