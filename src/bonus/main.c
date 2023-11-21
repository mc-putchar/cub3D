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

	(void)ft_printf("Cub3D: Peer of Destiny\n");
	if (init_scene(LEVEL_ONE, &scene))
		return (scrap_scene(&scene) && throw_error("No scene no play"));
	if (init_window(&cub))
		return (EXIT_FAILURE);
	cub.zbuffer = NULL;
	init_cub(&cub, &scene, &camera, &player);
	if (load_textures(&cub, &scene) || spawn_player(&player, &scene.map) || \
		start_camera(&cub, &camera, player.direction) || \
		validate_map(&scene.map) || sprites_to_array(&scene))
		return (throw_error("Catastrophic failure"), close_hook(&cub));
	if (validate_map(&scene.map))
		return (close_hook(&cub));
	if (gettimeofday(&cub.time, NULL))
		throw_error("I don't have time for this");
	if (ac < 2 || ft_strncmp(av[1], "--skip", 7))
	{
		draw_splash(&cub);
		draw_intro(&cub);
	}
	init_hud(&cub);
	return (mlx_loop(cub.mlx));
}
