/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:49:40 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/15 15:03:41 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lst.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*node;
	void	*content;

	map = (void *)0;
	if (!lst)
		return (map);
	while (lst)
	{
		content = (*f)(lst->content);
		if (!content)
		{
			map = (ft_lstclear(&map, del), (void *)0);
			return (map);
		}
		node = ft_lstnew(content);
		if (!node)
		{
			map = (del(content), ft_lstclear(&map, del), (void *)0);
			return (map);
		}
		ft_lstadd_back(&map, node);
		lst = lst->next;
	}
	return (map);
}
