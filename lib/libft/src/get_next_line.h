/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 02:02:07 by mcutura           #+#    #+#             */
/*   Updated: 2023/05/19 06:13:45 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_stream
{
	int				fd;
	ssize_t			len;
	size_t			off;
	unsigned char	buff[BUFFER_SIZE];
}	t_stream;

char			*get_next_line(int fd);
void			*ft_memgrow(void *ptr, size_t old_size, size_t new_size);

#endif
