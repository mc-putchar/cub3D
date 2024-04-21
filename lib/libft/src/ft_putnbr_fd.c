/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:00:52 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/16 14:12:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>

ssize_t	ft_putnbr_fd(int n, int fd)
{
	size_t	len;
	char	num[20];
	int		d;

	len = 0;
	if (n < 0 && ++len)
		num[0] = '-';
	d = n;
	while (++len && (d < -9 || d > 9))
		d /= 10;
	if (len > 20)
		return (-1);
	d = len;
	if (!n)
		num[0] = '0';
	while (n)
	{
		num[--d] = n % 10 * ((n > 0) * 2 - 1) + '0';
		n /= 10;
	}
	return (write(fd, num, len));
}
