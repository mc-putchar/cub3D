/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:09:45 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/16 17:09:45 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_menu(void)
{
	return ;
}

void	init_menu(t_cub *cub)
{
	cub->menu.img = mlx_new_image(cub->mlx, MENU_WIDTH, MENU_HEIGHT);
	cub->menu.title = ft_strdup("Cub 3D: Episode 1: The Cubbing");
	cub->menu.items = malloc(sizeof(char *) * 5);
	if (!cub->menu.items)
		error_handler(strerror(errno));
}
