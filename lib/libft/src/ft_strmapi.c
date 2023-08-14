/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:51:57 by mcutura           #+#    #+#             */
/*   Updated: 2023/04/02 17:04:14 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*map;
	size_t	len;

	len = ft_strlen(s);
	map = malloc(len + 1);
	if (!map)
		return (NULL);
	map[len] = 0;
	while (len--)
		map[len] = (*f)((unsigned int)len, s[len]);
	return (map);
}
