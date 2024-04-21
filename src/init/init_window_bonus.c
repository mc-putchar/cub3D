/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:44:37 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/20 01:52:43 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

static void	set_fullscreen(t_xvar *mlx, t_win_list *win);
static void	set_window_size(t_cub *cub, int fs);

int	init_window_bonus(t_cub *cub, int fullscreen)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (throw_error(MLX_FAIL));
	set_window_size(cub, fullscreen);
	cub->win = mlx_new_window(cub->mlx, cub->win_w, cub->win_h, WIN_TITLE);
	if (!cub->win)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		return (throw_error(WIN_FAIL));
	}
	if (fullscreen)
		set_fullscreen(cub->mlx, cub->win);
	return (0);
}

void	set_fullscreen(t_xvar *mlx, t_win_list *win)
{
	Atom	wm_state;
	Atom	wm_fullscreen;

	wm_state = XInternAtom(mlx->display, "_NET_WM_STATE", 1);
	wm_fullscreen = XInternAtom(mlx->display, "_NET_WM_STATE_FULLSCREEN", 1);
	XChangeProperty(mlx->display, win->window, wm_state, \
	XA_ATOM, 32, PropModeReplace, (unsigned char *)&wm_fullscreen, 1);
}

void	set_window_size(t_cub *cub, int fs)
{
	if (!fs)
	{
		cub->win_w = DEFAULT_WIDTH;
		cub->win_h = DEFAULT_HEIGHT;
	}
	else
		(void)mlx_get_screen_size(cub->mlx, &cub->win_w, &cub->win_h);
}
