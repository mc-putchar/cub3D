/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:36:59 by mcutura           #+#    #+#             */
/*   Updated: 2024/05/02 12:12:40 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static int	update_line(char **l, struct s_gnl_data *d, size_t cu, size_t *pr)
{
	char	*tmp;
	size_t	i;

	if (d->off + cu < (size_t)d->end)
		++cu;
	tmp = malloc(cu + *pr + 1);
	if (!tmp)
		return (1);
	i = (size_t)(-1);
	while (++i < *pr)
		tmp[i] = (*l)[i];
	free(*l);
	i = (size_t)(-1);
	while (++i < cu)
		tmp[i + *pr] = d->buff[d->off + i];
	tmp[cu + *pr] = 0;
	*l = tmp;
	*pr += cu;
	return (0);
}

static int	read_more(int fd, struct s_gnl_data *dat, char **line)
{
	dat->off = 0;
	dat->end = read(fd, dat->buff, BUFFER_SIZE);
	if (dat->end > 0)
		return (0);
	if (dat->end)
	{
		if (*line)
			free(*line);
		*line = NULL;
		dat->end = 0;
	}
	return (1);
}

char	*get_delim(int fd, int delim)
{
	static struct s_gnl_data	dat = {0};
	char						*line;
	size_t						c;
	size_t						p;

	p = 0;
	line = NULL;
	while (fd > -1 && BUFFER_SIZE > 0)
	{
		if (!dat.end && read_more(fd, &dat, &line))
			return (line);
		c = 0;
		while (c + dat.off < (size_t)dat.end && dat.buff[dat.off + c] != delim)
			++c;
		if (update_line(&line, &dat, c, &p))
			return (free(line), NULL);
		if (c + dat.off != (size_t)dat.end || dat.buff[dat.off + c] == delim)
		{
			dat.off = (dat.off + c + 1) * (c + 1 < dat.end - dat.off);
			dat.end *= (dat.off != 0);
			return (line);
		}
		dat.end = 0;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	return (get_delim(fd, '\n'));
}
