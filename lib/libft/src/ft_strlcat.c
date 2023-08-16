/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:05:44 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/03 11:26:25 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = ft_strlen(src);
	dstlen = 0;
	while (dst[dstlen] && dstlen < size)
		++dstlen;
	i = 0;
	if (srclen && size)
	{
		while (*src && i + dstlen < size - 1)
		{
			dst[dstlen + i] = *src++;
			++i;
		}
	}
	if (dstlen + i < size)
		dst[dstlen + i] = 0;
	return (dstlen + srclen);
}
