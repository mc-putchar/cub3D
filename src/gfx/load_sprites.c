/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:15:31 by mcutura           #+#    #+#             */
/*   Updated: 2024/05/02 20:00:35 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

static int	convert_to_array(t_cub *cub, t_sprite *spr, int siz);

int	load_sprites(t_cub *cub)
{
	t_mlx_image	*img;
	t_sprite	*tmp;

	tmp = cub->scene->sprites;
	while (tmp)
	{
		img = malloc(sizeof(t_mlx_image));
		if (!img)
			return (throw_error(MALLOC_FAIL));
		if (load_texture(cub->mlx, img, tmp->texture))
			return (free(img), 1);
		free(tmp->texture);
		tmp->texture = img;
		tmp->isloaded = 1;
		tmp = tmp->next;
	}
	return (convert_to_array(cub, cub->scene->sprites, cub->scene->n_sprites));
}

int	convert_to_array(t_cub *cub, t_sprite *spr, int siz)
{
	t_sprite	**arr;
	int			i;

	arr = malloc(sizeof(t_sprite *) * siz);
	if (!arr)
		return (throw_error(MALLOC_FAIL));
	i = 0;
	while (i < siz && spr)
	{
		arr[i++] = spr;
		spr = spr->next;
	}
	((t_bonus_data *)cub->bonus)->sprite_arr = arr;
	return (0);
}
