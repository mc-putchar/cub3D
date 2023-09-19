/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:56:48 by mcutura           #+#    #+#             */
/*   Updated: 2023/09/15 22:56:48 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*  
 * with extra space
 */
static int	convert_map(t_map *map, t_list *maplist)
{
	size_t	idx;
	size_t	padding;

	idx = 0;
	map->height = ft_lstsize(maplist);
	map->val = malloc(sizeof(char *) * map->height);
	if (!map->val)
		return (throw_error("Map memory allocation failed"));
	while (idx < map->height && maplist)
	{
		map->val[idx] = malloc(map->width + 1);
		if (!map->val[idx])
			return (free_map(map->val, idx + 1), \
			throw_error("Map memory allocation failed"));
		(void)ft_strlcpy(map->val[idx], maplist->content, map->width + 1);
		padding = map->width - ft_strlen(maplist->content);
		while (padding--)
			map->val[idx][map->width - 1 - padding] = ' ';
		map->val[idx][map->width] = 0;
		maplist = maplist->next;
		idx++;
	}
	return (0);
}

static int	add_line_to_list(char *line, t_list **list, size_t *width)
{
	char	*tmp;
	t_list	*node;
	size_t	linelen;

	tmp = ft_strtrim(line, "\r\n");
	free(line);
	if (!tmp)
		return (ft_lstclear(list, free), \
		throw_error("Memory allocation failed"));
	node = ft_lstnew(tmp);
	if (!node)
		return (ft_lstclear(list, free), \
		throw_error_free("Failed creating map node", free, tmp));
	ft_lstadd_back(list, node);
	linelen = ft_strlen(node->content);
	if (linelen > *width)
		*width = linelen;
	return (0);
}

int	read_map(char *line, int fd, t_map *map)
{
	t_list	*maplist;
	int		error;

	map->width = 0;
	maplist = NULL;
	if (!line)
		return (close(fd), throw_error("Scene file misconfigured"));
	while (line[0] == '\n' || line[0] == '\r')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && line[0] != '\n' && line[0] != '\r')
	{
		if (add_line_to_list(line, &maplist, &map->width))
			return (close(fd), 1);
		line = get_next_line(fd);
	}
	if (line && (line[0] == '\n' || line[0] == '\r'))
		free(line);
	error = convert_map(map, maplist);
	ft_lstclear(&maplist, free);
	if (error)
		return (close(fd), 1);
	return (close(fd), 0);
}
