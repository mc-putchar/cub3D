/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:08:02 by mcutura           #+#    #+#             */
/*   Updated: 2024/03/17 06:09:33 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

struct s_gnl_data
{
	size_t	off;
	ssize_t	end;
	char	buff[BUFFER_SIZE];
};

char	*get_delim(int fd, int delim);
char	*get_next_line(int fd);

#endif // GET_NEXT_LINE_H
