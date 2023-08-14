/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 22:21:50 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/27 01:06:09 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print(const char *str, int s, int e, int fd)
{
	int	ret;
	int	printed;
	int	remain;

	ret = 0;
	remain = -1;
	while (remain)
	{
		printed = write(fd, str + s, e - s);
		if (printed == -1)
			continue ;
		remain = e - s - printed;
		ret += printed;
		s += printed;
	}
	return (ret);
}

int	indexof(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	get_min_width(const char *fmt, int *i)
{
	int	width;

	width = 0;
	while (ft_isdigit(fmt[*i]))
		width = width * 10 + fmt[(*i)++] - '0';
	return (width);
}

int	get_precision(const char *fmt, int *i)
{
	int	precision;
	int	reset;

	precision = 0;
	reset = 0;
	if (fmt[(*i) + 1] == '-')
		reset = -1;
	while (ft_isdigit(fmt[++(*i)]))
		precision = precision * 10 + fmt[*i] - '0';
	if (reset)
		return (reset);
	return (precision);
}

char	*gen_padding(int c, int n)
{
	char	*str;

	str = malloc(n + 1);
	if (!str)
		return (NULL);
	str[n] = 0;
	while (n--)
		str[n] = (unsigned char)c;
	return (str);
}
