/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 05:19:27 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/16 14:06:52 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	memsize;
	size_t	i;
	char	*sub;

	memsize = 1;
	i = 0;
	if (s)
	{
		while (s[i] && i < (size_t)start)
			++i;
		while (s[i++] && len--)
			++memsize;
	}
	sub = malloc(memsize);
	if (!sub)
		return (NULL);
	sub[--memsize] = 0;
	while (memsize--)
		sub[memsize] = s[start + memsize];
	return (sub);
}
