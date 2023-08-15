/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:30:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/14 17:30:29 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "MLX42/MLX42.h"
# include "libft.h"

# include "point.h"

# define WIN_HEIGHT		800
# define WIN_WIDTH		800
# define BPP			sizeof(int)
# define MAP_SQUARE		32

typedef struct s_player
{
	t_point	position;
	float	orientation;
}	t_player;

typedef struct s_cub
{
	mlx_t		*mlx;
	t_player	player;
	char		**map;
	int			map_width;
	int			map_height;
	mlx_image_t	*img;
}	t_cub;


int		init_data(t_cub *cub);
int		drawMap(t_cub *cub);
void	drawPlayer(t_cub *cub);
void	drawSquare(mlx_image_t *img, t_pointInt position, int size, int color);

int	getColor(int r, int g, int b, int a);

#endif
