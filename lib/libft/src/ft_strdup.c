/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:30:47 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/16 14:12:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*cpy;

	len = 0;
	while (s[len])
		++len;
	cpy = malloc(len + 1);
	if (!cpy)
		return (NULL);
	cpy[len] = 0;
	i = 0;
	while (i + sizeof(int) <= len)
	{
		((int *)cpy)[i / sizeof(int)] = ((int *)s)[i / sizeof(int)];
		i += sizeof(int);
	}
	while (i < len)
	{
		cpy[i] = s[i];
		++i;
	}
	return (cpy);
}
