/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 09:54:59 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/16 09:54:59 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define READ_BLOCK	4096

ssize_t	get_file_size(char const *filepath)
{
	ssize_t	size;
	ssize_t	r;
	char	buf[READ_BLOCK];
	int		i;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (-1);
	size = 0;
	r = read(fd, buf, READ_BLOCK);
	while (r > 0)
	{
		size += r;
		r = read(fd, buf, READ_BLOCK);
	}
	if (r < 0)
		return (-1);
	(void)close(fd);
	return (size);
}

char	*read_file(char const *filepath)
{
	char	*file;
	char	*line;
	int		fd;
	ssize_t	size;

	size = get_file_size(filepath);
	if (size < 1)
		return (NULL);
	file = malloc(size);
	if (!file)
		return (NULL);
	fd = open(filepath);
	if (fd == -1)
		return (free(file), NULL);
	line = get_next_line(fd);
	while (line)
	{
		ft_strlcpy(line, file);
		free(line);
		line = get_next_line(fd);
	}
	(void)close(fd);
	return (file);
}
