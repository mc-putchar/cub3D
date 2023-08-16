/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:54:46 by mcutura           #+#    #+#             */
/*   Updated: 2023/06/08 13:29:17 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	parse_flags(const char *fmt, int *i)
{
	int	flags;
	int	j;

	flags = 0;
	j = 0;
	while (fmt[*i] && j != -1)
	{
		j = indexof(fmt[*i], FT_PRINTF_FLAGS);
		if (j == -1)
			break ;
		flags |= 1 << j;
		++(*i);
	}
	return (flags);
}

static t_format	*init_format(void)
{
	t_format	*fmt;

	fmt = malloc(sizeof(t_format));
	if (!fmt)
		return (NULL);
	fmt->flags = 0;
	fmt->width = 0;
	fmt->prec = -1;
	return (fmt);
}

/*
**	This function parses the format string, moving the index along
**	to the specifier at the end.
**	Returns the struct for the required format of next argument.
**	Use free() to deallocate the struct.
**	Format: %[flags][width][.precision]type
**	[size] not implemented
*/
static t_format	*parse_format(const char *fmt, int *i)
{
	t_format	*f;
	int			j;

	f = init_format();
	if (!f)
		return (NULL);
	if (fmt[*i])
	{
		f->flags = parse_flags(fmt, i);
		if (ft_isdigit(fmt[*i]))
			f->width = get_min_width(fmt, i);
		if (fmt[*i] == '.')
			f->prec = get_precision(fmt, i);
		j = indexof(fmt[*i], FT_PRINTF_SPECIFIERS);
		if (j != -1)
			return (f->specifier = j, f);
	}
	return (NULL);
}

int	ft_printf(const char *format, ...)
{
	int			c;
	int			s;
	int			i;
	va_list		ap;
	t_format	*f;

	c = 0;
	i = -1;
	s = 0;
	va_start(ap, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			if (i++ > s)
				c += ft_print(format, s, i - 1, STDOUT_FILENO);
			f = parse_format(format, &i);
			c += ft_printf_format(f, ap, STDOUT_FILENO);
			free(f);
			s = i + 1;
		}
	}
	if (i > s)
		c += ft_print(format, s, i, STDOUT_FILENO);
	return (va_end(ap), c);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int			c;
	int			s;
	int			i;
	va_list		ap;
	t_format	*f;

	c = 0;
	i = -1;
	s = 0;
	va_start(ap, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			if (i++ > s)
				c += ft_print(format, s, i - 1, fd);
			f = parse_format(format, &i);
			c += ft_printf_format(f, ap, fd);
			free(f);
			s = i + 1;
		}
	}
	if (i > s)
		c += ft_print(format, s, i, fd);
	return (va_end(ap), c);
}
