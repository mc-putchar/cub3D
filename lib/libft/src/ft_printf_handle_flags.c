/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handle_flags.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:59:44 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/14 03:59:46 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*zero_padding(t_format *f, int len)
{
	char	*str;
	char	*tmp;
	char	*pad;

	pad = gen_padding('0', len);
	if (!pad)
		return (NULL);
	if (f->out[0] == '-')
	{
		tmp = ft_strjoin("-", pad);
		if (!tmp)
			return (free(pad), NULL);
		str = ft_strjoin(tmp, f->out + 1);
		return (free(pad), free(tmp), str);
	}
	str = ft_strjoin(pad, f->out);
	return (free(pad), str);
}

int	ft_printf_handle_flags(t_format *f, int fd)
{
	char	*tmp;
	char	*str;

	str = NULL;
	tmp = NULL;
	if (f->width <= (int)ft_strlen(f->out))
		return (ft_print(f->out, 0, ft_strlen(f->out), fd));
	if (f->flags & 1)
	{
		tmp = gen_padding(' ', f->width - ft_strlen(f->out));
		str = ft_strjoin(f->out, tmp);
	}
	else if (f->flags & (1 << 1) && f->prec < 0 && f->specifier < 7)
		str = zero_padding(f, f->width - ft_strlen(f->out));
	else
	{
		tmp = gen_padding(' ', f->width - ft_strlen(f->out));
		str = ft_strjoin(tmp, f->out);
	}
	if (tmp)
		free(tmp);
	free(f->out);
	f->out = str;
	return (ft_print(f->out, 0, ft_strlen(f->out), fd));
}

int	ft_printf_char_flags(t_format *f, int fd)
{
	char	*pad;
	int		c;

	if (f->width < 2)
		return (write(fd, &(f->out[0]), 1));
	c = 0;
	pad = gen_padding(' ', f->width - 1);
	if (!pad)
		return (0);
	if (f->flags & 1)
	{
		c += write(fd, &(f->out[0]), 1);
		c += write(fd, pad, f->width - 1);
	}
	else
	{
		c += write(fd, pad, f->width - 1);
		c += write(fd, &(f->out[0]), 1);
	}
	return (free(pad), c);
}

int	ft_printf_format(t_format *f, va_list ap, int fd)
{
	static t_converter	con[PRINTF_CONVERTERS] = {&ft_printf_char, \
	&ft_printf_int, &ft_printf_int, &ft_printf_uint, &ft_printf_hex, \
	&ft_printf_uhex, &ft_printf_str, &ft_printf_ptr};
	int					c;

	if (!f || !ap)
		return (0);
	if (!(f->specifier))
		return (write(fd, &"%", 1));
	if (f->specifier > 6)
		f->u_arg.p = va_arg(ap, void *);
	else if (f->specifier > 3)
		f->u_arg.ui = (unsigned int)va_arg(ap, unsigned int);
	else
		f->u_arg.i = va_arg(ap, int);
	f->out = con[f->specifier - 1](f);
	if (!f->out)
		return (0);
	if (f->specifier == 1)
		c = ft_printf_char_flags(f, fd);
	else
		c = ft_printf_handle_flags(f, fd);
	free(f->out);
	return (c);
}
