/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 03:53:48 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/28 04:05:13 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list **head)
{
	t_list	*node;

	if (!head || !*head)
		return (NULL);
	node = *head;
	*head = (*head)->next;
	return (node);
}
