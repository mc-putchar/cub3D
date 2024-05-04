/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:46:19 by mcutura           #+#    #+#             */
/*   Updated: 2024/05/03 17:49:55 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

int	game_loop_bonus(void *param)
{
	t_cub	*cub;

	cub = param;
	render_scene(cub, cub->canvas);
	cast_sprites(cub, ((t_bonus_data *)cub->bonus)->sprite_arr, cub->player);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->canvas->img, 0, 0);
	mlx_do_sync(cub->mlx);
	do_frame_sync(cub);
	display_fps(cub);
	turn_player(cub->player, cub->camera);
	move_player(cub->player, &cub->scene->map);
	return (0);
}
