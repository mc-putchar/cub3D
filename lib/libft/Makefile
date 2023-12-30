# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 17:39:56 by mcutura           #+#    #+#              #
#    Updated: 2023/09/28 04:01:07 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#--- TARGET ---

NAME	:=	libft.a

#--- CMDS ---
CC		:=	cc
AR		:=	ar -rcs
ifdef OS
	MKDIR	= md
	PWD		= cd
	RM		= del /Q
	FixPath = $(subst /,\,$1)
else
	ifeq ($(shell uname), Linux)
		MKDIR	= mkdir -pm 775
		PWD		= $(shell pwd)
		RM		= rm -fr
		FixPath	= $1
	endif
endif

#--- DIRECTORIES ---

SRCDIR		:=	src
OBJDIR		:=	obj

#--- SOURCES ---

SRC		:=	ft_abs.c ft_atoi.c ft_atoi_base.c ft_bzero.c ft_calloc.c \
	ft_clampd.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c \
	ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
	ft_lstnew.c ft_lstsize.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memgrow.c ft_memmove.c ft_memset.c ft_printf.c \
	ft_printf_converters.c ft_printf_converters_hex.c \
	ft_printf_handle_flags.c ft_printf_utils.c ft_putchar_fd.c \
	ft_putline_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c ft_swap.c ft_tolower.c ft_toupper.c \
	get_next_line.c ft_splits.c ft_isnumber.c ft_atod_dirty.c ft_lstpop.c \
	ft_lstpush.c
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRC))

#--- OBJECTS ---

OBJS	:=	$(SRC:%.c=$(OBJDIR)/%.o)

#--- HEADERS ---

HEADERS	:=	libft.h src/ft_printf.h src/get_next_line.h

#--- FLAGS ---

CFLAGS	:=	-Wall -Wextra -Werror -pedantic-errors

#--- RULES ---

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(HEADERS) $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
