/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:37:51 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/16 14:12:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	llen;
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	llen = 0;
	while (little[llen])
		++llen;
	i = 0;
	while (big[i] && i + llen <= len)
	{
		j = 0;
		while (j < llen && !(big[i + j] - little[j]))
			++j;
		if (j == llen)
			return ((char *)&big[i]);
		++i;
	}
	return (NULL);
}
