# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 16:48:19 by mcutura           #+#    #+#              #
#    Updated: 2023/09/23 18:09:05 by mcutura          ###   ########.fr        #
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

# --- TARGET ---

NAME	:=	cub3D

# --- DIRECTORIES ---

SRCDIR		:=	src
INCDIR		:=	inc
OBJDIR		:=	obj
SUBDIRS		:=	$(addprefix $(OBJDIR)/, init err utils draw ray game)
LIBFTDIR	:=	lib/libft
LIBMLXDIR	:=	lib/MLX42

# --- SOURCES ---

SRC		:=	main.c
SRC		+=	init/init_scene.c init/init_window.c init/read_map.c
SRC		+=	init/set_scene_params.c init/load_textures.c init/hooks.c
SRC		+=	init/spawn_player.c init/init_camera.c
SRC		+=	err/error_handler.c
SRC		+=	utils/freez.c
SRC		+=	draw/put_pixel.c draw/draw_screen.c draw/draw_minimap.c
SRC		+=	ray/raycaster.c ray/wall_check.c
SRC		+=	game/move_player.c game/turn_player.c
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRC))

# --- INCLUDES ---

HDRS		:=	cub3D.h game_data.h point.h vector.h
HEADERS		:=	$(addprefix $(INCDIR)/, $(HDRS))
INCLUDES	:=	-I$(INCDIR) -I$(LIBFTDIR) -I$(LIBMLXDIR)/include

# --- OBJECTS ---

OBJS	:=	$(SRC:%.c=$(OBJDIR)/%.o)

# --- LIBRARIES ---

LIBFT	:=	$(LIBFTDIR)/libft.a
LIBMLX	:=	$(LIBMLXDIR)/build/libmlx42.a
#LIBMLX	:=	/usr/local/lib/libmlx.a

# --- FLAGS ---

CFLAGS	:=	-Wall -Wextra -Werror -pedantic-errors
LDFLAGS	:= -L$(LIBFTDIR)
LDLIBS	:= -lft $(LIBMLX)
LFLAGS	:= -ldl -lX11 -lglfw -pthread -lm

# --- DEBUG ---

debug:	CFLAGS		+= -ggdb3 -O0
debug:	CPPFLAGS	+= -DDEBUG=1
debug:	MLXDEBUG	:= -DDEBUG=1
debug:	DEBUGFLAG	:= debug
sanity:	CFLAGS		+= -fsanitize=address

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

$(LIBMLX):
	@cmake $(MLXDEBUG) $(LIBMLXDIR) -B $(LIBMLXDIR)/build && $(MAKE) -C $(LIBMLXDIR)/build -j4

$(SUBDIRS):
	$(MKDIR) $(SUBDIRS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(SUBDIRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

debug: all

sanity: debug

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJDIR)
	#@$(RM) $(LIBMLXDIR)/build
	@$(MAKE) -C $(LIBFTDIR) $@

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) $@

re: fclean all
