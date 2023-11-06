# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsoares- <nsoares-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 17:52:53 by nsoares-          #+#    #+#              #
#    Updated: 2023/11/02 11:36:55 by nsoares-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g  
RM = rm -rf
LIBFT = ./libft/libft.a

# __________MLX_______________

MLX = -L ./minilibx-linux -lmlx -Ilmlx -lXext -lX11 -lm

# _________SOURCES____________

SOURCE_FILES = gnl/get_next_line.c gnl/get_next_line_utils.c \
				main.c src/moves/hook.c src/cub_utils.c src/inits/window.c src/inits/init.c \
				src/parser/file_access.c src/parser/check_args.c src/draw_map/draw.c \
				src/moves/moves.c src/moves/move_rotate.c src/map_construct/map.c src/draw_map/render.c \
				src/moves/handle_moves.c
				

OBJS_FILES = $(SOURCE_FILES:.c=.o)

# __________COLORS____________

BOLD_PURPLE	=	\033[1;35m
BOLD_CYAN	=	\033[1;36m
BOLD_YELLOW	=	\033[1;33m
NO_COLOR	=	\033[0m

# _________MESSAGE_____________

COMPILATION_START	=	echo "\n$(BOLD_YELLOW)Make: $(NO_COLOR)Compilation start...\n"

CUB3D_READY  =   echo "\n$(BOLD_YELLOW)cub3D ready! ✅ \n"

CLEANED		=	echo "\n$(BOLD_YELLOW)Clean: $(NO_COLOR)Removed all the \".o\" files \n"

FCLEANED	=	echo "\n$(BOLD_YELLOW)Fclean: $(NO_COLOR)Removed the executables \n"

RE          =   echo "\n$(BOLD_YELLOW)Re: $(NO_COLOR)Compilation restarted \n"

# __________RULES______________

all: compilation_start $(NAME)

$(NAME): $(OBJS_FILES)
		$(MAKE) --no-print-directory -C ./libft
		@ chmod 777 ./minilibx-linux/./configure
		$(MAKE) --no-print-directory -C ./minilibx-linux
		$(CC) $(CFLAGS) $(SOURCE_FILES) $(LIBFT) $(MLX) -o $(NAME)
		@ $(CUB3D_READY)

compilation_start:
	@ $(COMPILATION_START)

clean:
	@ $(RM) $(OBJS_FILES)
	@ cd libft && make clean
	@ $(CLEANED)
	
fclean: clean
	@ $(RM) $(NAME)
	@ cd libft && make fclean
	@ cd ./minilibx-linux && make clean
	@ $(FCLEANED)
		
re:	fclean all
	@ $(RE) 