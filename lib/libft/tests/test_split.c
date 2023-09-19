/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:28:36 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/13 14:28:36 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int main(void)
{
	char const	*test[10];
	char		**res;
	int			idx;

	test[0] = "";
	test[1] = "Quick brown fox jumps over lazy dog!";
	test[2] = " Quick brown fox jumps over lazy dog! ";
	test[3] = "          ";
	test[4] = "Quickbrownfox,jumpsoverlazydog!";
	test[5] = "   Quick   brown   fox   jumps   over   lazy   dog!   ";
	test[6] = " Numbers 0 -1 42 +/-10 = X*Y!!";
	test[7] = "1.2 * 2,4";
	test[8] = "102		24		42";
	test[9] = "12392433405672356239582358 569212075256785657896235";

	for (int i = 0; i < 10; ++i) {
		res = ft_splits(test[i], " ,a0\t");
		// res = ft_split(test[i], ' ');
		printf("TEST SET %d\nSTRING: <%s>\nRESULT:\n", i, test[i]);
		idx = -1;
		while (res[++idx])
			printf("\t[%d]<%s>\n", idx, res[idx]);
		printf("END\n\n");
		while (idx + 1)
			free(res[idx--]);
		free(res);
	}
	return (0);
}
