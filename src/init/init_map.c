/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:59:08 by mcutura           #+#    #+#             */
/*   Updated: 2024/04/21 07:24:20 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	add_line_to_list(char *line, t_list **list, size_t *width);
static int	convert_map(t_map *map, t_list *maplist);

static inline int	flush_gnl(char *line, int fd)
{
	close(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	read_map(char *line, int fd, t_map *map)
{
	t_list	*maplist;
	int		error;

	map->width = 0;
	maplist = NULL;
	while (line && line[0] != '\n' && line[0] != '\r')
	{
		if (add_line_to_list(line, &maplist, &map->width))
		{
			ft_lstclear(&maplist, free);
			return (flush_gnl(line, fd));
		}
		free(line);
		line = get_next_line(fd);
	}
	flush_gnl(line, fd);
	error = convert_map(map, maplist);
	ft_lstclear(&maplist, free);
	return (error);
}

int	add_line_to_list(char *line, t_list **list, size_t *width)
{
	char	*tmp;
	t_list	*node;
	size_t	linelen;

	tmp = ft_strtrim(line, "\r\n");
	if (!tmp)
		return (throw_error(MALLOC_FAIL));
	node = ft_lstnew(tmp);
	if (!node)
		return (throw_error_free(NODE_FAILED, free, tmp));
	ft_lstadd_back(list, node);
	linelen = ft_strlen(node->content);
	if (linelen > *width)
		*width = linelen;
	return (0);
}

int	convert_map(t_map *map, t_list *maplist)
{
	size_t	idx;
	size_t	padding;

	idx = 0;
	if (!maplist)
		return (throw_error(BAD_SCENE));
	map->height = ft_lstsize(maplist);
	map->val = malloc(sizeof(char *) * map->height);
	if (!map->val)
		return (throw_error(MALLOC_FAIL));
	while (idx < map->height && maplist)
	{
		map->val[idx] = malloc(map->width + 1);
		if (!map->val[idx])
			return (free_map(map->val, idx + 1), throw_error(MALLOC_FAIL));
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
