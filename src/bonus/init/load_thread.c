/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:12:32 by mcutura           #+#    #+#             */
/*   Updated: 2023/12/04 17:12:32 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	*load_resources(void *arg)
{
	t_cub *const	cub = arg;

	if (load_textures(cub, cub->scene) \
	|| spawn_player(cub->player, &cub->scene->map) \
	|| validate_map(&cub->scene->map) \
	|| start_camera(cub, cub->camera, cub->player->direction) \
	|| sprites_to_array(cub->scene))
		return (throw_error("Catastrophic failure"), NULL);
	return (cub);
}
