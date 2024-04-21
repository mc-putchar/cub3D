/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:28:17 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/26 13:32:06 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	game_loop(void *param);
static int	keydown_hook(int key, void *param);
static int	keyup_hook(int key, void *param);

void	init_hooks(t_cub *cub)
{
	(void)mlx_hook(cub->win, ON_DESTROY, 1L << 17, close_hook, cub);
	(void)mlx_hook(cub->win, ON_KEYDOWN, 1L << 0, keydown_hook, cub);
	(void)mlx_hook(cub->win, ON_KEYUP, 1L << 1, keyup_hook, cub);
	(void)mlx_loop_hook(cub->mlx, game_loop, cub);
}

int	close_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	cleanup(cub);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	ft_printf("Exiting\n");
	exit(EXIT_SUCCESS);
}

int	game_loop(void *param)
{
	t_cub	*cub;

	cub = param;
	render_scene(cub, cub->canvas);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->canvas->img, 0, 0);
	mlx_do_sync(cub->mlx);
	turn_player(cub->player, cub->camera);
	move_player(cub->player, &cub->scene->map);
	return (0);
}

int	keydown_hook(int key, void *param)
{
	t_cub	*cub;

	cub = param;
	if (key == KEY_ESC)
		close_hook(param);
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
	return (0);
}
