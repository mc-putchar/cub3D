/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:32:34 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/03 16:20:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*cptr;

	cptr = (void *)0;
	while (*s)
	{
		if (*s == (char)c)
			cptr = (char *)s;
		++s;
	}
	if (!(char)c)
		cptr = (char *)s;
	return (cptr);
}
