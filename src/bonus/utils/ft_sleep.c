/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 09:37:06 by mcutura           #+#    #+#             */
/*   Updated: 2023/11/19 09:37:06 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_sleep(unsigned int milisecs)
{
	unsigned int	passed;

	passed = 0;
	while (passed < milisecs)
	{
		if (usleep(50000))
			return (1);
		passed += 50;
	}
	return (0);
}