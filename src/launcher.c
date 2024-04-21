/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:52:25 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/20 01:39:05 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*	Scene!
 *	Camera!
 *	Action!
 */
int	main(int ac, char **av)
{
	static t_cub	cub;
	static t_scene	scene_one;
	static t_player	player_one;
	static t_camera	camera;

	if (ac != 2)
		return (throw_error(USAGE));
	if (init_scene(av[1], &scene_one))
		return (EXIT_FAILURE);
	cub.scene = &scene_one;
	if (spawn_player(&player_one, &cub.scene->map) \
	|| validate_map(&cub.scene->map))
		return (scrap_scene(cub.scene));
	cub.player = &player_one;
	if (init_window(&cub, FULLSCREEN) || init_canvas(&cub)
	|| init_camera(&cub, &camera, player_one.direction)
	|| load_scene_textures(&cub))
		return (cleanup(&cub), EXIT_FAILURE);
	init_hooks(&cub);
	ft_printf("Cub3D\nScene: %s\n", av[1]);
	return (mlx_loop(cub.mlx));
}
