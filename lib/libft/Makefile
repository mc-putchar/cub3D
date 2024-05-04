# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 12:21:15 by mcutura           #+#    #+#              #
#    Updated: 2024/05/02 12:14:58 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

SRCDIR := src
BINDIR := bin
INCDIR := include

IDN := $(addprefix $(BINDIR)/, ft_isalnum.o ft_isalpha.o ft_isascii.o \
	ft_isdigit.o ft_isprint.o ft_isnumber.o)
CON := $(addprefix $(BINDIR)/, ft_atoi.o ft_tolower.o ft_toupper.o ft_itoa.o \
	ft_atod.o)
MEM := $(addprefix $(BINDIR)/, ft_bzero.o ft_calloc.o ft_memchr.o ft_memrchr.o \
	ft_memcmp.o ft_memcpy.o ft_memccpy.o ft_memset.o ft_memmove.o)
STR := $(addprefix $(BINDIR)/, ft_strchr.o ft_strdup.o ft_strjoin.o \
	ft_strlcat.o ft_strlcpy.o ft_strlen.o ft_strncmp.o ft_strnstr.o \
	ft_strrchr.o ft_strtrim.o ft_substr.o ft_strmapi.o ft_striteri.o \
	ft_split.o ft_splits.o)
I/O := $(addprefix $(BINDIR)/, ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o \
	ft_putnbr_fd.o)
LST := $(addprefix $(BINDIR)/, ft_lstadd_front.o ft_lstadd_back.o \
	ft_lstdelone.o ft_lstclear.o ft_lstnew.o ft_lstsize.o ft_lstiter.o \
	ft_lstlast.o ft_lstmap.o)
GNL := $(BINDIR)/get_next_line.o
PRNTF := $(addprefix $(BINDIR)/, ft_printf.o ft_printf_utils.o \
	ft_printf_converters.o ft_printf_converters_hex.o)

HEADER := libft.h
MEMH := libft_mem.h
STRH := libft_str.h
I/OH := libft_io.h
LSTH := libft_lst.h
GNLH := get_next_line.h
PRNTFH := ft_printf.h

CC := cc
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99
debug: CFLAGS += -g -Og
release: CFLAGS += -march=native -O2
ARFLAGS := src
MKDIR := mkdir -p
INSTALL :=

.PHONY: all clean fclean re debug release install

all: $(NAME)

$(IDN): $(INCDIR)/$(HEADER)
$(CON): $(INCDIR)/$(HEADER)
$(MEM): $(INCDIR)/$(MEMH)
$(STR): $(INCDIR)/$(STRH)
$(I/O): $(INCDIR)/$(I/OH)
$(LST): $(INCDIR)/$(LSTH)
$(GNL): $(INCDIR)/$(GNLH)
$(PRNTF): $(INCDIR)/$(PRNTFH)

$(NAME): $(INCDIR)/$(HEADER) $(IDN) $(CON) $(MEM) $(STR) $(I/O) $(LST) $(GNL) $(PRNTF)
	$(AR) $(ARFLAGS) $(NAME) $(IDN) $(CON) $(MEM) $(STR) $(I/O) $(LST) $(GNL) $(PRNTF)

$(IDN) $(CON) $(MEM) $(STR) $(I/O) $(LST) $(GNL) $(PRNTF): \
  $(BINDIR)/%.o: $(SRCDIR)/%.c |$(BINDIR)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(BINDIR):
	$(MKDIR) $(BINDIR)

clean:
	$(RM) -r $(BINDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
debug: re
release: re
install: release
	$(INSTALL)
