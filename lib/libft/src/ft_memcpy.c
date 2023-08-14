/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:07:53 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/03 16:00:09 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dest, const void *src, size_t n)
{
	unsigned char		*pd;
	unsigned char const	*ps;

	if (!src && !dest)
		return (NULL);
	pd = dest;
	ps = src;
	while (n--)
		*pd++ = *ps++;
	return (dest);
}
