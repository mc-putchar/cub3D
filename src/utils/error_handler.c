/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:27:27 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/14 23:27:27 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	throw_error(char const *msg)
{
	ft_dprintf(STDERR_FILENO, "Error\n%s\n", msg);
	return (1);
}

int	throw_error_free(char const *msg, void (*f)(), void *ptr)
{
	ft_dprintf(STDERR_FILENO, "Error\n%s\n", msg);
	f(ptr);
	return (1);
}
