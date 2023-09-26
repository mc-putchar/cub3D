# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 16:48:19 by mcutura           #+#    #+#              #
#    Updated: 2023/09/26 14:12:04 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- USAGE ---

# make			compile the project to an executable file
# make all		^same
# make clean	remove binary object files
# make fclean	remove all compiled files
# make re		remove all compiled files and recompile again
# make debug	compile all with debug flags
# make sanity	compile debug with memory address sanitize injected
# make noleaks	compile debug without leaky external functions

# --- TARGET ---

NAME	:=	cub3D

# --- DIRECTORIES ---

SRCDIR		:=	src
INCDIR		:=	inc
OBJDIR		:=	obj
SUBDIRS		:=	$(addprefix $(OBJDIR)/, init utils draw game)
LIBFTDIR	:=	lib/libft
# LIBMLXDIR	:=	lib/MLX42
LIBMLXDIR	:=	lib/minilibx-linux

# --- SOURCES ---

SRC		:=	main.c
SRC		+=	init/init_scene.c init/init_window.c init/read_map.c
SRC		+=	init/set_scene_params.c init/load_textures.c init/init_hooks.c
SRC		+=	init/spawn_player.c init/init_camera.c
SRC		+=	utils/error_handler.c utils/freez.c
SRC		+=	draw/put_pixel.c draw/draw_screen.c draw/draw_minimap.c
SRC		+=	draw/draw_sprite.c
SRC		+=	game/move_player.c game/turn_player.c game/interact.c game/hooks.c
SRC		+=	game/raycaster.c game/wall_check.c game/fps.c
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRC))

# --- INCLUDES ---

HDRS		:=	cub3D.h game_data.h point.h vector.h keycodes.h
HEADERS		:=	$(addprefix $(INCDIR)/, $(HDRS))
INCLUDES	:=	-I$(INCDIR) -I$(LIBFTDIR)
# INCLUDES	+=	-I$(LIBMLXDIR)/include
INCLUDES	+=	-I/usr/local/include -Imlx-linux

# --- OBJECTS ---

OBJS	:=	$(SRC:%.c=$(OBJDIR)/%.o)

# --- LIBRARIES ---

LIBFT	:=	$(LIBFTDIR)/libft.a
# LIBMLX	:=	$(LIBMLXDIR)/build/libmlx42.a
LIBMLX	:=	/usr/local/lib/libmlx.a

# --- FLAGS ---

CFLAGS	:=	-Wall -Wextra -Werror -pedantic-errors
LDFLAGS	:=	-L$(LIBFTDIR)
LDFLAGS	+=	-L/usr/local/lib -Lmlx_linux
LDLIBS	:=	-lft $(LIBMLX)
# LFLAGS	:=	-ldl -lX11 -lglfw -pthread -lm
LFLAGS	:=	-lXext -lX11 -lm -lz

# --- DEBUG ---

debug:		CFLAGS		+= -ggdb3 -O0
debug:		CPPFLAGS	+= -DDEBUG=1
# debug:		MLXDEBUG	:= -DDEBUG=1
debug:		DEBUGFLAG	:= debug
sanity:		CFLAGS		+= -fsanitize=address
noleaks:	CPPFLAGS	+= -DNOLEAKS=1

# --- CMDS ---

CC		:=	cc
CD		:=	cd
RM		:=	rm -fr
MKDIR	:=	mkdir -pm 775
ECHO	:=	echo

# --- RULES ---
.PHONY: all clean debug fclean re sanity

all: $(LIBFT) $(LIBMLX) $(NAME)

$(NAME): $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJS) $(LDLIBS) $(LFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) $(DEBUGFLAG)

# $(LIBMLX):
#	@cmake $(MLXDEBUG) $(LIBMLXDIR) -B $(LIBMLXDIR)/build && $(MAKE) -C $(LIBMLXDIR)/build -j4

$(SUBDIRS):
	$(MKDIR) $(SUBDIRS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(SUBDIRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

debug: all

sanity: debug

noleaks: debug

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJDIR)
	@$(MAKE) -C $(LIBFTDIR) $@
	# @$(RM) $(LIBMLXDIR)/build

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) $@

re: fclean all
