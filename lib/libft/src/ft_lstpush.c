/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 03:58:27 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/29 02:45:58 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstpush(t_list **head, void *content)
{
	t_list	*node;

	if (!head)
		return (1);
	node = ft_lstnew(content);
	if (!node)
		return (1);
	ft_lstadd_front(head, node);
	return (0);
}
