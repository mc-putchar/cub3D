/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:37:51 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/03 11:29:57 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	llen;
	size_t	i;

	if (!*little)
		return ((char *)big);
	llen = 0;
	while (little[llen])
		++llen;
	i = 0;
	while (big[i] && i + llen <= len)
	{
		if (!ft_strncmp(&big[i], little, llen))
			return ((char *)&big[i]);
		++i;
	}
	return (NULL);
}
