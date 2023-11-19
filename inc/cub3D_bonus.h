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

void		interact(t_cub *cub);
void		display_fps(t_cub *cub);
void		draw_hud(t_mlx_image *img);

#endif