/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 03:06:03 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/20 03:26:54 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "cub3D_bonus.h"

static int	set_extra_params(t_extra *ex, char const **param);

int	init_extra(t_scene *scene, char const **param)
{
	int		fd;
	t_extra	*ex;
	t_extra	*node;

	if (!param[1])
		return (throw_error(PARAM_ERROR));
	if (validate_file(param[1], &fd))
		return (throw_error(BAD_FILEPATH));
	if (!ft_strncmp(param[0], "S", 2) || !ft_strncmp(param[0], "A", 2))
		return (init_sprite(scene, param));
	ex = malloc(sizeof(t_extra));
	if (!ex || set_extra_params(ex, param))
		return (throw_error(MALLOC_FAIL));
	if (!scene->extras)
		scene->extras = ex;
	else
	{
		node = scene->extras;
		while (node->next)
			node = node->next;
		node->next = ex;
	}
	return (0);
}

int	set_extra_params(t_extra *ex, char const **param)
{
	ex->key = ft_strdup(param[0]);
	if (!ex->key)
		return (1);
	ex->value = ft_strdup(param[1]);
	if (!ex->value)
	{
		free(ex->key);
		return (1);
	}
	ex->next = NULL;
	ex->isloaded = 0;
	return (0);
}
