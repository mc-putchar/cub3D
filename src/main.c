/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:29:49 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/14 17:29:49 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(void)
{
	t_cub	cub;

	if (init_data(&cub))
		error_handler("Init failure.");
	ft_printf("Init complete\n");
	mlx_loop(cub.mlx);
	free_map(cub.map, cub.map_height);
	mlx_delete_image(cub.mlx, cub.img);
	mlx_terminate(cub.mlx);
	return (EXIT_SUCCESS);
}
