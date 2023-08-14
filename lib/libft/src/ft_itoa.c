/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 05:12:32 by mcutura           #+#    #+#             */
/*   Updated: 2023/07/07 05:22:33 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int		len;

	len = 1;
	if (n < 0)
		++len;
	while (n && ++len)
		n /= 10;
	return (len);
}

static int	ft_uintlen(unsigned int n)
{
	int		len;

	len = 1;
	while (n && ++len)
		n /= 10;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		neg;

	if (!n)
		return (ft_strdup("0"));
	len = ft_intlen(n);
	str = malloc(len);
	if (!str)
		return (NULL);
	str[--len] = '\0';
	neg = 1;
	if (n < 0)
		neg = -1;
	while (n)
	{
		str[--len] = (n % 10) * neg + '0';
		n /= 10;
	}
	if (neg == -1)
		str[0] = '-';
	return (str);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		len;

	if (!n)
		return (ft_strdup("0"));
	len = ft_uintlen(n);
	str = malloc(len);
	if (!str)
		return (NULL);
	str[--len] = '\0';
	while (n)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
