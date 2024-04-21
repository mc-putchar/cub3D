# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 11:35:47 by mcutura           #+#    #+#              #
#    Updated: 2024/04/21 03:08:18 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D
BONUS := cub3D_PoD

SRCDIR := src
INCDIR := include
LIBDIR := lib
BINDIR := bin
BONUSBINDIR := bin/bonus
SUBDIRS := $(addprefix $(BINDIR)/, core gfx init utils)
SUBDIRS += $(addprefix $(BONUSBINDIR)/, core gfx init sound utils)

LIBFTDIR := $(LIBDIR)/libft
LIBFT := $(LIBFTDIR)/libft.a

# /* Merci! Paris! */
LIBMLXURL := https://github.com/42Paris/minilibx-linux.git
LIBMLXDIR := $(LIBDIR)/minilibx-linux
LIBMLX := $(LIBMLXDIR)/libmlx.a
LIBMLXLOCAL := /usr/local/include/mlx.h

HEADER := $(INCDIR)/cub3D.h
BONUSHEADER := $(INCDIR)/cub3D_bonus.h

# Binaries
CORE := $(addprefix core/, player_control.o)
GFX := $(addprefix gfx/, put_pixel.o new_img.o load_texture.o)
GFX += $(addprefix gfx/, draw_map.o render_scene.o raycaster.o)
INIT := $(addprefix init/, init_scene.o init_scene_params.o init_canvas.o)
INIT += $(addprefix init/, init_hooks.o init_window.o init_camera.o)
INIT += $(addprefix init/, init_map.o validate_map.o spawn_player.o)
UTILS := $(addprefix utils/, error_handler.o freez.o validators.o)
BINS := $(addprefix $(BINDIR)/, launcher.o $(CORE) $(GFX) $(INIT) $(UTILS))

# Bonus binaries
BONUSCORE := $(addprefix core/, player_control.o player_interact.o)
BONUSGFX := $(addprefix gfx/, put_pixel.o new_img.o load_texture.o)
BONUSGFX += $(addprefix gfx/, draw_map.o render_scene.o raycaster.o)
BONUSGFX += $(addprefix gfx/, draw_splash.o)
BONUSINIT := $(addprefix init/, init_scene_bonus.o init_scene_params_bonus.o)
BONUSINIT += $(addprefix init/, init_camera.o init_canvas.o)
BONUSINIT += $(addprefix init/, init_map.o validate_map.o spawn_player.o)
BONUSINIT += $(addprefix init/, init_window_bonus.o init_hooks_bonus.o)
BONUSINIT += $(addprefix init/, load_thread.o init_extra.o init_sprite.o)
# BONUSSOUND := $(addprefix sound/, play_sound.o)
BONUSUTILS := $(addprefix utils/, error_handler.o freez.o validators.o)
BONUSUTILS += $(addprefix utils/, freez_bonus.o)
BONUSBINS := $(addprefix $(BONUSBINDIR)/, launcher_bonus.o \
	$(BONUSCORE) $(BONUSGFX) $(BONUSINIT) $(BONUSSOUND) $(BONUSUTILS))

CC := cc
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99
debug: CFLAGS += -g -Og
release: CFLAGS += -O3 -march=native
CPPFLAGS := -I$(INCDIR) -I$(LIBFTDIR)/include -I$(LIBMLXDIR)
LDFLAGS := -L$(LIBFTDIR) -L$(LIBMLXDIR)
LDLIBS := -lft -lmlx
LFLAGS := -lXext -lX11 -lm -lz -lpulse-simple

TEAM := ./res/shiteam.nfo
BANNER := ./res/splash.nfo

MKDIR := mkdir -pm 775
GITCLONE := git clone
ECHO := echo
SHOW := cat

.PHONY: all bonus nobonus clean fclean re debug release

release: all
all: $(NAME) $(BONUS)
bonus: $(BONUS)
nobonus: $(NAME)

$(NAME): $(HEADER) $(BINS) $(LIBMLX) | $(LIBFT)
	$(CC) $(BINS) $(LDFLAGS) $(LDLIBS) $(LFLAGS) -o $(NAME)

$(BONUS): $(HEADER) $(BONUSHEADER) $(BONUSBINS) $(LIBMLX) | $(LIBFT)
	$(CC) $(BONUSBINS) $(LDFLAGS) $(LDLIBS) $(LFLAGS) -o $(BONUS)
	@$(SHOW) $(TEAM)
	@$(SHOW) $(BANNER)

$(BINS): $(BINDIR)/%.o: $(SRCDIR)/%.c $(HEADER) | $(SUBDIRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BONUSBINS): $(BONUSBINDIR)/%.o: $(SRCDIR)/%.c $(BONUSHEADER) $(HEADER) | $(SUBDIRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(SUBDIRS):
	$(MKDIR) $(SUBDIRS)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR) release

$(LIBMLX):
	$(GITCLONE) $(LIBMLXURL) $(LIBMLXDIR)
	$(MAKE) -C $(LIBMLXDIR)

clean:
	$(RM) $(BINS)
	$(RM) $(BONUSBINS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS)

re: fclean all
debug: all
