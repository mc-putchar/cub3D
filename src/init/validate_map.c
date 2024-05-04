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
	size_t	i;
	size_t	j;

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

inline static int	check(t_map *map, size_t x, size_t y)
{
	return (x >= map->width || y >= map->height || map->val[y][x] == ' ');
}

int	validate_map(t_map *map)
{
	size_t	i;
	size_t	j;

	if ((!BONUS && verify_symbols(map, MAP_SYMS)) \
	|| (BONUS && verify_symbols(map, MAP_SYMS_BONUS)))
		return (throw_error(UNKNOWN_MAPSYM));
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
					return (throw_error(MAP_NOT_CLOSED));
			}
			++i;
		}
		++j;
	}
	return (0);
}
