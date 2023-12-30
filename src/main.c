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

#include "cub3D.h"

/* Take: 1
 * Action!
 */
int	main(int ac, char **av)
{
	t_cub		cub;
	t_scene		scene;
	t_player	player;
	t_camera	camera;

	if (ac != 2)
		return (ft_printf("%s\n", USAGE), EXIT_FAILURE);
	(void)ft_printf("Cub3D: 42RayCaster\nScene: %s\n", av[1]);
	if (init_scene(av[1], &scene))
		return (scrap_scene(&scene) && throw_error("No scene no play"));
	if (init_window(&cub))
		return (EXIT_FAILURE);
	cub.zbuffer = NULL;
	init_cub(&cub, &scene, &camera, &player);
	if (load_textures(&cub, &scene) || spawn_player(&player, &scene.map) || \
		start_camera(&cub, &camera, player.direction) || \
		validate_map(&scene.map))
		return (throw_error("Catastrophic failure"), close_hook(&cub));
	return (mlx_loop(cub.mlx));
}
