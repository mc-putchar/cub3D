/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:47:29 by mcutura           #+#    #+#             */
/*   Updated: 2024/05/02 11:57:02 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	free_arr(char **arr);

double	ft_atod(char const *str)
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
		dec = (double)ft_atoi(tmp[1]);
		while (dec > 1)
			dec /= 10;
		res += dec;
	}
	(void)free_arr(tmp);
	return (res);
}

int	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (1);
}
