/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 05:21:52 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/15 05:21:52 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

typedef struct s_point
{
	float	x;
	float	y;
	int		color;
}	t_point;

typedef struct s_pointInt
{
	int	x;
	int	y;
	int	color;
}	t_pointInt;

#endif
