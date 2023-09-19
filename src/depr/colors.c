/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 00:07:44 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/15 00:07:44 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static double	percent_between(int start, int current, int end)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (!distance)
		return (1.0);
	return (placement / distance);
}

static int	get_mix(int start, int end, double percent)
{
	int			red;
	int			green;
	int			blue;
	int			alpha;

	red = (int)((1 - percent) * (start >> 24 & 0xFF) + \
	percent * (end >> 24 & 0xFF));
	green = (int)((1 - percent) * (start >> 16 & 0xFF) + \
	percent * (end >> 16 & 0xFF));
	blue = (int)((1 - percent) * (start >> 8 & 0xFF) + \
	percent * (end >> 8 & 0xFF));
	alpha = (int)((1 - percent) * (start & 0xFF) + \
	percent * (end & 0xFF));
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

int	get_gradient(t_point *curr, t_point *start, t_point *end, \
	t_point *delta)
{
	double	percent;

	if (!start->color)
		start->color = 0xFFFFFFFF;
	if (!end->color)
		end->color = 0xFFFFFFFF;
	if (start->color == end->color)
		return (end->color);
	if (delta->x > delta->y)
		percent = percent_between(start->x, curr->x, end->x);
	else
		percent = percent_between(start->y, curr->y, end->y);
	return (get_mix(start->color, end->color, percent));
}
