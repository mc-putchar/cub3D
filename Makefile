# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 16:48:19 by mcutura           #+#    #+#              #
#    Updated: 2023/09/29 05:13:28 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- USAGE ---

# make			compile the project to an executable file
# make all		^same
# make bonus	^same (too lazy to make separate dumbed down binary w/out bonus)
# make clean	remove binary object files
# make fclean	remove all compiled files
# make re		remove all compiled files and recompile again
# make debug	compile all with debug flags
# make sanity	compile debug with memory address sanitize injected
# make noleaks	compile debug without leaky external functions

# --- TARGET ---

NAME		:=	cub3D

# --- DOWNLOADABLES ---

LIBMLXURL	:=	git@github.com:42Paris/minilibx-linux.git

# --- DIRECTORIES ---

SRCDIR		:=	src
INCDIR		:=	inc
OBJDIR		:=	obj
SUBDIRS		:=	$(addprefix $(OBJDIR)/, init draw game utils)
LIBFTDIR	:=	lib/libft
LIBMLXDIR	:=	lib/minilibx-linux

# --- SOURCES ---

SRC		:=	main.c
SRC		+=	init/init_scene.c init/init_window.c init/read_map.c
SRC		+=	init/set_scene_params.c init/load_textures.c init/init_hooks.c
SRC		+=	init/spawn_player.c init/init_camera.c init/get_extras.c 
SRC		+=	init/init_cub.c init/validate_map.c
SRC		+=	draw/put_pixel.c draw/draw_screen.c draw/draw_minimap.c
SRC		+=	draw/draw_sprite.c
SRC		+=	game/move_player.c game/turn_player.c game/interact.c game/hooks.c
SRC		+=	game/raycaster.c game/wall_check.c game/fps.c
SRC		+=	utils/error_handler.c utils/freez.c utils/quicksort.c
SRC		+=	utils/sprites_to_array.c
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRC))

# --- INCLUDES ---

HDRS		:=	cub3D.h game_data.h point.h vector.h keycodes.h
HEADERS		:=	$(addprefix $(INCDIR)/, $(HDRS))
INCLUDES	:=	-I$(INCDIR) -I$(LIBFTDIR)
INCLUDES	+=	-I/usr/local/include -Imlx-linux
INCLUDES	+=	-I$(LIBMLXDIR)

# --- OBJECTS ---

OBJS	:=	$(SRC:%.c=$(OBJDIR)/%.o)

# --- LIBRARIES ---

LIBFT		:=	$(LIBFTDIR)/libft.a
LIBMLX		:=	$(LIBMLXDIR)/libmlx.a
LIBMLXLOCAL	:=	/usr/local/lib/libmlx.a
AUTHR		:=	./res/shiteam.nfo
WHAT		:=	"\t\t\t\t presents"
BANNER		:=	./res/splash.nfo

# --- FLAGS ---

CFLAGS	:=	-Wall -Wextra -Werror -pedantic-errors
LDFLAGS	:=	-L$(LIBFTDIR)
LDFLAGS	+=	-L/usr/local/lib
LDLIBS	:=	-lft $(LIBMLX)
LFLAGS	:=	-lXext -lX11 -lm -lz

# --- DEBUG ---

debug:		CFLAGS		+= -ggdb3 -O0
debug:		CPPFLAGS	+= -DDEBUG=1
debug:		DEBUGFLAG	:= debug
sanity:		CFLAGS		+= -fsanitize=address
noleaks:	CPPFLAGS	+= -DNOLEAKS=1

# --- CMDS ---

CC		:=	cc
CD		:=	cd
RM		:=	rm -fr
MKDIR	:=	mkdir -pm 775
ECHO	:=	echo
SHOW	:=	cat

# --- RULES ---
.PHONY: all bonus clean debug fclean re sanity

all: $(NAME)

bonus: all

$(NAME): $(LIBFT) $(LIBMLX) $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJS) $(LDLIBS) $(LFLAGS) -o $(NAME)
	@$(SHOW) $(AUTHR)
	@$(ECHO) $(WHAT)
	@$(SHOW) $(BANNER)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) $(DEBUGFLAG)

$(LIBMLX): | $(LIBMLXDIR)
	@if [ -f $(LIBMLXLOCAL) ]; then ln -s $(LIBMLXLOCAL) $(LIBMLX); \
	else git clone $(LIBMLXURL) $(LIBMLXDIR) && cd $(LIBMLXDIR) && $(MAKE); \
	fi

$(LIBMLXDIR):
	$(MKDIR) $(LIBMLXDIR)

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

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) $@

re: fclean all
