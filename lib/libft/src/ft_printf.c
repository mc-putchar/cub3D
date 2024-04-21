/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:04:33 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/16 21:33:20 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "ft_printf.h"

int			ft_vprintf(int fd, const char *format, va_list ap);
static int	print_substr(const char *str, int start, int end, int fd);
static int	print_formatted(const char *fmt, int *i, va_list ap, int fd);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vprintf(STDOUT_FILENO, format, ap);
	va_end(ap);
	return (ret);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vprintf(fd, format, ap);
	va_end(ap);
	return (ret);
}

int	ft_vprintf(int fd, const char *format, va_list ap)
{
	int		ret;
	int		i;
	int		j;

	ret = 0;
	i = -1;
	j = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			j = print_substr(format, j, i, fd);
			if (j == -1)
				return (-1);
			ret += j;
			j = print_formatted(format, &i, ap, fd);
			if (j == -1)
				return (-1);
			ret += j;
			j = i + 1;
		}
	}
	if (i > j)
		ret += print_substr(format, j, i, fd);
	return (ret);
}

int	print_substr(const char *str, int start, int end, int fd)
{
	ssize_t	printed;
	int		remain;
	int		ret;

	ret = 0;
	remain = end - start;
	while (remain > 0)
	{
		printed = write(fd, str + start, end - start);
		if (printed < 0)
			return (-1);
		remain = end - start - (int)printed;
		ret += printed;
		start += printed;
	}
	return (ret);
}

int	print_formatted(const char *fmt, int *i, va_list ap, int fd)
{
	static t_converter const	converter[8] = {char_con, int_con, int_con, \
		uint_con, hex_con, uhex_con, str_con, ptr_con};
	t_format					format;
	int							ret;

	ret = 0;
	parse_format(&format, fmt, i);
	if (format.specifier < 0)
		return (0);
	if (!format.specifier)
		return (write(fd, &"%", 1));
	if (format.specifier > 6)
		format.u_arg.p = va_arg(ap, void *);
	else if (format.specifier > 3)
		format.u_arg.ui = (unsigned int)va_arg(ap, unsigned int);
	else
		format.u_arg.i = va_arg(ap, int);
	format.out = converter[format.specifier - 1](&format);
	if (!format.out)
		return (-1);
	// TODO
	// apply flag modifications
	ret = write(fd, format.out, format.len);
	free(format.out);
	return (ret);
}
