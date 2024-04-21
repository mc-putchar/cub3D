/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:58:38 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/16 14:10:50 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>

ssize_t	ft_putendl_fd(char *s, int fd)
{
	ssize_t	i;
	size_t	len;

	len = 0;
	while (s[len])
		++len;
	i = write(fd, s, len);
	if (i < 0)
		return (i);
	if (write(fd, "\n", 1) < 1)
		return (i);
	return (++i);
}
