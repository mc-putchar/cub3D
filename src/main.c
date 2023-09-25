/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:29:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 09:54:23 by mcutura          ###   ########.fr       */
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
	(void)ft_printf("Cub3D: My first RayCaster\nScene: %s\n", av[1]);
	if (!(av + 1) || init_scene(av[1], &scene))
		return (throw_error("No scene no play"));
	cub.scene = &scene;
	(void)ft_printf("Scene set\n");
	if (init_window(&cub))
		return (EXIT_FAILURE);
	if (load_textures(&cub, &scene) || spawn_player(&player, &scene.map) || \
		start_camera(&camera, cub.win_h, cub.win_w, player.direction))
		return (throw_error("Catastrophic failure"), close_hook(&cub));
	cub.player = &player;
	cub.camera = &camera;
	(void)ft_printf("Starting game\nGood luck!\n");
	mlx_loop(cub.mlx);
	(void)ft_printf("Reached unreacheable code... Byeee\n");
	return (EXIT_FAILURE);
}
