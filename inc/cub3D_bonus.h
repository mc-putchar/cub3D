/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 09:12:36 by mcutura           #+#    #+#             */
/*   Updated: 2023/11/19 09:12:36 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/* for FPS calculation and sync */
# include <sys/time.h>

# include "cub3D.h"

# undef TITLE
# define TITLE		"Cub3D: Peer of Destiny"
# define HUD_HEIGHT	290
# define LOGO_FILE	"res/logo.xpm"
# define INFO_FILE	"res/bios.nfo"
# define SPLSH_FILE	"res/cubcover.xpm"
/* TODO figure out how to set font portably (maybe make one?)
# define FONT		"-sony-fixed-medium-r-normal-*-16-*-*-*-*-*-iso8859-1"
# define FONT2		"-sony-fixed-medium-r-normal-*-24-*-*-*-*-*-iso8859-1"
# define FONT3		"-schumacher-clean-*-*-*-*-17-*-*-*-*-*-iso10646-1"
*/
# define FONT_DEF	"-misc-fixed-*-*-*-*-17-*-*-*-*-*-*-*"
# define FONT_COLOR	0x0042AA42
# define FONT_ERROR	0x00AA4242
# define FONT_BLACK	0x00000000

/* INIT */
int			img_gen(void *mlx, t_mlx_image *img, int width, int height);
int			tex_load(void *mlx, t_mlx_image *img, char *path);
int			set_animation(t_sprite *spr, char const **param);
void		free_animation(void *mlx, t_animation *anim);

/* DRAW */
void		draw_splash(t_cub *cub);
int			draw_intro(t_cub *cub);
void		init_hud(t_cub *cub);
void		draw_hud(t_cub *cub);
void		put_circle(t_mlx_image *img, t_point *center, int r, int color);

/* GAME */
void		interact(t_cub *cub);
void		item_pickup(t_cub *cub, t_scene *scn);
void		register_pickup(t_sprite *spr, char const *type);
void		key_pickup(t_cub *cub, t_mlx_image *img);
void		phone_pickup(t_cub *cub, t_mlx_image *img);
void		badge_pickup(t_cub *cub, t_mlx_image *img);

/* UTILS */
void		display_fps(t_cub *cub);
int			ft_sleep(unsigned int milisecs);
void		typewrite(t_cub *cub, t_point *p, char *font, char **text);

#endif