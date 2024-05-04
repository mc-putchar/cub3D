/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:25:20 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 07:21:42 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/* for asynchronous loading screens and soundtrack loop */
# include <pthread.h>
/* for playing sounds */
// # include <pulse/simple.h>
/* for FPS calculation and sync */
# include <sys/time.h>
# include <time.h>
/* for running fullscreen undecorated window */
# include <X11/Xatom.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>

# include "mlx_int.h"

# include "game_data_bonus.h"

# undef FULLSCREEN
# define FULLSCREEN	1
# undef WIN_TITLE
# define WIN_TITLE	"Cub3D: Peer of Destiny"
# define HUD_HEIGHT	288
# define FONT_COLOR	0x0042AA42
# define FONT_ERROR	0x00AA4242
# define FONT_BLACK	0x00000000
# define ANIMATION_FRAME_DELAY	2

# ifndef SINGLE_THREADED
#  define SINGLE_THREADED	1
# endif

/* INIT */
int		init_window_bonus(t_cub *cub, int fullscreen);
void	init_hooks_bonus(t_cub *cub);
int		close_hook_bonus(void *param);
int		load_thread(t_cub *cub, char *scene_file);
int		init_extra(t_scene *scene, char const **param);
int		init_sprite(t_scene *scene, char const **param);
int		init_canvas_bonus(t_cub *cub);

/* DRAW */
void	draw_splash(t_cub *cub, char const *splash_file);
int		load_extras(t_cub *cub);
int		load_sprites(t_cub *cub);
int		cast_sprites(t_cub *cub, t_sprite **arr, t_player *pl);

/* GAME */
int		game_loop_bonus(void *param);
void	player_interact(t_player *player, t_map *map);
void	do_frame_sync(t_cub *cub);
void	display_fps(t_cub *cub);

/* SOUND */
void	*play_intro_sound(void *ignore);

/* UTILS */
void	cleanup_bonus(t_cub *cub);
void	free_extras(t_cub *cub, t_extra *ex);
void	quicksort(t_sprite **tab, int size);

#endif
