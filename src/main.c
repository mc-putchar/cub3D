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
	{
		ft_dprintf(STDERR_FILENO, "init error");
		return (EXIT_FAILURE);
	}
	cub.img = mlx_new_image(cub.mlx, 768, 768);
	if (!cub.img || (mlx_image_to_window(cub.mlx, cub.img, 16, 16) < 0))
	{
		ft_dprintf(STDERR_FILENO, "%s", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	ft_printf("Initialized\nDrawing map\n");
	draw_map(&cub);
	mlx_loop(cub.mlx);
	free_map(cub.map, cub.map_height);
	mlx_delete_image(cub.mlx, cub.img);
	mlx_terminate(cub.mlx);
	return (EXIT_SUCCESS);
}
