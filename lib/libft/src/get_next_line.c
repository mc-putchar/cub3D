/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:00:17 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/19 06:13:26 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	init_buffer(t_stream *stream, unsigned char **re, ssize_t *rs)
{
	if (*rs == -1)
	{
		stream->len = read(stream->fd, stream->buff, BUFFER_SIZE);
		return (stream->len);
	}
	if (!*re)
		return (-1);
	ft_memcpy(stream->buff, *re, *rs);
	free(*re);
	stream->len = *rs;
	stream->off = 0;
	*rs = -1;
	return (stream->len);
}

static void	save_re(t_stream *stream, unsigned char **re, ssize_t *rs)
{
	if (stream->off < (size_t)stream->len)
	{
		*re = malloc(stream->len - stream->off);
		*rs = stream->len - stream->off;
	}
	if (!*re || stream->off >= (size_t)stream->len)
		*rs = -1;
	else
		ft_memcpy(*re, stream->buff + stream->off, *rs);
}

static unsigned char	*getl(t_stream *s, size_t *n)
{
	unsigned char	*line;
	unsigned char	*tmp;

	line = NULL;
	while (s->len > 0)
	{
		line = ft_memgrow(line, *n, *n + s->len + 1);
		if (!line)
			return (NULL);
		tmp = ft_memccpy(line + *n, s->buff, 10, s->len);
		if (tmp)
		{
			s->off = (size_t)(tmp - line - *n);
			*n += s->off;
			return (line);
		}
		*n += s->len;
		s->len = read(s->fd, s->buff, BUFFER_SIZE);
	}
	if (s->len == -1)
		return (free(line), NULL);
	return (line);
}

static unsigned char	*gnl(t_stream *s, unsigned char **re, ssize_t *rs)
{
	size_t			n;
	unsigned char	*line;

	n = 0;
	if (init_buffer(s, re, rs) < 1)
		return (NULL);
	line = getl(s, &n);
	if (!line)
		return (NULL);
	if (s->len > 0)
		save_re(s, re, rs);
	else
		*rs = -1;
	line[n] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static unsigned char	*re = NULL;
	static ssize_t			res = -1;
	unsigned char			*nline;
	t_stream				*stream;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stream = malloc(sizeof(t_stream));
	if (!stream)
		return (NULL);
	stream->fd = fd;
	nline = gnl(stream, &re, &res);
	if (!nline)
	{
		re = NULL;
		return (free(stream), NULL);
	}
	return (free(stream), (char *)nline);
}
