/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:42:37 by mcutura           #+#    #+#             */
/*   Updated: 2023/03/20 12:32:12 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void const *s1, void const *s2, size_t n)
{
	int					diff;
	unsigned char const	*p1;
	unsigned char const	*p2;

	p1 = s1;
	p2 = s2;
	diff = 0;
	while (!diff && n--)
		diff = *p1++ - *p2++;
	return (diff);
}
