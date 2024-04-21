/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_converters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:14:55 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/16 22:45:28 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

char	*char_con(t_format *fmt)
{
	char	*tmp;

	tmp = malloc(2);
	if (!tmp)
	{
		fmt->len = 0;
		return (NULL);
	}
	fmt->len = 1;
	tmp[0] = (char)fmt->u_arg.i;
	tmp[1] = 0;
	return (tmp);
}

char	*int_con(t_format *fmt)
{
	char	*tmp;

	tmp = ft_itoa(fmt->u_arg.i);
	if (!tmp)
		return (NULL);
	if (!fmt->precision && tmp[0] == '0')
		tmp[0] = 0;
	fmt->len = ft_strlen(tmp);
	return (tmp);
}

char	*uint_con(t_format *fmt)
{
	char	*tmp;

	tmp = ft_itoa(fmt->u_arg.i);
	if (!tmp)
		return (NULL);
	if (!fmt->precision && tmp[0] == '0')
		tmp[0] = 0;
	fmt->len = ft_strlen(tmp);
	return (tmp);
}

char	*str_con(t_format *fmt)
{
	if (!fmt->u_arg.p)
	{
		fmt->len = 6;
		if (fmt->precision)
			return (ft_strdup("(null)"));
		fmt->len = 0;
		return (ft_strdup(""));
	}
	fmt->len = ft_strlen((const char *)fmt->u_arg.p);
	return (ft_strdup((const char *)fmt->u_arg.p));
}
