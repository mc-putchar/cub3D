/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typewrite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 10:00:42 by mcutura           #+#    #+#             */
/*   Updated: 2023/11/19 10:00:42 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

#define OFFSET_H	10
#define OFFSET_V	18

void	typewrite(t_cub *cub, t_point *p, char *font, char **text)
{
	int const	font_color = 0x0042AA42;
	char		*line;
	char		typed;
	int			x;
	int			y;

	// mlx_set_font(cub->mlx, cub->win, font);
	(void)font;
	y = p->y;
	while (*text)
	{
		x = p->x;
		line = *text;
		mlx_string_put(cub->mlx, cub->win, x, y, font_color, "$>");
		x += (2 * OFFSET_H);
		ft_sleep(1000);
		while (*line)
		{
			typed = *line++;
			mlx_string_put(cub->mlx, cub->win, x, y, font_color, &typed);
			ft_sleep(50);
			x += OFFSET_H;
		}
		++text;
		y += OFFSET_V;
	}
}
