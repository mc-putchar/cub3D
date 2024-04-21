/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 05:43:39 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/16 14:06:45 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static inline int	is_set(const char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*trim;
	size_t	len;
	size_t	start;
	size_t	end;

	len = 0;
	while (s1[len])
		++len;
	start = 0;
	while (start < len && is_set(s1[start], set))
		++start;
	end = len;
	while (--end > start && is_set(s1[end], set))
		;
	trim = malloc(++end - start + 1);
	if (!trim)
		return (NULL);
	len = 0;
	while (len < end - start)
	{
		trim[len] = s1[start + len];
		++len;
	}
	trim[len] = 0;
	return (trim);
}
