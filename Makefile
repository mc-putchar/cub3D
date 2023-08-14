# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 16:48:19 by mcutura           #+#    #+#              #
#    Updated: 2023/08/14 16:48:19 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--- TARGET ---

NAME	:=	cub3D

#--- DIRECTORIES ---

SRCDIR		:=	src
INCDIR		:=	inc
OBJDIR		:=	obj
LIBFTDIR	:=	lib/libft
LIBMLXDIR	:=	lib/MLX42

#--- LIBRARIES ---

LIBFT	:=	$(LIBFTDIR)/libft.a
LIBMLX	:=	$(LIBMLXDIR)/build/libmlx42.a

#--- SOURCES ---

SRC		:=	main.c
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRC))

#--- OBJECTS ---

OBJS	:=	$(SRC:%.c=$(OBJDIR)/%.o)

#--- HEADERS ---

_HEADERS	:=	cub3D.h
HEADERS		:=	$(addprefix $(INCDIR)/, $(_HEADERS))
INCLUDES	:=	-I$(INCDIR) -I$(LIBFTDIR) -I$(LIBMLXDIR)/include

#--- FLAGS ---

CFLAGS	:=	-Wall -Wextra -Werror -pedantic-errors
LDFLAGS	:= -L$(LIBFTDIR) -L$(LIBMLXDIR)
LDLIBS	:= -lft $(LIBMLX)
LFLAGS	:= -ldl -lglfw -pthread -lm

#--- DEBUG ---

debug:	CFLAGS		+= -ggdb3
debug:	CPPFLAGS	+= -DDEBUG

#--- CMDS ---

CC		:=	cc
RM		:=	rm -rf
MKDIR	:=	mkdir
COMPILE	:=	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(LDFLAGS)

#--- RULES ---
.PHONY: all clean debug fclean re

all: $(LIBMLX) $(NAME)

$(NAME): $(HEADERS) $(OBJS) $(LIBFT)
	$(COMPILE) $(OBJS) $(LFLAGS) $(LDLIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(LIBMLX):
	@cmake $(LIBMLXDIR) -B $(LIBMLXDIR)/build && $(MAKE) -C $(LIBMLXDIR)/build -j4

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

# debug: fclean
# compile MLX42 with DEBUG=1 to see assertions and to add debug flags
# 	@$(MAKE) -C $(LIBFTDIR) $@
# 	$(COMPILE) $(OBJS) $(LFLAGS) $(LDLIBS) -o $(NAME)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJDIR)
	@$(RM) $(LIBMLXDIR)/build
	@$(MAKE) -C $(LIBFTDIR) $@

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) $@

re: fclean all
