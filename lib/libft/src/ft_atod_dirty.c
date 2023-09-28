/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod_dirty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:30:32 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/25 12:00:42 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

double	ft_atod_dirty(char const *str)
{
	char	**tmp;
	double	res;
	double	dec;

	tmp = ft_split(str, '.');
	if (!tmp)
		return (0);
	res = (double)ft_atoi(tmp[0]);
	if (tmp[1])
	{
		if (tmp[2])
			return (free_arr(tmp));
		dec = (double)ft_atoi(tmp[1]);
		while (dec > 1)
			dec /= 10;
		res += dec;
	}
	(void)free_arr(tmp);
	return (res);
}
