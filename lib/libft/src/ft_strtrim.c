/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 05:43:39 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/03 12:49:21 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(const char c, const char *set)
{
	if (!set)
		return (0);
	if (!c)
		return (1);
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*trim;
	int		start;
	int		end;
	size_t	len;

	start = 0;
	while (s1[start] && is_set(s1[start], set))
		++start;
	end = ft_strlen(s1);
	while (end-- > start && is_set(s1[end], set))
		;
	len = 0;
	if (end >= start)
		len = (size_t)(end - start + 1);
	trim = ft_substr(s1, start, len);
	return (trim);
}
