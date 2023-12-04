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

void	*load_resources(void *arg)
{
	t_cub *const	cub = arg;

	if (load_textures(cub, cub->scene) \
	|| spawn_player(cub->player, &cub->scene->map) \
	|| validate_map(&cub->scene->map) \
	|| start_camera(cub, cub->camera, cub->player->direction) \
	|| sprites_to_array(cub->scene))
		return (throw_error("Catastrophic failure"), NULL);
	if (gettimeofday(&cub->time, NULL))
		throw_error("I don't have time for this");
	return (cub);
}

void	*play_intro_sound(void *ignore)
{
	char		*sound;
	size_t		sound_bytes;

	if (load_sound(INTRO_RIFF, &sound, &sound_bytes))
		return (NULL);
	play_sound(sound, sound_bytes);
	free(sound);
	return (ignore);
}

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
	pthread_t	sound_thread;

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
		(void)pthread_create(&sound_thread, NULL, play_intro_sound, NULL);
		draw_intro(&cub);
		// pthread_join(sound_thread, NULL);
	}
	pthread_join(load_thread, NULL);
	init_hud(&cub);
	return (mlx_loop(cub.mlx));
}
