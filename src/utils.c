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

ssize_t	get_file_size(char *filepath, int *line_count)
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
	*line_count = 0;
	r = read(fd, buf, READ_BLOCK);
	while (r > 0)
	{
		size += r;
		i = 0;
		while (i < r)
			if (buf[i++] == '\n')
				(*line_count)++;
		r = read(fd, buf, READ_BLOCK);
	}
	if (r < 0)
		return (-1);
	close(fd);
	return (size);
}
