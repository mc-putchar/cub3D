/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:47:01 by mcutura           #+#    #+#             */
/*   Updated: 2023/08/14 17:47:01 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

/* IDENTITY */
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);

/* CONVERTERS */
int					ft_tolower(int c);
int					ft_toupper(int c);

/* PUTS */
ssize_t				ft_putchar_fd(char c, int fd);
ssize_t				ft_putnbr_fd(int n, int fd);
ssize_t				ft_putstr_fd(char *s, int fd);
ssize_t				ft_putendl_fd(char *s, int fd);

/* PRINTS */
int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);

/* READS */
char				*get_next_line(int fd);

/* NUMBERS */
int					ft_abs(int n);
int					ft_atoi(const char *nptr);
int					ft_atoi_base(char *str, char *base);
char				*ft_itoa(int n);
char				*ft_uitoa(unsigned int n);
double				ft_clampd(double d, double min, double max);
void				ft_swap(int *a, int *b);

/* STRINGS */
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little, \
					size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strdup(const char *s);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_substr(const char *s, unsigned int start, size_t len);
char				*ft_strtrim(const char *s1, const char *set);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				**ft_split(const char *s, char c);

/* MEMORY */
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memcpy(void	*dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memgrow(void *ptr, size_t old_size, size_t new_size);

/* LIST */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstlast(t_list *lst);
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *), \
					void (*del)(void *));

#endif