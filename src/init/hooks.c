/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:39:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 09:18:39 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	free_scene(cub->mlx, cub->scene);
	mlx_destroy_image(cub->mlx, cub->walls[0]->img);
	free(cub->walls[0]);
	mlx_destroy_image(cub->mlx, cub->walls[1]->img);
	free(cub->walls[1]);
	mlx_destroy_image(cub->mlx, cub->walls[2]->img);
	free(cub->walls[2]);
	mlx_destroy_image(cub->mlx, cub->walls[3]->img);
	free(cub->walls[3]);
	mlx_destroy_image(cub->mlx, cub->minimap->img);
	free(cub->minimap);
	mlx_destroy_image(cub->mlx, cub->img->img);
	free(cub->img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	ft_printf("Exiting\n");
	exit(EXIT_SUCCESS);
}

int	keys_hook(int key, void *param)
{
	if (key == KEY_ESC)
		close_hook(param);
	if (key == KEY_W || key == KEY_S)
		move_player(param, key);
	if (key == KEY_A || key == KEY_D)
		sidestep_player(param, key);
	if (key == ARROW_LEFT || key == ARROW_RIGHT)
		turn_player(param, key);
	if (key == KEY_SPACE)
		interact(param);
	return (0);
}

int	mouse_look(t_cub *cub)
{
	int		x;
	int		y;

	(void)mlx_mouse_get_pos(cub->mlx, cub->win, &x, &y);
	if (x != WIN_W >> 1)
		mouse_view(cub, x, y);
	mlx_mouse_move(cub->mlx, cub->win, WIN_W >> 1, WIN_H >> 1);
	return (0);
}

int	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	mouse_look(cub);
	draw_screen(cub);
	draw_minimap(cub->minimap, &cub->scene->map, cub->player->position);
	mlx_do_sync(cub->mlx);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img->img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap->img, \
		(WIN_W >> 1) - (MINIMAP_SIZE >> 1), WIN_H - MINIMAP_SIZE - 10);
	mlx_do_sync(cub->mlx);
	return (0);
}

void	init_hooks(t_cub *cub)
{
	(void)mlx_hook(cub->win, 2, 1L << 0, keys_hook, cub);
	(void)mlx_hook(cub->win, 17, 1L << 17, close_hook, cub);
	(void)mlx_loop_hook(cub->mlx, ft_hook, cub);
	(void)mlx_do_key_autorepeaton(cub->mlx);
	(void)mlx_mouse_move(cub->mlx, cub->win, WIN_W >> 1, WIN_H >> 1);
	if (!NOLEAKS)
		(void)mlx_mouse_hide(cub->mlx, cub->win);
}
