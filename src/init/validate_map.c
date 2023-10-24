/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 03:17:33 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/29 05:06:58 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	verify_symbols(t_map *map, char const *sym)
{
	t_size	i;
	t_size	j;

	j = 0;
	while (j < map->height)
	{
		i = 0;
		while (i < map->width)
		{
			if (!ft_strchr(sym, map->val[j][i]))
				return (1);
			++i;
		}
		++j;
	}
	return (0);
}

inline static int	check(t_map *map, t_size x, t_size y)
{
	return (x >= map->width || y >= map->height || map->val[y][x] == ' ');
}

int	validate_map(t_map *map)
{
	t_size	i;
	t_size	j;

	if (verify_symbols(map, " 01DL"))
		return (throw_error("Unrecognized symbol on map"));
	j = 0;
	while (j < map->height)
	{
		i = 0;
		while (i < map->width)
		{
			if (map->val[j][i] != '1' && map->val[j][i] != ' ')
			{
				if (check(map, i + 1, j) || (i && check(map, i - 1, j)) || \
					check(map, i, j + 1) || (j && check(map, i, j - 1)))
					return (throw_error("Map not enclosed by walls"));
			}
			++i;
		}
		++j;
	}
	return (0);
}
