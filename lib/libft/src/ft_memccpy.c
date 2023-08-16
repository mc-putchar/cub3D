/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:14:02 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/03 11:23:39 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*pd;
	unsigned char const	*ps;

	pd = dest;
	ps = src;
	while (n--)
	{
		*pd = *ps++;
		if (*pd++ == c)
			return (pd);
	}
	return (NULL);
}
