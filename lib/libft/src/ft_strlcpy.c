/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:58:02 by mcutura           #+#    #+#             */
/*   Updated: 2023/04/02 16:28:11 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (size && src && dst)
	{
		if (size > srclen)
			size = srclen + 1;
		i = 0;
		while (i < size - 1)
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = 0;
	}
	return (srclen);
}
