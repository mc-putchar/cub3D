/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 05:35:21 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/16 14:12:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joined;
	size_t	len;
	size_t	i;

	i = 0;
	while (s1[i])
		++i;
	len = 0;
	while (s2[len])
		++len;
	len += i + 1;
	joined = malloc(len);
	if (!joined)
		return (NULL);
	joined[--len] = 0;
	while (len-- > i)
		joined[len] = s2[len - i];
	while (i--)
		joined[i] = s1[i];
	return (joined);
}
