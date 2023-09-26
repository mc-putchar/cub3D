/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:39:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/26 13:24:07 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	free(cub->zbuffer);
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
	if (key == KEY_SHIFT)
		cub->player->move_speed *= 2;
	if (key == KEY_SPACE)
		interact(param);
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

int	mouse_look(int x, int y, t_cub *cub)
{
	double	cosa;
	double	sina;
	double	tmp;
	double	angle;

	(void)y;
	angle = cub->player->turn_speed * (x - (cub->win_w >> 1)) * 0.1;
	cosa = cos(angle);
	sina = sin(angle);
	tmp = cub->player->direction.x;
	cub->player->direction.x = cosa * tmp - sina * cub->player->direction.y;
	cub->player->direction.y = sina * tmp + cosa * cub->player->direction.y;
	tmp = cub->camera->plane.x;
	cub->camera->plane.x = cosa * tmp - sina * cub->camera->plane.y;
	cub->camera->plane.y = sina * tmp + cosa * cub->camera->plane.y;
	(void)mlx_mouse_move(cub->mlx, cub->win, cub->win_w >> 1, cub->win_h >> 1);
	return (0);
}

int	ft_hook(void *param)
{
	t_cub	*cub;

	cub = param;
	move_player(cub->player, &cub->scene->map);
	sidestep_player(cub->player, &cub->scene->map);
	turn_player(cub->player, cub->camera);
	draw_screen(cub);
	draw_minimap(cub->minimap, &cub->scene->map, cub->player->position);
	mlx_do_sync(cub->mlx);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img->img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap->img, \
		(cub->win_w - MINIMAP_SIZE - 20), 20);
	mlx_do_sync(cub->mlx);
	return (0);
}

void	init_hooks(t_cub *cub)
{
	(void)mlx_hook(cub->win, ON_DESTROY, 1L << 17, close_hook, cub);
	(void)mlx_hook(cub->win, ON_KEYDOWN, 1L << 0, keydown_hook, cub);
	(void)mlx_hook(cub->win, ON_KEYUP, 1L << 1, keyup_hook, cub);
	(void)mlx_hook(cub->win, ON_MOUSEMOVE, 1L << 6, mouse_look, cub);
	(void)mlx_loop_hook(cub->mlx, ft_hook, cub);
	(void)mlx_mouse_move(cub->mlx, cub->win, cub->win_w >> 1, cub->win_h >> 1);
	if (!NOLEAKS)
		(void)mlx_mouse_hide(cub->mlx, cub->win);
}
