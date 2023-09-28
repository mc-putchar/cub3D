/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:29:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/28 02:06:35 by mcutura          ###   ########.fr       */
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
	if (!(av + 1) || init_scene(av[1], &scene))
		return (throw_error("No scene no play"));
	cub.scene = &scene;
	if (init_window(&cub))
		return (EXIT_FAILURE);
	cub.zbuffer = malloc(sizeof(double) * camera.width);
	if (load_textures(&cub, &scene) || spawn_player(&player, &scene.map) || \
		start_camera(&camera, cub.win_h, cub.win_w, player.direction) || \
		sprites_to_array(cub.scene))
		return (throw_error("Catastrophic failure"), close_hook(&cub));
	cub.player = &player;
	cub.camera = &camera;
	if (!cub.zbuffer)
		return (throw_error("Memory allocation failure"), close_hook(&cub));
	if (gettimeofday(&cub.time, NULL))
		throw_error("I don't have time for this");
	return (mlx_loop(cub.mlx));
}
