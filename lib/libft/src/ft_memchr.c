/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:39:05 by mcutura           #+#    #+#             */
/*   Updated: 2023/03/20 12:29:45 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char const	*p;

	p = s;
	while (n--)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		++p;
	}
	return (NULL);
}
