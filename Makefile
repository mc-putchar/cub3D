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

#--- SOURCES ---

SRC		:=	main.c init.c utils.c error_handler.c
SRC		+=	hooks.c freez.c colors.c
SRC		+=	draw_lines.c bresenham.c draw_shapes.c draw_map.c draw_player.c
SRC		+=	player.c
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRC))

#--- HEADERS ---

_HEADERS	:=	cub3D.h point.h game_data.h
HEADERS		:=	$(addprefix $(INCDIR)/, $(_HEADERS))
INCLUDES	:=	-I$(INCDIR) -I$(LIBFTDIR) -I$(LIBMLXDIR)/include

#--- OBJECTS ---

OBJS	:=	$(SRC:%.c=$(OBJDIR)/%.o)

#--- LIBRARIES ---

LIBFT	:=	$(LIBFTDIR)/libft.a
LIBMLX	:=	$(LIBMLXDIR)/build/libmlx42.a

#--- FLAGS ---

CFLAGS	:=	-Wall -Wextra -Werror -pedantic-errors
LDFLAGS	:= -L$(LIBFTDIR) -L$(LIBMLXDIR)
LDLIBS	:= -lft $(LIBMLX)
LFLAGS	:= -ldl -lglfw -pthread -lm

#--- DEBUG ---

debug:	CFLAGS		+= -ggdb3
debug:	CPPFLAGS	+= -DDEBUG
debug:	MLXDEBUG	:= -DDEBUG=1
debug:	DEBUGFLAG	:= debug

#--- CMDS ---

CC		:=	cc
RM		:=	rm -rf
MKDIR	:=	mkdir

#--- RULES ---
.PHONY: all clean debug fclean re

all: $(LIBFT) $(LIBMLX) $(NAME)

$(NAME): $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJS) $(LDLIBS) $(LFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR) $(DEBUGFLAG)

$(LIBMLX):
	@cmake $(MLXDEBUG) $(LIBMLXDIR) -B $(LIBMLXDIR)/build && $(MAKE) -C $(LIBMLXDIR)/build -j4

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

debug: all

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJDIR)
	@$(RM) $(LIBMLXDIR)/build
	@$(MAKE) -C $(LIBFTDIR) $@

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) $@

re: fclean all
