/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:43:19 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/16 17:38:17 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	validate_file(char const *path, int *fd)
{
	if (!path)
		return (1);
	*fd = open(path, O_RDONLY);
	return (*fd < 0);
}

int	validate_extension(char const *path, char const *extension)
{
	size_t	extlen;
	size_t	pathlen;

	if (!path || !extension)
		return (1);
	extlen = ft_strlen(extension);
	pathlen = ft_strlen(path);
	return (pathlen < extlen \
		|| ft_strncmp(path + pathlen - extlen, extension, extlen));
}
