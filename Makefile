#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguthert <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/30 15:25:02 by jguthert          #+#    #+#              #
#    Updated: 2016/02/16 13:30:37 by jguthert         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

##=-  Compilatator -=##

NAME = fdf
CC = clang


##=-  FLAGS -=##

MLX_FW = -framework OpenGL -framework AppKit
MLX_FLAGS = -lmlx #-lXext -lX11
CFLAGS = -Wall -Wextra #-Werror


##=-  PATH -=##

OBJPATH = obj
SRCPATH = srcs
LIBFT_PATH = libft

INCLUDE_PATH = include/

##=-  Rules -=##

LIBFT = -L $(LIBFT_PATH)
MLX = $(MLX_FLAGS) $(MLX_FW)
LIBS = $(MLX) $(LIBFT) -lft

INCLUDES = -I./ -I $(LIBFT_PATH)/includes -I $(INCLUDE_PATH)


##=-  Files -=##

OBJ = $(SRC:$(SRCPATH)/%.c=$(OBJPATH)/%.o)
	SRC = $(addprefix $(SRCPATH)/,$(SRCSFILES))

SRCSFILES =             main.c      		\
						ft_error.c  		\
						bonus.c				\
						draw.c				\
						hook.c				\
						parcing.c			\
						draw_pixel.c		\
						calcul.c			\
						bonus_fps.c 		\
						bonus_fps_corner.c	\


##=-  Process -=##

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[33mProcessing\n\033[0m"
	@$(MAKE) -C libft/
	@$(CC) -o $@ $(CFLAGS) $(OBJ) $(LIBS)
	@echo "\n\033[33mEnd of the Process\n\033[0m"

$(OBJ): $(OBJPATH)/%.o : $(SRCPATH)/%.c
	@mkdir -p $(dir $@)
	@echo "\033[32m"
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<
	@echo "\033[0m"

clean:
	/bin/rm -rf $(OBJPATH)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all