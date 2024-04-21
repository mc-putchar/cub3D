/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_converters_hex.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:40:10 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/16 23:06:26 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_printf.h"
#include "libft.h"

static char	*to_hex_str(unsigned long long n, int offset);

char	*hex_con(t_format *fmt)
{
	char	*tmp;

	tmp = to_hex_str(fmt->u_arg.ui, HEX_OFFSET_LOWER);
	if (!tmp)
		return (NULL);
	if (!fmt->precision && tmp[0] == '0')
		tmp[0] = 0;
	fmt->len = ft_strlen(tmp);
	return (tmp);
}

char	*uhex_con(t_format *fmt)
{
	char	*tmp;

	tmp = to_hex_str(fmt->u_arg.ui, HEX_OFFSET_UPPER);
	if (!tmp)
		return (NULL);
	if (!fmt->precision && tmp[0] == '0')
		tmp[0] = 0;
	fmt->len = ft_strlen(tmp);
	return (tmp);
}

char	*ptr_con(t_format *fmt)
{
	char	*tmp;

	if (!fmt->u_arg.p)
	{
		fmt->len = 5;
		return (ft_strdup("(nil)"));
	}
	tmp = ft_strjoin("0x", \
		to_hex_str((unsigned long long)fmt->u_arg.p, HEX_OFFSET_LOWER));
	if (tmp)
		fmt->len = ft_strlen(tmp);
	return (tmp);
}

static int	count_digits(unsigned long long n)
{
	int	d;

	d = 0;
	if (!n)
		return (1);
	while (n)
	{
		n >>= 4;
		++d;
	}
	return (d);
}

char	*to_hex_str(unsigned long long n, int offset)
{
	char	*hex;
	int		i;

	i = count_digits(n);
	hex = malloc(i + 1);
	if (!hex)
		return (NULL);
	if (!n)
		hex[0] = '0';
	hex[i] = 0;
	while (n && i--)
	{
		hex[i] = (n & 0xF) + '0';
		if (hex[i] > '9')
			hex[i] += offset;
		n >>= 4;
	}
	return (hex);
}
