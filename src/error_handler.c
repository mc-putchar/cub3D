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

void	error_handler(char const *message)
{
	ft_dprintf(STDERR_FILENO, "ERROR: %s\n", message);
	exit(EXIT_FAILURE);
}
