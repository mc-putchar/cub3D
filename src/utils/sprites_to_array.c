/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:41:29 by mcutura           #+#    #+#             */
/*   Updated: 2023/10/19 19:41:29 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	sprites_to_array(t_scene *scn)
{
	t_size		i;
	t_sprite	*spr;

	scn->spr_arr = malloc(sizeof(t_sprite *) * scn->n_sprites);
	if (!scn->spr_arr)
		return (throw_error("Memory allocation failed"));
	spr = scn->sprites;
	i = 0;
	while (i < scn->n_sprites && spr)
	{
		scn->spr_arr[i++] = spr;
		spr = spr->next;
	}
	return (0);
}
