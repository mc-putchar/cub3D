/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 03:07:58 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/20 03:07:58 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

static int	keydown_hook(int key, void *param);
static int	keyup_hook(int key, void *param);

void	init_hooks_bonus(t_cub *cub)
{
	(void)mlx_hook(cub->win, ON_DESTROY, 1L << 17, close_hook_bonus, cub);
	(void)mlx_hook(cub->win, ON_KEYDOWN, 1L << 0, keydown_hook, cub);
	(void)mlx_hook(cub->win, ON_KEYUP, 1L << 1, keyup_hook, cub);
	(void)mlx_loop_hook(cub->mlx, game_loop_bonus, cub);
}

int	close_hook_bonus(void *param)
{
	t_cub	*cub;

	cub = param;
	cleanup_bonus(cub);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	ft_printf("Exiting\n");
	exit(EXIT_SUCCESS);
}

int	keydown_hook(int key, void *param)
{
	t_cub const	*cub = param;

	if (key == KEY_ESC)
		close_hook_bonus(param);
	if (key == KEY_W)
		cub->player->dir_move = 1;
	if (key == KEY_A)
		cub->player->side_move = -1;
	if (key == KEY_S)
		cub->player->dir_move = -1;
	if (key == KEY_D)
		cub->player->side_move = 1;
	if (key == ARROW_LEFT)
		cub->player->turn_dir = -1;
	if (key == ARROW_RIGHT)
		cub->player->turn_dir = 1;
	if (key == KEY_SHIFT)
		cub->player->move_speed *= 2;
	if (key == KEY_SPACE)
		player_interact(cub->player, &cub->scene->map);
	return (0);
}

int	keyup_hook(int key, void *param)
{
	t_cub	*cub;

	cub = param;
	if (key == KEY_W || key == KEY_S)
		cub->player->dir_move = 0;
	if (key == KEY_A || key == KEY_D)
		cub->player->side_move = 0;
	if (key == ARROW_LEFT || key == ARROW_RIGHT)
		cub->player->turn_dir = 0;
	if (key == KEY_SHIFT)
		cub->player->move_speed /= 2;
	return (0);
}
