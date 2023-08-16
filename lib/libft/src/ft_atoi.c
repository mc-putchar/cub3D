/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:38:51 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/03 11:32:15 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	return (c == 32 || (c > 8 && c < 14));
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	neg;

	neg = 1;
	res = 0;
	while (*nptr && ft_isspace((int) *nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (res * neg);
}
