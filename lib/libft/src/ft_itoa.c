/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:34:55 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/16 14:07:16 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	intlen(int n)
{
	size_t	len;

	len = (n < 0);
	while (++len && (n > 9 || n < -9))
		n /= 10;
	return (len);
}

static size_t	uintlen(unsigned int n)
{
	size_t	len;

	len = 1;
	while (n > 9 && ++len)
		n /= 10;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		neg;

	len = intlen(n);
	str = malloc(++len);
	if (!str)
		return (NULL);
	str[--len] = '\0';
	neg = 1;
	if (n < 0)
		neg = -1;
	if (!n)
		str[0] = '0';
	while (n)
	{
		str[--len] = (n % 10) * neg + '0';
		n /= 10;
	}
	if (neg < 0)
		str[0] = '-';
	return (str);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	size_t	len;

	len = uintlen(n);
	str = malloc(++len);
	if (!str)
		return (NULL);
	str[--len] = '\0';
	if (!n)
		str[0] = '0';
	while (n)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
