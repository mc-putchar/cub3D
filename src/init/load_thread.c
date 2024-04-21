/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:23:50 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 03:04:49 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

void	*load_resources(void *arg)
{
	t_cub *const	cub = arg;

	if (spawn_player(cub->player, &cub->scene->map) \
	|| validate_map(&cub->scene->map) || init_canvas_bonus(cub) \
	|| init_camera(cub, cub->camera, cub->player->direction) \
	|| load_scene_textures(cub) \
	|| load_extras(cub))
		return (cleanup_bonus(cub), NULL);
	return (cub);
}

int	load_thread(t_cub *cub, char *scene_file)
{
	pthread_t	ld_thread;
	void		*thread_ret;

	cub->scene = malloc(sizeof(t_scene));
	if (!cub->scene)
		return (throw_error(MALLOC_FAIL));
	if (init_scene(scene_file, cub->scene))
		return (1);
	if (pthread_create(&ld_thread, NULL, load_resources, cub))
		return (throw_error(THREAD_FAIL));
	draw_splash(cub, SPLSH_BONUS);
	if (pthread_join(ld_thread, &thread_ret) || !thread_ret)
		return (1);
	ft_printf("%s\n", "Resources loaded successfully");
	return (0);
}
