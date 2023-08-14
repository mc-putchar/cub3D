/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:00:52 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/03 16:25:19 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	ft_putn(int n, int fd)
{
	ssize_t	c;

	c = 0;
	if (!n)
		return (0);
	if (n < 0)
	{
		c += ft_putchar_fd('-', fd);
		if (n < -9)
			c += ft_putn(n / 10 * -1, fd);
		c += ft_putchar_fd(n % 10 * -1 + '0', fd);
	}
	else
	{
		if (n > 9)
			c += ft_putn(n / 10, fd);
		c += ft_putchar_fd(n % 10 + '0', fd);
	}
	return (c);
}

ssize_t	ft_putnbr_fd(int n, int fd)
{
	if (!n)
		return (ft_putchar_fd('0', fd));
	else
		return (ft_putn(n, fd));
}
