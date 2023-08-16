/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 05:19:27 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/02 17:55:20 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	memsize;
	size_t	i;
	char	*sub;

	memsize = 1;
	i = 0;
	if (s)
	{
		while (s[i] && i < start)
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
