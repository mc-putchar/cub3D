/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:14:01 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/12 20:24:31 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*prefix_checks(char *str, int *neg)
{
	int	stage;

	stage = 0;
	while (*str)
	{
		if (stage == 0 && ft_isspace(*str))
		{
			str++;
			continue ;
		}
		else
			stage++;
		if (stage > 0 && (*str == '-' || *str == '+'))
		{
			if (*str++ == '-')
				*neg *= -1;
		}
		else
			return (str);
	}
	return (str);
}

static int	is_valid_base(char *base)
{
	int	base_n;
	int	i;

	base_n = 0;
	while (base[base_n])
	{
		if (base[base_n] == '+' || base[base_n] == '-')
			return (0);
		if (ft_isspace(base[base_n]))
			return (0);
		i = base_n + 1;
		while (base[i])
			if (base[base_n] == base[i++])
				return (0);
		base_n++;
	}
	if (base_n == 1)
		return (0);
	return (base_n);
}

static int	value_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int		b;
	int		res;
	int		neg;
	char	val;

	neg = 1;
	res = 0;
	b = is_valid_base(base);
	if (b)
	{
		str = prefix_checks(str, &neg);
		while (*str)
		{
			val = value_in_base(*str++, base);
			if (val < 0)
				return (res * neg);
			res = res * b + val;
		}
	}
	return (res * neg);
}
