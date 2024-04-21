/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:37:55 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/16 14:06:30 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	i;
	size_t	t;

	if (!nmemb || !size)
		return (malloc(0));
	if ((size_t)(-1) / size < nmemb \
	|| ((size_t)(-1) / size == nmemb && (size_t)(-1) % size))
		return (NULL);
	t = nmemb * size;
	p = malloc(t);
	if (!p)
		return (p);
	i = 0;
	while (i + sizeof(size_t) <= t)
	{
		((size_t *)p)[i / sizeof(size_t)] = 0;
		i += sizeof(size_t);
	}
	while (i < t)
		((unsigned char *)p)[i++] = 0;
	return (p);
}
